#include <windows.h>

#define SIZE 3      // Размер игрового поля крестики-нолики

HINSTANCE hInst;    // Экземпляр текущего приложения
char grid[SIZE][SIZE];   // Игровое поле
bool isPlayerOneTurn = true;  // Флаг, определяющий очередь игрока
HWND hWnd1, hWnd2;    // Окна для Игрока 1 и Игрока 2

HANDLE hTurnSemaphore[2]; // Семофоры для управления очередностью ходов игроков

// Прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ResetGrid();
void DrawGrid(HDC hdc);
int CheckWin();
void ResetSemaphores();

// Функция для сброса игрового поля
void ResetGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = ' ';  // Очистка каждой клетки
        }
    }
    isPlayerOneTurn = true;  // Начать с первого игрока
}

// Функция для сброса семафоров на начальное состояние
void ResetSemaphores() {
    ReleaseSemaphore(hTurnSemaphore[0], 1, NULL);  // Устанавливаем семафор для игрока 1
    WaitForSingleObject(hTurnSemaphore[1], 0);     // Сбрасываем семафор для игрока 2
}

// Функция для рисования игрового поля
void DrawGrid(HDC hdc) {
    RECT rect;
    GetClientRect(WindowFromDC(hdc), &rect);
    int stepX = rect.right / SIZE;
    int stepY = rect.bottom / SIZE;

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
                RECT cellRect = { j * stepX, i * stepY, (j + 1) * stepX, (i + 1) * stepY };
                DrawTextA(hdc, &grid[i][j], 1, &cellRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            }
        }
    }
}

// Функция для проверки победителя или ничьей
int CheckWin() {
    for (int i = 0; i < SIZE; i++) {
        // Проверка строк
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0];

        // Проверка столбцов
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return grid[0][i];
    }

    // Проверка диагоналей
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return grid[0][0];

    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return grid[0][2];

    // Проверка на ничью
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == ' ') {
                return 0;  // Игра продолжается
            }
        }
    }

    return -1;  // Ничья
}

// Точка входа для приложения Windows
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    MSG msg;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("X-O-GAME");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // Регистрация класса окна
    if (!RegisterClass(&wc)) {
        return 0;
    }

    // Создание окон для двух игроков
    hWnd1 = CreateWindow(TEXT("X-O-GAME"), TEXT("Игрок 1: Крестики"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInstance, NULL);
    hWnd2 = CreateWindow(TEXT("X-O-GAME"), TEXT("Игрок 2: Нолики"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInstance, NULL);

    if (!hWnd1 || !hWnd2) {
        return 0;
    }

    // Показ окон
    ShowWindow(hWnd1, nCmdShow);
    ShowWindow(hWnd2, nCmdShow);
    UpdateWindow(hWnd1);
    UpdateWindow(hWnd2);

    // Инициализация игрового поля
    ResetGrid();

    // Инициализация семафоров для управления очередностью ходов
    hTurnSemaphore[0] = CreateSemaphore(NULL, 1, 1, L"Player1Turn");
    hTurnSemaphore[1] = CreateSemaphore(NULL, 0, 1, L"Player2Turn");

    // Основной цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Закрытие семафоров перед завершением программы
    CloseHandle(hTurnSemaphore[0]);
    CloseHandle(hTurnSemaphore[1]);

    return (int)msg.wParam;
}

// Оконная процедура для обработки сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawGrid(hdc);  // Рисуем игровое поле
        EndPaint(hWnd, &ps);  // Заканчиваем рисование
        break;
    case WM_LBUTTONDOWN: {
        int x = LOWORD(lParam);  // Получаем координаты клика
        int y = HIWORD(lParam);
        RECT rect;
        GetClientRect(hWnd, &rect);
        int stepX = rect.right / SIZE;
        int stepY = rect.bottom / SIZE;
        int col = x / stepX;
        int row = y / stepY;

        // Определение, какой игрок сделал клик (по какому окну)
        bool isPlayerOne = (hWnd == hWnd1);

        // Проверка очередности хода с использованием семафоров и проверка, не занята ли клетка
        if (((isPlayerOne && WaitForSingleObject(hTurnSemaphore[0], 0) == WAIT_OBJECT_0) ||
            (!isPlayerOne && WaitForSingleObject(hTurnSemaphore[1], 0) == WAIT_OBJECT_0)) &&
            grid[row][col] == ' ') {

            // Обновление клетки игрового поля
            grid[row][col] = isPlayerOne ? 'X' : 'O';

            // Обновление окна для обоих игроков
            InvalidateRect(hWnd1, NULL, TRUE);
            UpdateWindow(hWnd1);
            InvalidateRect(hWnd2, NULL, TRUE);
            UpdateWindow(hWnd2);

            // Проверка состояния игры (победа, ничья или продолжается)
            int winner = CheckWin();
            if (winner != 0) {
                if (winner == 'X') {
                    MessageBox(NULL, TEXT("Игрок 1 выиграл!"), TEXT("Конец игры"), MB_OK);
                }
                else if (winner == 'O') {
                    MessageBox(NULL, TEXT("Игрок 2 выиграл!"), TEXT("Конец игры"), MB_OK);
                }
                else {
                    MessageBox(NULL, TEXT("Ничья!"), TEXT("Конец игры"), MB_OK);
                }
                // Сброс игрового поля и семафоров после завершения игры
                ResetGrid();
                InvalidateRect(hWnd1, NULL, TRUE);
                InvalidateRect(hWnd2, NULL, TRUE);
                UpdateWindow(hWnd1);
                UpdateWindow(hWnd2);
                ResetSemaphores();  // Сброс семафоров
            }
            else {
                // Передача очереди другому игроку
                if (isPlayerOne) {
                    ReleaseSemaphore(hTurnSemaphore[1], 1, NULL);
                }
                else {
                    ReleaseSemaphore(hTurnSemaphore[0], 1, NULL);
                }
            }
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);  // Завершение приложения
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}