#pragma once
#include "stdafx.h"
#include <stdio.h> 
#include <conio.h> 
#include <math.h> 
#include <locale.h> 
#include <malloc.h>
#include "stdlib.h"
#include "Menu.h"

#include <iostream> 
#include "stdlib.h" 
#include "conio.h" 
#include "string.h" 
#include "ctype.h"
#include "windows.h" 
#include<conio.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<math.h> 
#include<time.h>


HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hConsole;
COORD position;
HANDLE hConsoleOutput;


float NewBySr(float **mas, float **new_mas, int n, int m)
{
	float sum = 0;
	int kol = 0;
	float sr;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
			{
				sum += mas[i][j];
				kol++;
			}
		}
	}

	sr = sum / kol;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			new_mas[i][j] = mas[i][j] / sr;
		}
	}
	return sr;
}

void NewByMax(float **mas,float **new_mas,int n,int m,float max)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			new_mas[i][j] = mas[i][j]/max;
		}
	}
}

void NewByMin(float **mas, float **new_mas, int n, int m, float min)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			new_mas[i][j] = mas[i][j] / min;
		}
	}
}


void FormRand(float **mas, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			mas[i][j] = rand() % 100;
		}
	}
}

void PrintMatrix(float **mas, int n, int m, float max, float min)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if(mas[i][j]==max || mas[i][j]==min)
			SetConsoleTextAttribute(hout, BACKGROUND_RED);
			else SetConsoleTextAttribute(hout, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE );
			printf("%6.2f ", mas[i][j]);
		}
		printf("\n");
	}
}

void PrintMaxMin(float max, float min)
{
	printf("\n");
	printf("Минимальный элемент матрицы = %6.2f\n",min);
	printf("Максимальный элемент матрицы = %6.2f", max);
	printf("\n");
}

float FindMax(float **mas, int n, int m)
{
	float max = -10000;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (fabs(mas[i][j]) > max)
				max = fabs(mas[i][j]);
		}
	}
	return max;
}

float FindMin(float **mas, int n, int m)
{
	float min = 10000;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (fabs(mas[i][j]) < min && mas[i][j]!=0)
				min = fabs(mas[i][j]);
		}
	}
	return min;
}

void MatrixMenu()
{
	FILE *f;
	FILE *out;
	out = fopen("out_matrix.txt", "w");
	int n, m;
	float max, min;
	printf("Введите размерность матрицы:\n");
	printf("Количество строк: ");  scanf("%d",&n);
	printf("Количество столбцов: ");  scanf("%d",&m);

	float **mas;
	mas = new float*[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = new float[m];
	}
	
	float **new_mas;
	new_mas = new float*[n];
	for (int i = 0; i < n; i++)
	{
		new_mas[i] = new float[m];
	}

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
					for (int i = 0; i < n; i++)
					{
						for (int j = 0; j < m; j++)
						{
							if (feof(f))
								mas[i][j] = rand() % 10;
							else
								fscanf(f, "%f", &mas[i][j]);
						}
					}
				}
				break;
			case 1:
				system("cls");
				FormRand(mas, n, m);
				break;
			case 2:
				system("cls");
				printf("Ручное заполнение матрицы:\n");
				position.X = 5;
				position.Y = 3;

				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < m; j++)
					{
						SetConsoleCursorPosition(hout, position);
						printf("[%d][%d]= ",i+1,j+1);
					    scanf("%f", &mas[i][j]);
						position.X += 11;
					}
					position.X = 5;
					position.Y += 3;
				}_getch();
				break;
			case 3:
				system("cls");
				printf("Справка\nПо нажатию 1 клавиши, элементы матрицы считаются из файла.\n");
				printf("По нажатию 2 клавиши, элементы сформируются случайно.\n");
				printf("По нажатию 3 клавиши, вы введеты элементы вручную.\n");
				printf("По нажатию 5 клавиши, вы выйдете из программы.\n");
				_getch();
				system("cls");
				goto hop;
				break;
			case 4:
				exit(0);
			}

	system("cls");

	printf("Исходная матрица:\n\n");
	max = FindMax(mas, n, m);
	min = FindMin(mas, n, m);
	PrintMatrix(mas, n, m,max,min);
	PrintMaxMin(max, min);
	_getch();
	system("cls");
	system("color F0");

	

	char *nnames_of_buttons[] = { "Макс", "Мин", "Среднее", "Справка", "Exit" };
	 tap = 0;
	 float sr;
	 bool choose;
	 keys = parameters_of_buttons(nnames_of_buttons, 10, 10, 400, 100, 5, 0);
	keys.color_select = default_color_select;
	keys.color_not_select = default_color_not_select;
	top:  tap = menu_item(&keys);
		switch (tap)
		{
		case 0:
			system("cls");
			NewByMax(mas, new_mas, n, m, max);
			break;
		case 1:
			system("cls");
			NewByMin(mas, new_mas, n, m, min);
			break;
		case 2:
			system("cls");
			sr=NewBySr(mas, new_mas, n, m);
			choose = true;
			break;
		case 3:
			system("cls");
			printf("Справка\n");
			printf("По нажатию 1 клавиши, получим новую матрицу делением элементов старой на максимальный элемент\n");
			printf("По нажатию 2 клавиши, получим новую матрицу делением элементов старой на минимальный элемент\n");
			printf("По нажатию 3 клавиши, получим новую матрицу делением элементов старой на среднее арифметическое элементов гланой диагонали\n");
			printf("По нажатию 4 клавиши, программа будет закрыта\n");
			_getch();
			system("cls");
			goto top;
			break;
		case 4:
			exit(0);
		}


	printf("Исходная матрица:\n");
	PrintMatrix(mas, n, m,max,min);
	if (choose == true)
		printf("\nСреднее арифметическое элементов главной диагонали = %6.2f\n", sr);
	else PrintMaxMin(max, min);
	printf("\nНовая матрица:\n");
	PrintMatrix(new_mas, n, m,max,min);
	_getch();
	system("color F0");


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(out, "%6.2f ", new_mas[i][j]);
		}
		fprintf(out, "\n");
	}


	for (int i = 0; i <n; i++)
	{
		delete[]mas[i];
		delete[]new_mas[i];
	}
	
	fclose(out);
	system("cls");
}
