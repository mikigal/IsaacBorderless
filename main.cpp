#include <iostream>
#include <windows.h>

int main() {
    puts("Starting game via Steam...\n");
    system("start \"\" steam://rungameid/250900");
    puts("Started game, waiting for window...");

    HWND window;
    do {
        Sleep(1000);
        window = FindWindowA(nullptr, "Binding of Isaac: Repentance");
    } while (window == nullptr);

    puts("Found window, waiting for next launch state...");

    // Wait until game fully start, just for reliability reason
    LPRECT rect;
    do {
        GetWindowRect(window, rect);
        Sleep(100);
    } while((rect->right - rect->left) < 1200);

    puts("Game started, sleeping for 1 second...");
    Sleep(1000);

    puts("Applying patch...");
    if (SetWindowLongPtrA(window, GWL_STYLE, WS_VISIBLE | WS_CLIPSIBLINGS) == 0) {
        printf("an error occurred while settings props, %d", GetLastError());
        return 1;
    }

    CloseHandle(window);
    puts("Done!");
    return 0;
}