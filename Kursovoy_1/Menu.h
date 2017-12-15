#pragma once
#include "stdafx.h"
#include <stdio.h> 
#include <conio.h> 
#include <math.h> 
#include <locale.h> 
#include <malloc.h>
#include "stdlib.h"

#define up 72 
#define down 80 
#define enter 13 
#define esc 27 

const int l = 0;
const int t = 1;
const int w = 2;
const int h = 3;
COLORREF default_color_select = RGB(0, 100, 200);
COLORREF default_color_not_select = RGB(0, 150, 200);

HDC hDC;
HWND hWnd;
RECT Rect;
HPEN hPen, hOldPen, lPen;
HBRUSH hBrush, hOldBrush;
HFONT hFont, hOldFont;
LOGFONT Lf = { 0 };

typedef struct {
	int x[4];
	char *text;
} button;

typedef struct {
	button *button_parameters;
	COLORREF color_select;
	COLORREF color_not_select;
	int select;
	int total;
} Menu;


void delete_struct(Menu *keys)
{
	for (int i = 0; i < keys->total; i++)
	{
		delete[]keys->button_parameters[i].text;
	}
	delete[]keys->button_parameters;
}


Menu parameters_of_buttons(char *text_buttons[], int margin_left, int margin_top, int width, int height, int quantity_of_buttons, int selected_key) {
	Menu filling_keys;
	filling_keys.total = quantity_of_buttons;
	filling_keys.select = selected_key;
	filling_keys.button_parameters = new button[quantity_of_buttons];
	for (int i = 0; i < quantity_of_buttons; i++)
	{
		filling_keys.button_parameters[i].x[l] = margin_left;
		if (i == 0)
			filling_keys.button_parameters[i].x[t] = margin_top;
		else
			filling_keys.button_parameters[i].x[t] = filling_keys.button_parameters[i - 1].x[t] + filling_keys.button_parameters[i - 1].x[h] + 10;
		filling_keys.button_parameters[i].x[h] = height;
		filling_keys.button_parameters[i].x[w] = width;
		filling_keys.button_parameters[i].text = new char[strlen(text_buttons[i] + 1)];
		strcpy(filling_keys.button_parameters[i].text, text_buttons[i]);
	}

	return filling_keys;
}

void draw_buttons(button *button_parameters, COLORREF temp, BOOL temp_func) 
{
	hPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	if (temp_func == true)
		Rectangle(hDC, button_parameters->x[l] - 3, button_parameters->x[t] - 3, button_parameters->x[l] + button_parameters->x[w] + 3, button_parameters->x[t] + button_parameters->x[h] + 3);
	else
		Rectangle(hDC, button_parameters->x[l] - 3, button_parameters->x[t] - 3, button_parameters->x[l] + button_parameters->x[w] + 3, button_parameters->x[t] + button_parameters->x[h] + 3);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	if (temp_func == true)
		Rectangle(hDC, button_parameters->x[l], button_parameters->x[t], button_parameters->x[l] + button_parameters->x[w] + 3, button_parameters->x[t] + button_parameters->x[h] + 3);
	else
		Rectangle(hDC, button_parameters->x[l], button_parameters->x[t], button_parameters->x[l] + button_parameters->x[w] + 3, button_parameters->x[t] + button_parameters->x[h] + 3);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);


	hPen = CreatePen(PS_SOLID, 4, temp);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(temp);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hFont = CreateFontIndirect(&Lf);
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	if (temp == RGB(0, 0, 0))
		SetTextColor(hDC, RGB(0, 0, 0));
	else
		SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, temp);
	if (temp_func == true)
		Rectangle(hDC, button_parameters->x[l], button_parameters->x[t], button_parameters->x[l] + button_parameters->x[w], button_parameters->x[t] + button_parameters->x[h]);
	else
		Rectangle(hDC, button_parameters->x[l], button_parameters->x[t], button_parameters->x[l] + button_parameters->x[w], button_parameters->x[t] + button_parameters->x[h]);
	TextOut(hDC, button_parameters->x[l] + button_parameters->x[w] / 6, button_parameters->x[t] + button_parameters->x[h] / 2 - 12, (LPCSTR)button_parameters->text, strlen(button_parameters->text));
	SelectObject(hDC, hOldPen);                                  
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}


void choice_figure(Menu *keys)
{
	COLORREF temp;
	BOOL func_choice;
	for (int i = 0; i < keys->total; i++)
	{
		if (keys->select == i)
		{
			temp = keys->color_select;
			func_choice = true;
		}
		else
		{
			temp = keys->color_not_select;
			func_choice = false;
		}

		draw_buttons(&keys->button_parameters[i], temp, func_choice);
	}
}

int menu_item(Menu *keys)
{
	char tap;
	do
	{
		choice_figure(keys);
		tap = _getch();
		switch (tap)
		{
		case up:
			if (keys->select == 0)
				keys->select = keys->total - 1;
			else
				keys->select--;
			system("cls");
			break;
		case down:
			if (keys->select == keys->total - 1)
				keys->select = 0;
			else
				keys->select++;
			system("cls");
		}
	} while (tap != enter && tap != esc);
	if (tap == esc)
		keys->select = 4;
	return keys->select;
}

