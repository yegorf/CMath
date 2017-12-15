#pragma once

void printText(int col_str, char **b)
{
	for (int i = 0; i < col_str; i++)
	{
		printf("%d) ",i + 1);
		puts(b[i]);	
	}
	printf("\n");
}

void Sort(int col_str, char **b)
{
	for (int k = 0; k < col_str; k++)
	{
		for (int i = 0; i < strlen(b[k]); ++i)
		{
			for (int j = strlen(b[k]) - 1; j > i; --j)
			{
				if (b[k][j] < b[k][j - 1])
				{
					char t = b[k][j - 1];
					b[k][j - 1] = b[k][j];
					b[k][j] = t;
				}
			}
		}
	}
}


void text()
{
	FILE *f;
	FILE *out;
	char a[150] = { NULL };
	int  col_str=0;
	char nameFile[100];

	printf("Введите название файла, из которого берем текст: ");
	gets_s(nameFile);

	f = fopen(nameFile, "r");
	out = fopen("out_text.txt", "w");

	fseek(f, 0L, SEEK_SET);
	while (fgets(a, 150, f)) col_str++;
	int o = 0;
	char **b = new char*[col_str];
	fseek(f, 0L, SEEK_SET);

	while (fgets(a, 150, f)) {
		b[o] = new char[strlen(a)+1];
		o++;
	}

	fseek(f, 0L, SEEK_SET);
	for (int i = 0; i < col_str; i++)
		fgets(b[i],100,f);

	printf("Исходный текст:\n");
	printText(col_str, b);
	printf("\n");

	Sort(col_str, b);

	printf("\nОтсортировано:\n");
	printText(col_str, b);
	printf("\n");

	for (int i = 0; i < col_str; i++)
		fputs(b[i], out);

	fclose(out);
	fclose(f);
	system("notepad out_text.txt");
	system("cls");
	_getch();
}