#include "stdafx.h" 
#include "windows.h" 
#include "conio.h" 
#include "stdlib.h" 
#include "dos.h" 
#include "string.h" 
#include "locale.h" 
#include "Matrix.h"
#include "Menu.h"
#include "Geometry.h"
#include "Text.h"
#include "About.h"


int main() {
	setlocale(0, "rus");

	hWnd = GetConsoleWindow();
	if (!hWnd) {
		printf("HWND не был получен");
		_getch();
		return 0;
	}
	hDC = GetDC(hWnd);
	if (!hDC) {
		printf("HDC не был получен");
		_getch();
		return 0;
	}

	MoveWindow(hWnd, 0, 0, 1000, 800, TRUE);
	GetClientRect(hWnd, &Rect);
	system("cls");

	char *names_of_buttons[] = { "Matrix", "Text", "Geom", "About", "Exit" };
	int tap = 0;

	Menu keys = parameters_of_buttons(names_of_buttons, 10, 10, 400, 100, 5, 0);
	keys.color_select = default_color_select;
	keys.color_not_select = default_color_not_select;
	do {
		tap = menu_item(&keys);
		switch (tap)
		{
		case 0:
			system("cls");
			MatrixMenu();
			break;
		case 1:
			system("cls");
			text();	
			system("notepad text.txt");
			break;
		case 2:
			system("cls");
			GeometryMenu();
			break;
		case 3:
			system("cls");
			aboutProgramm();
			_getch();
			
			break;
		case 4:
			exit(0);
		}

	} while (tap != 4);
	delete_struct(&keys);
	ReleaseDC(hWnd, hDC);
	return 0;
}




