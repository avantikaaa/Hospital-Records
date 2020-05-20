#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "extern.h"
#include"print.h"

int log_patient(FILE *fptr, int date[])		//Date file
{
	int da[3];
	while(fread(da, sizeof(da), 1, fptr)==1)
	{
		int count = 0;
		for(int i=0; i<3; i++)
			if(da[i]==date[i])
				count++;
		if(count==3)
		{
			return 1;
		}
	}
	return 0;
}

void openfile(FILE *fptr, int date[])	//Main record file.
{
	struct patient *p;
	FILE *log = fopen("log.dat", "wb+");
	while(fread(p, sizeof(struct patient), 1, fptr)==1)
	{
		FILE *date_file = fopen(p->name, "rb");
		if(date_file==NULL)
		{
			printf("Couldn't open file\n");
		}
		if(log_patient(date_file, date)==1)
		{
			fwrite(p, sizeof(struct patient), 1, log);
		}

		fclose(date_file);
	}
	fseek(log,0,SEEK_SET);
	print(log);
	fclose(log);
}
