#include <windows.h>
#include <tchar.h>
#include <string>
#include <ctime>

// Global variables
const int TIMER_ID = 1;
const int TIMER_INTERVAL = 30000; // 30 seconds
const int RECT_WIDTH = 400;
const int RECT_HEIGHT = 200;
HWND hStaticText;

// Array of compliments
const char* compliments[] = {
    "You're doing great!",
    "Keep up the good work!",
    "You are awesome!",
    "You're a star!",
    "Fantastic job!"
};

// Function to get a random compliment
const char* getRandomCompliment() {
    int index = rand() % 5;
    return compliments[index];
}

// Window Procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            // Create a static text control to display the compliment
            hStaticText = CreateWindow(
                "STATIC", getRandomCompliment(),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                50, 50, RECT_WIDTH - 100, RECT_HEIGHT - 100,
                hwnd, (HMENU)1, NULL, NULL
            );
            // Set a timer to update the compliment every 30 seconds
            SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
            break;
        case WM_TIMER:
            if (wParam == TIMER_ID) {
                // Update the compliment
                SetWindowText(hStaticText, getRandomCompliment());
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Seed the random number generator
    srand((unsigned)time(NULL));

    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_GRAY + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Compliment Generator",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, RECT_WIDTH, RECT_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
