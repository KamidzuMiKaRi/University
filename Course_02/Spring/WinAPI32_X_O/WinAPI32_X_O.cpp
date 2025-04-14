#include <windows.h> 

#define SIZE 3  // Размер поля крестики-нолики 

HINSTANCE hInst;  // Экземпляр текущего приложения
char grid[SIZE][SIZE];  // Игровое поле
int currentPlayer;  // Текущий игрок: 0 для 'X', 1 для 'O'

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  // Объявление оконной функции

// Функция для сброса игрового поля
void ResetGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = ' ';
        }
    }
    currentPlayer = 0;  // Первый игрок
}

// Функция для рисования игрового поля
void DrawGrid(HDC hdc) {
    RECT rect;
    GetClientRect(WindowFromDC(hdc), &rect);  // Получаем размер клиентской области окна
    int stepX = rect.right / SIZE;  // Шаг для линий сетки по горизонтали
    int stepY = rect.bottom / SIZE;  // Шаг для линий сетки по вертикали

    // Рисуем сетку
    for (int i = 1; i < SIZE; i++) {
        MoveToEx(hdc, i * stepX, 0, NULL);
        LineTo(hdc, i * stepX, rect.bottom);
        MoveToEx(hdc, 0, i * stepY, NULL);
        LineTo(hdc, rect.right, i * stepY);
    }

    // Рисуем символы 'X' и 'O'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != ' ') {
                char symbol[2] = { grid[i][j], '\0' };
                TextOutA(hdc, j * stepX + stepX / 2, i * stepY + stepY / 2, symbol, 1);
            }
        }
    }
}

// Проверка на победителя и ничью
int CheckWin() {
    // Проверка строк и столбцов на победителя
    for (int i = 0; i < SIZE; i++) {
        // Проверка строк
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0];

        // Проверка столбцов
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return grid[0][i];
    }

    // Проверка диагоналей на победителя
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return grid[0][0];

    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return grid[0][2];

    // Проверка на ничью: если нет победителя и все клетки заполнены
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == ' ')
                return 0;  // Клетка пустая, значит игра продолжается
        }
    }

    // Если все клетки заполнены и нет победителя, то ничья
    return -1;
}

// Точка входа для приложения Windows
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    HWND hWnd;
    MSG msg;

    // Создание и регистрация классов окон
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("X-O-GAME");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        return 0;
    }

    // Создание главного окна
    hWnd = CreateWindow(
        TEXT("X-O-GAME"),
        TEXT("Крестики-Нолики"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 300,
        NULL, NULL,
        hInstance, NULL);

    if (!hWnd) {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    ResetGrid();  // Инициализация игрового поля

    // Основной цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Оконная процедура для обработки сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_PAINT:  // Сообщение отрисовки окна
        hdc = BeginPaint(hWnd, &ps);
        DrawGrid(hdc);  // Рисуем игровое поле
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:  // Сообщение нажатия левой кнопки мыши
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        int stepX = rect.right / SIZE;  // Шаг для вычисления координат клетки
        int stepY = rect.bottom / SIZE;

        int x = LOWORD(lParam) / stepX;  // Вычисляем индекс по горизонтали
        int y = HIWORD(lParam) / stepY;  // Вычисляем индекс по вертикали

        if (grid[y][x] == ' ') {  // Если клетка пустая
            grid[y][x] = currentPlayer == 0 ? 'X' : 'O';  // Записываем символ текущего игрока
            currentPlayer = !currentPlayer;  // Переключаем игрока

            int result = CheckWin();  // Проверяем на победу или ничью
            if (result != 0) {
                if (result == -1) {
                    MessageBox(hWnd, TEXT("Ничья!"), TEXT("Конец игры"), MB_OK);
                }
                else {
                    TCHAR buffer[256];
                    wsprintf(buffer, TEXT("Игрок %c победил!"), result);
                    MessageBox(hWnd, buffer, TEXT("Конец игры"), MB_OK);
                }
                ResetGrid();  // Сбрасываем игровое поле
            }

            InvalidateRect(hWnd, NULL, TRUE);  // Обновляем клиентскую область, чтобы перерисовать окно
        }
    }
    break;

    case WM_DESTROY:  // Сообщение закрытия окна
        PostQuitMessage(0);  // Завершаем цикл сообщений
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);  // Обрабатываем все остальные сообщения
    }

    return 0;
}