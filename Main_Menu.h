#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
using namespace std;

// Function to hide console cursor during main menu
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Moves cursor coordinates for title art
void gotoxy3(int x, int y) {
    if (x >= 0 && y >= 0) {
        COORD kursor;
        kursor.X = x;
        kursor.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
    }
}

// Creates main menu for program
void MainMenu()
{
    char Button;

    while (1)
    {
        // Clear console for every loop
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Hide console cursor
        ShowConsoleCursor(false);

        // Displays title of program in ASCII
        SetConsoleTextAttribute(hConsole, 3);
        cout << R"(
            $$$$$$$\  $$\                                               $$$$$$$$\                            
            $$  __$$\ \__|                                              \__$$  __|                           
            $$ |  $$ |$$\ $$$$$$$\   $$$$$$\   $$$$$$\  $$\   $$\          $$ | $$$$$$\   $$$$$$\   $$$$$$\  
            $$$$$$$\ |$$ |$$  __$$\  \____$$\ $$  __$$\ $$ |  $$ |         $$ |$$  __$$\ $$  __$$\ $$  __$$\ 
            $$  __$$\ $$ |$$ |  $$ | $$$$$$$ |$$ |  \__|$$ |  $$ |         $$ |$$ |  \__|$$$$$$$$ |$$$$$$$$ |
            $$ |  $$ |$$ |$$ |  $$ |$$  __$$ |$$ |      $$ |  $$ |         $$ |$$ |      $$   ____|$$   ____|
            $$$$$$$  |$$ |$$ |  $$ |\$$$$$$$ |$$ |      \$$$$$$$ |         $$ |$$ |      \$$$$$$$\ \$$$$$$$\ 
            \_______/ \__|\__|  \__| \_______|\__|       \____$$ |         \__|\__|       \_______| \_______|
                                                        $$\   $$ |                                           
                                                       \$$$$$$  |                                           
                                                        \______/                                                   

                       )" << endl;

        // Colored Start Instructions
        gotoxy3(50, 15);
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Press '";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "Q"; // Tells user to press 'Q' or 'q' to start
        SetConsoleTextAttribute(hConsole, 15);
        cout << "' to start" << endl;
        gotoxy3(45, 17);
        cout << "Press '";
        SetConsoleTextAttribute(hConsole, 14);
        cout << "ESC"; // Tells user 'ESC' to exit
        SetConsoleTextAttribute(hConsole, 15);
        cout << "' to exit program";

        gotoxy3(34, 20);
        cout << "PLEASE MAXIMIZE CONSOLE WINDOW FOR BEST EXPERIENCE" << endl;

        if (_kbhit())
        {
            Button = _getch();
            // Checks if 'Q' or 'q' is pressed to start
            if (Button == 'q' || Button == 'Q')
            {
                break;
            }
            // Checks if 'ESC' is pressed to end
            if (Button == 27)
            {
                system("cls");
                cout << "You have exited the program successfully!" << endl;
                exit(EXIT_SUCCESS);
            }
        }
        // 300ms delay for loop
        Sleep(300);
    }
}
