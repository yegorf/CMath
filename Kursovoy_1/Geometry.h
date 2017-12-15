#pragma once
#include "stdafx.h" 
#include "windows.h" 
#include "conio.h" 
#include "stdlib.h" 
#include "dos.h" 
#include "string.h" 
#include "locale.h" 
#include "Menu.h"
#include "stdio.h"
#include "math.h"
int size = 52;
#define Margin 15.0

void scale(int n, float *scale_x, float *scale_y, float *max_x, float *max_y, float *min_x, float *min_y) {

	*max_x = 12;
	*min_x = -12;
	*max_y = 20;
	*min_y = -20;

	*scale_x = (Rect.right-size - 2 * Margin) / ((float)*max_x - (float)*min_x);
	*scale_y = (Rect.bottom - 2 * Margin) / ((float)*max_y - (float)*min_y);
}

int odd;
void strip(float MoveToEx_x, float MoveToEx_y, float Line_x, float Line_y, float TextOut_x, float TextOut_y, int coordinates, char *arg) {
	char *text = new char[10];
	int z;
	MoveToEx(hDC, MoveToEx_x, MoveToEx_y, NULL);
	LineTo(hDC, Line_x, Line_y);
	if (odd >= 1) {
		sprintf(text, arg, coordinates);
		z = strlen(text);
		TextOut(hDC, TextOut_x, TextOut_y, (LPSTR)text, z);
	}
	delete text;
}

void get_axis(float scale_x, float scale_y, float *axis_x, float *axis_y, float max_x, float max_y, float min_x, float min_y)
{
	*axis_x = Rect.bottom - fabs(min_y)*scale_y - Margin;
	*axis_y = fabs(min_x)*scale_x + Margin;
}

void axis(float scale_x, float scale_y, float *axis_x, float *axis_y, float max_x, float max_y, float min_x, float min_y) {
	*axis_x = Rect.bottom - fabs(min_y)*scale_y - Margin;
	*axis_y = fabs(min_x)*scale_x + Margin;

	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	MoveToEx(hDC, Margin, *axis_x, NULL);
	LineTo(hDC, Rect.right - Margin, *axis_x);
	MoveToEx(hDC, *axis_y, Margin, NULL);
	LineTo(hDC, *axis_y, Rect.bottom - Margin);

	odd = 0;
	float i = *axis_y;
	float j = i;
	int flag_1 = 0, flag_2 = 0;
	int coordinates = 0;

	while (flag_1 == 0 || flag_2 == 0) {
		if (i <= Rect.right - Margin / 2) {
			strip(i, *axis_x - 5.0, i, *axis_x + 5.0, i - 7.0, *axis_x - 20.0, coordinates, "%d");
			i += scale_x;
		}
		else flag_1 = 1;
		if (j >= Margin / 2) {
			strip(j, *axis_x - 5.0, j, *axis_x + 5.0, j - 10.0, *axis_x + 10.0, coordinates*-1, "%d");
			j -= scale_x;
		}
		else flag_2 = 1;
		coordinates++;
		odd++;
	}
	odd = 0;
	i = *axis_x;
	j = i;
	flag_1 = 0, flag_2 = 0;
	coordinates = 0;
	while (flag_1 == 0 || flag_2 == 0) {
		if (i >= Margin / 2) {
			strip(*axis_y + 5.0, i, *axis_y - 5.0, i, *axis_y - 25.0, i - 7.0, coordinates, "%d");
			i -= scale_y * 2;
		}
		else flag_1 = 1;
		if (j <= Rect.bottom - Margin / 2) {

			strip(*axis_y + 5.0, j, *axis_y - 5.0, j, *axis_y + 20.0, j - 7.0, coordinates*-1.0, "%d");
			j += scale_y * 2;
		}
		else flag_2 = 1;
		coordinates++;
		odd++;
	}
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}


struct geom
{
	float x;
	float y;
	float rst;
	int check;
};

void FormRandP(geom *mas,int n)
{
	for (int i = 0; i < n; i++)
	{
		mas[i].x = rand() % 20 + (-10);
		mas[i].y = rand() % 10;
	}
}

void PrintCoordinats(geom *mas, int n, float r, float k)
{
	printf("Радиус окружности = %6.2f\n", r);
	printf("Коэффициент наклона прямой = %6.2f\n\n", k);
	for (int i = 0; i < n; i++)
	{
		printf("Координаты %d-ой точки: (%6.2f, %6.2f) \n", i + 1,mas[i].x,mas[i].y);
	}
}

void Check(geom *mas, int n,float r,float k,float A,float B,float C)
{
	float d;
	printf("\nПроверка\n\n");
	for (int i = 0; i < n; i++)
	{
		d = A*mas[i].x + B*mas[i].y + C;
		mas[i].rst = sqrt(pow(mas[i].x, 2) + pow(mas[i].y, 2));

			if (mas[i].rst <= r && d <= 0)
			{
				if (mas[i].rst==r)
				{
					printf("%d-ая точка лежит на границе заданной области!\n\n", i + 1);
					mas[i].check = 1;
				}
				else {
					printf("%d-ая точка попадает в заданную область!\n\n", i + 1);
					mas[i].check = 2;
				}
			} 
			else {
				printf("%d-ая точка НЕ попадает в заданную область!\n\n", i + 1);
				mas[i].check = 3;
			}
	}
}

