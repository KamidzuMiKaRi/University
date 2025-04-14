#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

#define IDM_NEW_GAME 1
#define IDM_EXIT 2

// Размеры окна и клетки.
const int BOARD_SIZE = 3;
const int CELL_SIZE = 100;

// Семафоры для синхронизации между процессами.
HANDLE hTurnSemaphore[2];

// Глобальные переменные для хранения состояния игры.
char board[BOARD_SIZE][BOARD_SIZE];
bool isFirstPlayerTurn = true;
HWND hWnd1, hWnd2;

// Прототипы функций.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawBoard(HWND);
void CheckWin();

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ticTacToeClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc))
        return 1;

    hWnd1 = CreateWindow(wc.lpszClassName, L"Крестики-нолики - Игрок 1", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE, nullptr, nullptr, hInstance, nullptr);
    hWnd2 = CreateWindow(wc.lpszClassName, L"Крестики-нолики - Игрок 2", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd1 || !hWnd2)
        return 2;

    ShowWindow(hWnd1, nCmdShow);
    ShowWindow(hWnd2, nCmdShow);

    // Инициализация семафоров.
    hTurnSemaphore[0] = CreateSemaphore(NULL, 1, 1, L"SemaphorePlayer1");
    hTurnSemaphore[1] = CreateSemaphore(NULL, 0, 1, L"SemaphorePlayer2");

    MSG msg = { 0 };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CloseHandle(hTurnSemaphore[0]);
    CloseHandle(hTurnSemaphore[1]);
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_NEW_GAME:
            for (int i = 0; i < BOARD_SIZE; ++i)
                for (int j = 0; j < BOARD_SIZE; ++j)
                    board[i][j] = ' ';
            InvalidateRect(hWnd1, nullptr, TRUE);
            InvalidateRect(hWnd2, nullptr, TRUE);
            break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lParam) / CELL_SIZE;
        int y = HIWORD(lParam) / CELL_SIZE;

        // Проверка координат на предмет выхода за границы массива.
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        {
            // Проверка семафоров.
            DWORD playerIndex = (hWnd == hWnd1) ? 0 : 1;
            DWORD opponentIndex = (hWnd == hWnd1) ? 1 : 0;

            if (WaitForSingleObject(hTurnSemaphore[playerIndex], 100) == WAIT_OBJECT_0)
            {
                if (board[x][y] == ' ')
                {
                    board[x][y] = (playerIndex == 0) ? 'X' : 'O';
                    InvalidateRect(hWnd, nullptr, TRUE);
                    InvalidateRect((hWnd == hWnd1) ? hWnd2 : hWnd1, nullptr, TRUE);
                    CheckWin();
                }

                // Освобождение семафоров.
                ReleaseSemaphore(hTurnSemaphore[opponentIndex], 1, NULL);
            }
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawBoard(hWnd);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

void DrawBoard(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    // Отрисовка линий сетки
    for (int i = 0; i <= BOARD_SIZE; ++i)
    {
        MoveToEx(hdc, i * CELL_SIZE, 0, nullptr);
        LineTo(hdc, i * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
        MoveToEx(hdc, 0, i * CELL_SIZE, nullptr);
        LineTo(hdc, BOARD_SIZE * CELL_SIZE, i * CELL_SIZE);
    }

    // Отрисовка X и O на игровом поле
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] != ' ')
            {
                RECT rc;
                SetRect(&rc, i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);
                DrawText(hdc, board[i][j] == 'X' ? L"X" : L"O", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            }
        }

    EndPaint(hWnd, &ps);
}

void CheckWin()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            MessageBox(nullptr, board[i][0] == 'X' ? L"Игрок 1 выиграл!" : L"Игрок 2 выиграл!", L"Конец игры", MB_OK);
            return;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            MessageBox(nullptr, board[0][i] == 'X' ? L"Игрок 1 выиграл!" : L"Игрок 2 выиграл!", L"Конец игры", MB_OK);
            return;
        }
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        MessageBox(nullptr, board[0][0] == 'X' ? L"Игрок 1 выиграл!" : L"Игрок 2 выиграл!", L"Конец игры", MB_OK);
        return;
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        MessageBox(nullptr, board[0][2] == 'X' ? L"Игрок 1 выиграл!" : L"Игрок 2 выиграл!", L"Конец игры", MB_OK);
        return;
    }
}