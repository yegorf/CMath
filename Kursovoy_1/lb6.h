#pragma once
#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "dos.h"
#include "string.h"
#include "locale.h"

typedef struct {
	float A;
	float B;
	float C;
	float x1;
	float x2;
	float y1;
	float y2;
	int col = 0;
} Koef;

//Расчетная часть
int lol(Koef *abc, int n, int z, int r)
{
	int kol = 0;

	for (int i = 0; i < n; i++)
	{
		abc[i].x1 = z;
		abc[i].x2 = r;

		scanf("%f %f %f", &abc[i].A, &abc[i].B, &abc[i].C);
	}

	for (int l = 0; l < n; l++)
	{
		for (int k = l + 1; k < n; k++)
		{
			float d = abc[l].A*abc[k].B - abc[k].A*abc[l].B;
			printf("%4.2f ", d);
			if (d != 0)
			{
				abc[l].col++;
				abc[k].col++;
			}
		}
	}
	kol = kol / 2;

	for (int i = 0; i < n; i++)
	{
		printf("\nКоличество пересечений %d-ой прямой=%d", i + 1, abc[i].col);
		kol = kol + abc[i].col;
	}
	kol = kol / 2;

	printf("\nОбщее количество пересечений=%d", kol);

	int min = 1000;
	for (int i = 0; i < n; i++)
	{
		if (abc[i].col < min)
			min = abc[i].col;
	}

	for (int i = 0; i < n; i++)
	{
		if (abc[i].col == min)
		{
			printf("\nНомер прямой с минимальным количеством пересечений: %d\n", i + 1);
		}
	}

	//Нахождение координат точек для каждой прямой
	printf("%4.2f %4.2f %4.2f\n", abc[0].A, abc[0].B, abc[0].C);
	for (int i = 0; i < n; i++)
	{
		abc[i].y1 = -((abc[i].C - abc[i].A*abc[i].x1) / abc[i].B);
		abc[i].y2 = -((abc[i].C - abc[i].A*abc[i].x2) / abc[i].B);
	}

	// Их вывод
	for (int i = 0; i < n; i++)
	{
		printf("\nКоординаты точек, через которые проходит %d-ая прямая:\n 1 точка: (%6.2f, %6.2f) 2 точка:(%6.2f, %6.2f)", i + 1, abc[i].x1, abc[i].y1, abc[i].x2, abc[i].y2);
	}

	getchar();
	getchar();
	return 0;
}

#define Margin 15.0

HWND hWnd;
HDC hDC;
RECT Rect;
HPEN hPen, hOldPen;
HBRUSH hBrush, hOldBrush;
int m = 2;


void scale(Koef *abc, int n, float *scale_x, float *scale_y, float *max_x, float *max_y, float *min_x, float *min_y) {

	*max_x = abc->x2;
	*min_x = abc->x1;
	*max_y = *min_y = abc->y1;
	for (int i = 1; i < n; i++) {
		if (abc[i].y1 >= *max_y)
			*max_y = abc[i].y1;
		if (abc[i].y1 <= *min_y)
			*min_y = abc[i].y1;
		if (abc[i].y2 >= *max_y)
			*max_y = abc[i].y2;
		if (abc[i].y2 <= *min_y)
			*min_y = abc[i].y2;
	}
	*scale_x = (Rect.right - 2 * Margin) / ((float)*max_x - (float)*min_x);
	*scale_y = (Rect.bottom - 2 * Margin) / ((float)*max_y - (float)*min_y);
}

void clear() {
	system("cls");
	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
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

void printpoints(Koef *abc, float scale_x, float scale_y, float axis_x, float axis_y, int n) {
	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	char *text = new char[100];
	float plus_x, plus_y;
	for (int i = 0; i < n; i++) {
		float x = axis_y + (abc[i].x1 * scale_x),
			y = axis_x - (abc[i].y1 * scale_y);
		MoveToEx(hDC, x, y, NULL);
		x = axis_y + (abc[i].x2 * scale_x),
			y = axis_x - (abc[i].y2 * scale_y);
		LineTo(hDC, x, y);
	}
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}


int main() {
	setlocale(0, "rus");
	int n;
	float scale_x, scale_y;
	float max_x, max_y, min_x, min_y;
	float axis_x, axis_y;
	int z, r, temp;
	z = -10;
	r = 10;
	printf("Введте количество прямых:\n");
	scanf("%d", &n);
	Koef abc[10];

	lol(&abc[0], n, z, r);
	_getch();
	hWnd = GetConsoleWindow();
	if (!hWnd) {
		printf("hWnd неоч");
		_getch();
		return -1;
	}
	hDC = GetDC(hWnd);
	if (!hWnd) {
		printf("hDC неоч");
		_getch();
		return -2;
	}

	MoveWindow(hWnd, 0, 0, 1000, 800, TRUE);
	GetClientRect(hWnd, &Rect);
	clear();
	scale(&abc[0], n, &scale_x, &scale_y, &max_x, &max_y, &min_x, &min_y);
	for (int i = 0; i < n; i++)
	{
		printf("\nКоординаты точек, через которые проходит %d-ая прямая:\n 1 точка: (%6.2f, %6.2f) 2 точка:(%6.2f, %6.2f)", i + 1, abc[i].x1, abc[i].y1, abc[i].x2, abc[i].y2);
	}

	for (int i = 0; i < n; i++)
	{
		printf("\nКоэффициенты %d-ой прямой: %6.2f %6.2f %6.2f", i + 1, abc[i].A, abc[i].B, abc[i].C);
	}
	axis(scale_x, scale_y, &axis_x, &axis_y, max_x, max_y, min_x, min_y);
	/*printpoints(&abc[0], scale_x, scale_y, axis_x, axis_y, n);*/
	ReleaseDC(hWnd, hDC);
	_getch();
	return 0;

}