void Printpoints(float R,geom *mas, float scale_x, float scale_y, float axis_x, float axis_y, int n) {
	hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	lPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	
	float x, y;
	for (int i = 0; i < n; i++)
	{
		x = axis_y + (mas[i].x * scale_x);
		y = axis_x - (mas[i].y * (scale_y * 2));
		if (mas[i].check == 1 || mas[i].check == 2)
		{
			hOldPen = (HPEN)SelectObject(hDC, lPen);
			Ellipse(hDC, x - 3, y + 3, x + 3, y - 3);
		}
		else 
		{ 
		hOldPen = (HPEN)SelectObject(hDC, hPen); 
		Ellipse(hDC, x - 2, y + 2, x + 2, y - 2);
		}
	}

	SelectObject(hDC, hOldPen);
	DeleteObject(lPen);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void Line(float x1,float y1, float x2, float y2, float scale_x, float scale_y, float axis_x, float axis_y)
{
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);

	float x11 = axis_y + (x1 * scale_x);
	float y11 = axis_x - (y1 * (scale_y * 2));
	float x22 = axis_y + (x2 * scale_x);
	float y22 = axis_x - (y2 * (scale_y * 2));

	MoveToEx(hDC, x11, y11, NULL);
	LineTo(hDC, x22, y22);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void Circle(float axis_x, float axis_y,float R, float scale_x)
{
	hBrush = CreateSolidBrush(RGB(255,255,255));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	float x, y;
	x = axis_y;
	y = axis_x;
	R *= scale_x;
	Ellipse(hDC, x - R, y + R, x + R, y - R);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}


void GeometryMenu()
{
	FILE *f;
	int n;
	float R, k;
	float A, B, C;
	printf("Введите Радиус окружности: ");
	scanf("%f", &R);
	printf("\nВведите Коэффициент наклона прямой: ");
	scanf("%f", &k);
	printf("\nВведите количество точек: ");
	scanf("%d", &n);

	geom *mas;
	mas = new geom[n];

	char *names_of_buttons[] = { "Из файла", "Рандомно", "Вручную", "Справка", "Выйти" };
	int tap = 0;
	char ch = _getch();
	Menu keys = parameters_of_buttons(names_of_buttons, 10, 10, 400, 100, 5, 0);
	keys.color_select = default_color_select;
	keys.color_not_select = default_color_not_select;
	int temp;
hop:tap = menu_item(&keys);
	switch (tap)
	{
	case 0:
		system("cls");
		if (!(f = fopen("matrix.txt", "r"))) { printf("Error!\n"); _getch(); }
		else {
				f = fopen("geom.txt", "r");

				for (int i = 0; i < n; i++)
				{
					if (feof(f))
					{
						mas[i].x = rand() % 10;
						mas[i].y = rand() % 10;
					}
					else fscanf(f, "%f %f", &mas[i].x, &mas[i].y);		
				}
		}
		break;
	case 1:
		system("cls");
		FormRandP(mas, n);
		break;
	case 2:
		system("cls");
			for (int i = 0; i < n; i++)
			{
				printf("%d-ая точка: \n", i + 1);
					printf("x = ");
					scanf("%f",&mas[i].x);
					printf("y = ");
					scanf("%f",&mas[i].y);
			}
		break;
	case 3:
		system("cls");
		printf("Справка\nПо нажатию 1 клавиши, координаты точек считаются из файла.\n");
		printf("По нажатию 2 клавиши, координаты точек сформируются случайно.\n");
		printf("По нажатию 3 клавиши, вы введете координаты точек вручную.\n");
		printf("По нажатию 5 клавиши, вы выйдете из программы.\n");
		_getch();
		system("cls");
		goto hop;
		break;
	case 4:
		exit(0);
	}

	system("cls");

	PrintCoordinats(mas,n,R,k);

	float x1=-10, x2=10;
	float y1, y2;
	float d;

	y1 = k*x1;
	y2 = k*x2;

	A = y1 - y2;
	B = x2 - x1;
	C = x1*y2 - x2*y1; 

	Check(mas, n, R, k,A,B,C);

	_getch();
	system("cls");
	float scale_x, scale_y;
	float max_x, max_y, min_x, min_y;
	float axis_x, axis_y;

	scale(n, &scale_x, &scale_y, &max_x, &max_y, &min_x, &min_y);
	get_axis(scale_x, scale_y, &axis_x, &axis_y, max_x, max_y, min_x, min_y);
	Circle(axis_x, axis_y, R,scale_x);
	Line(x1, y1, x2, y2, scale_x, scale_y,axis_x,axis_y); 
	axis(scale_x, scale_y, &axis_x, &axis_y, max_x, max_y, min_x, min_y);
	Printpoints(R,&mas[0], scale_x, scale_y, axis_x, axis_y, n);
	
	char v[18];
	int g = 30;
	char q[20] = "Координаты точек:";
	TextOut(hDC, Rect.left+5, Rect.top + 10, (LPCTSTR)q, 20);
	for (int i = 0; i < n; i++)
	{
		sprintf(v, "%d)(%6.2f,%6.2f)",i+1,mas[i].x,mas[i].y);
		TextOut(hDC, Rect.left, Rect.top+g, (LPCTSTR)v, 18);
		g += 15;
	}

	delete[]mas;
	_getch();
	system("cls");
}


