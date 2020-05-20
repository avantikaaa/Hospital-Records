#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"extern.h"

void date(FILE *fptr)
{
	int date[3];
	while(fread(date, sizeof(date), 1, fptr)==1)
	{
		printf("   %2d-%2d-%4d\n", date[0], date[1], date[2]);
	}
}

void print(FILE *fptr)
{
	struct patient p;
	char c;
	printf("Patient ID\tName\t\t\tAge  Sex   Height\tWeight\tBlood Group \tStatus\t\tBill\t\t\tAmt. Deposited\t\tAmt. Due\n");
	while(fread(&p, sizeof(p), 1, fptr)==1)
	{
		printf("%.0ld\t\t", p.pid);
		if(strlen(p.name)<8)
			printf("%s\t\t\t", p.name);
		else if(strlen(p.name)<16)
			printf("%s\t\t", p.name);
		else
			printf("%s\t", p.name);
		printf(" %d ", p.age);
		printf("  %c    ", p.sex);
		printf("%.2f\t", p.height);
		printf("%.2f\t", p.weight);
		printf("   %s\t\t", p.bgrp);
		if(p.stat==0)
			printf("Discharged\t");
		else if(p.stat==1)
			printf("O.P.D\t\t");
		else
			printf("Emergency\t");
		int a = p.bill/1000000000;
		if(a>0)
			printf("%lf\t", p.bill);
		else
			printf("%lf\t\t", p.bill);
		int b = p.amtdep/1000000000;
		if(b>0)
			printf("%lf\t", p.amtdep);
		else
			printf("%lf\t\t", p.amtdep);
		double due = p.bill-p.amtdep;
		if(due==0)
			printf("No dues");
		else
			printf("%lf", due);
		printf("\n");
	}
	while((c=getchar())!='\n')
		;
	printf("\nDo you want more details of all patients?(Y/N): ");
	char ans;
	scanf("%c", &ans);
	if(ans=='y' ||ans=='Y')
	{
		fseek( fptr, 0, SEEK_SET );
		while (fread(&p, sizeof(p), 1, fptr)==1)
		{
			printf("%s:\n", p.name);
			printf("   Doctor's name : %s\n", p.doc);
			printf("   Diagnosis     : %s\n", p.diag);
		}
	}
	while((c=getchar())!='\n')
		;
	printf("\nDo you want to print the date log of a patient?(Y/N): ");
	scanf("%c", &ans);

	while(ans=='y' || ans=='Y')
	{
		long p_id;
		printf("Enter patient ID: ");
		scanf("%ld", &p_id);
		fseek( fptr, 0, SEEK_SET );
		while(fread(&p, sizeof(struct patient), 1, fptr)==1)
		{
			if(p_id==p.pid)
			{
				FILE *fileptr = fopen(p.name, "rb");
				if (fileptr==NULL)
				{
					printf("No record");
					//exit(1);
					goto a;
				}
				printf("%s: ", p.name);
				date(fileptr);
				fclose(fileptr);
				break;
			}
		}
a:		printf("\nDo you want to get the log of another patient? (Y/N): ");
		scanf("%c", &ans);
	}

}
