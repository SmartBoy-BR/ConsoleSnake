// ConsoleSnake.cpp: define o ponto de entrada para o aplicativo.
//
//#define _WIN32_WINNT 0x0500

#include <conio.h>
#include <vector>
#include <Windows.h>
#include "ConsoleSnake.h"
#include "../Headers/Game.h"

using namespace std;

int main()
{
    Game consoleSnake;
    //consoleSnake.testColors();
    consoleSnake.run();

    /*
    system("cls");
    HWND consoleWindow = GetConsoleWindow();
    long windowLong = GetWindowLong(consoleWindow, GWL_STYLE);
    //SetWindowLong(consoleWindow, GWL_STYLE, windowLong & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    setlocale(LC_ALL, "");
    SetConsoleTitleA("SmartBoy Snake Game");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO *ptrConsScreenBuffInfo = new CONSOLE_SCREEN_BUFFER_INFO();

    GetConsoleScreenBufferInfo(handle, ptrConsScreenBuffInfo);

    cout << "dwSize: X-" << ptrConsScreenBuffInfo->dwSize.X << " | Y-" << ptrConsScreenBuffInfo->dwSize.Y << endl;
    cout << "dwCursPos: X-" << ptrConsScreenBuffInfo->dwCursorPosition.X << " | Y-" << ptrConsScreenBuffInfo->dwCursorPosition.Y << endl;
    cout << "wAttrib: " << ptrConsScreenBuffInfo->wAttributes << endl;
    cout << "srWindow: Left-" << ptrConsScreenBuffInfo->srWindow.Left << " | "
         << "Top-" << ptrConsScreenBuffInfo->srWindow.Top << " | "
         << "Right-" << ptrConsScreenBuffInfo->srWindow.Right << " | "
         << "Bottom-" << ptrConsScreenBuffInfo->srWindow.Bottom << endl;
    cout << "dwMaxWindowSize: X-" << ptrConsScreenBuffInfo->dwMaximumWindowSize.X << " | Y-" << ptrConsScreenBuffInfo->dwMaximumWindowSize.Y << endl;

    // COM A JANELA ABERTA NO TAMANHO ORIGINAL
    //dwSize: X - 111 | Y - 26
    //dwCursPos : X - 0 | Y - 0
    //wAttrib : 7
    //srWindow : Left - 0 | Top - 0 | Right - 110 | Bottom - 25
    //dwMaxWindowSize : X - 111 | Y - 26

    SMALL_RECT smallRect;
    COORD consoleSize;

    consoleSize.X = 120; consoleSize.Y = 36;

    smallRect.Top = smallRect.Left = 0;
    smallRect.Right = 119; smallRect.Bottom = 35;

    system("Pause");

    //SetConsoleWindowInfo(handle, true, &sr);
    //SetConsoleScreenBufferSize(handle, consoleSize);
    
    ptrConsScreenBuffInfo->dwSize.X = ptrConsScreenBuffInfo->dwMaximumWindowSize.X = 50;
    ptrConsScreenBuffInfo->dwSize.Y = ptrConsScreenBuffInfo->dwMaximumWindowSize.Y = 16;
    ptrConsScreenBuffInfo->srWindow.Right = ptrConsScreenBuffInfo->dwSize.X - 1;
    ptrConsScreenBuffInfo->srWindow.Bottom = ptrConsScreenBuffInfo->dwSize.Y - 1;

    //SetConsoleScreenBufferInfoEx(handle, ptrConsScreenBuffInfoEx);
    SetConsoleWindowInfo(handle, true, &smallRect);
    SetConsoleScreenBufferSize(handle, consoleSize);

    system("Pause");

    ptrConsScreenBuffInfo->dwSize.X = ptrConsScreenBuffInfo->dwMaximumWindowSize.X = 120;
    ptrConsScreenBuffInfo->dwSize.Y = ptrConsScreenBuffInfo->dwMaximumWindowSize.Y = 36;
    ptrConsScreenBuffInfo->srWindow.Right = ptrConsScreenBuffInfo->dwSize.X - 1;
    ptrConsScreenBuffInfo->srWindow.Bottom = ptrConsScreenBuffInfo->dwSize.Y - 1;

    consoleSize.X = 50; consoleSize.Y = 25;
    smallRect.Right = consoleSize.X - 1;
    smallRect.Bottom = consoleSize.Y - 1;

    SetConsoleWindowInfo(handle, true, &smallRect);
    SetConsoleScreenBufferSize(handle, consoleSize);
    
    // COM A JANELA ABERTA APÓS MODIFICAR O TAMANHO COM O MOUSE
    //dwSize : X - 99 | Y - 24
    //dwCursPos : X - 0 | Y - 0
    //wAttrib : 7
    //srWindow : Left - 0 | Top - 0 | Right - 98 | Bottom - 23
    //dwMaxWindowSize : X - 99 | Y - 24
    */

    vector<string> msg{ "Hello", "C++", "World", "from", "VS Code", "and the C++ extension!" };
    /*
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    Test test;
    cout << test.getMsg() << endl;

    char charValue;

    do
    {
        charValue = _getch();
        cout << charValue << " ";
        //system("color 18");
    } while (charValue != ' ');

    cout << endl;
    system("Pause");
    system("cls");
    SetConsoleTitleA("SmartBoy Snake Game");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord = { 0, 0 };
    CONSOLE_CURSOR_INFO *ccInfo = new CONSOLE_CURSOR_INFO();
    GetConsoleCursorInfo(handle, ccInfo);
    ccInfo->bVisible = false;
    SetConsoleCursorInfo(handle, ccInfo);
    for (int i = 0; i < 256; i++)
    {
        //Sleep(500);
        //cursorCoord.X = cursorCoord.Y = 0;
        //SetConsoleCursorPosition(handle, cursorCoord);
        SetConsoleTextAttribute(handle, i);
        cout << "Cor " << i;
    }
    cout << endl;
    SetConsoleTextAttribute(handle, 15);

    ccInfo->bVisible = true;
    SetConsoleCursorInfo(handle, ccInfo);

    //SetWindowLong(consoleWindow, GWL_STYLE, windowLong);
    */
    return 0;
}
