#pragma once

#include <windows.h>
#include <iostream>
#include <locale>

using namespace std;


// for dll building.
#ifdef BUILD
__declspec(dllexport) typedef struct keyState {
    bool pressed;
    bool toggled;
} keyState;

class __declspec(dllexport) Console {
    private:
        CONSOLE_SCREEN_BUFFER_INFO csbinfo;
    public:
        HANDLE h;
        int initColor;
        int initFore, initBack;
        Console();
        void writeChar(string s, COORD p, unsigned long* written);
        void writeCharColor(string s, COORD p, int fg, int bg);
        void fill(char c);
        void cls();
        void setColor(int bg, int fg);
        void resetColor();
        void setConsCursorPos(COORD p);
        keyState getKey(int vk_code);

        int xSize, ySize;
};

Console::Console() {
    h = GetStdHandle(-11);
    GetConsoleScreenBufferInfo(h, &csbinfo);
    xSize = csbinfo.srWindow.Right - csbinfo.srWindow.Left + 1;
    ySize = csbinfo.srWindow.Bottom - csbinfo.srWindow.Top + 1;
    initColor = csbinfo.wAttributes;
    initBack = initColor / 16;
    initFore = initColor % 16;
}

__declspec(dllexport) void __cdecl Console::writeChar(string s, COORD p, unsigned long* written) {
    WriteConsoleOutputCharacterA(h, s.c_str(), s.size(), p, written);
}
__declspec(dllexport) void __cdecl Console::writeCharColor(string s, COORD p, int fg, int bg) {
    unsigned long int writ;
    WriteConsoleOutputCharacterA(h, s.c_str(), s.size(), p, &writ);
    WORD attr[1] = {static_cast<WORD>(fg + bg * 16)};
    for (int i = 0; i < s.size(); i++) {
        WriteConsoleOutputAttribute(h, attr, 1, p, &writ);
        p.X++;
    }
}
__declspec(dllexport) void __cdecl Console::fill(char c) {
    COORD p = {0, 0};
    unsigned long k;
    for (int i = 0; i < ySize; i++) {
        p.Y = i;
        FillConsoleOutputCharacter(h, c, xSize, p, &k);
    }
}
// system("cls"); but better
__declspec(dllexport) void __cdecl Console::cls() {
    fill(' ');
    unsigned long writ;
    WORD attr[1] = {static_cast<WORD>(initFore + initBack * 16)};
    for (short i = 0; i < ySize; i++) {
        FillConsoleOutputAttribute(h, initBack * 16 + initFore, xSize, {0, i}, &writ);
    }
}
__declspec(dllexport) void __cdecl Console::setColor(int fg, int bg = 0) {
    SetConsoleTextAttribute(h, bg * 16 + fg);
}
__declspec(dllexport) void __cdecl Console::resetColor() {
    setColor(initFore, initBack);
}
__declspec(dllexport) void __cdecl Console::setConsCursorPos(COORD p) {
    SetConsoleCursorPosition(h, p);
}
__declspec(dllexport) keyState Console::getKey(int vk_code) {
    keyState ret;
    short k = GetKeyState(vk_code);
    ret.pressed = (int)((k & -128) != 0);
    ret.toggled = k & 1;
    return ret;
}

__declspec(dllexport) int __cdecl FGToBG(const int fg);

extern __declspec(dllexport) const int BLACK;
extern __declspec(dllexport) const int BLUE;
extern __declspec(dllexport) const int GREEN;
extern __declspec(dllexport) const int CYAN;
extern __declspec(dllexport) const int RED;
extern __declspec(dllexport) const int MAGENTA;
extern __declspec(dllexport) const int BROWN;
extern __declspec(dllexport) const int LIGHTGRAY;
extern __declspec(dllexport) const int GRAY;
extern __declspec(dllexport) const int LIGHTBLUE;
extern __declspec(dllexport) const int LIGHTGREEN;
extern __declspec(dllexport) const int LIGHTCYAN;
extern __declspec(dllexport) const int LIGHTRED;
extern __declspec(dllexport) const int LIGHTMAGENTA;
extern __declspec(dllexport) const int YELLOW;
extern __declspec(dllexport) const int WHITE;

extern __declspec(dllexport) const int WITAJ_PRZYBYSZU;

// for including
#else

__declspec(dllimport) typedef struct keyState {
    bool pressed;
    bool toggled;
} keyState;

class __declspec(dllimport) Console {
    private:
        CONSOLE_SCREEN_BUFFER_INFO csbinfo;
    public:
        HANDLE h;
        int initColor;
        int initFore, initBack;
        __declspec(dllimport) Console();
        __declspec(dllimport) void writeChar(string s, COORD p, unsigned long* written);
        __declspec(dllimport) void writeCharColor(string s, COORD p, int fg, int bg);
        __declspec(dllimport) void fill(char c);
        __declspec(dllimport) void cls();
        __declspec(dllimport) void setColor(int fg, int bg);
        __declspec(dllimport) void resetColor();
        __declspec(dllimport) void setConsCursorPos(COORD p);
        __declspec(dllimport) keyState getKey(int vk_code);

        int xSize, ySize;
};

__declspec(dllimport) int __cdecl FGToBG(const int fg);

extern __declspec(dllimport) const int BLACK;
extern __declspec(dllimport) const int BLUE;
extern __declspec(dllimport) const int GREEN;
extern __declspec(dllimport) const int CYAN;
extern __declspec(dllimport) const int RED;
extern __declspec(dllimport) const int MAGENTA;
extern __declspec(dllimport) const int BROWN;
extern __declspec(dllimport) const int LIGHTGRAY;
extern __declspec(dllimport) const int GRAY;
extern __declspec(dllimport) const int LIGHTBLUE;
extern __declspec(dllimport) const int LIGHTGREEN;
extern __declspec(dllimport) const int LIGHTCYAN;
extern __declspec(dllimport) const int LIGHTRED;
extern __declspec(dllimport) const int LIGHTMAGENTA;
extern __declspec(dllimport) const int YELLOW;
extern __declspec(dllimport) const int WHITE;

extern __declspec(dllimport) const int WITAJ_PRZYBYSZU;
#endif