#pragma once
#include "Menu.h"

void aboutProgramm()
{
	FILE *f;
	char a[150] = { NULL };
	int  col_str = 0;
	f = fopen("about.txt", "r");

	fseek(f, 0L, SEEK_SET);
	while (fgets(a, 150, f)) col_str++;
	int o = 0;
	char **b = new char*[col_str];
	fseek(f, 0L, SEEK_SET);

	while (fgets(a, 150, f)) {
		b[o] = new char[strlen(a) + 1];
		o++;
	}

	fseek(f, 0L, SEEK_SET);
	for (int i = 0; i < col_str; i++)
		fgets(b[i], 100, f);

	printf("\t\t\t\t\tÎ ןנמדנאללו:\n\n");

	for (int i = 0; i < col_str; i++)
	{
		puts(b[i]);
	}

	fclose(f);

}	



