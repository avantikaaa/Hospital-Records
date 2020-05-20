#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add_patient.h"
#include "search.h"
#include "edit.h"
#include "printname_pid.h"
#include "doctor.h"
#include "delete.h"
#include "doctor.h"
#include "print.h"
#include "diagnosis.h"
#include "bgrp.h"
#include "log.h"
int main()
{
	int option, pid=436, id;
	char yn;
	char c;
	int flag=0;
	
	printf("WELCOME TO WE-CARE\n");
menu:	printf("\nMain menu:\n");
	printf("1. Display patient records\n");
	printf("2. Add patient record\n");
	printf("3. Search a patient's records in the database\n");  //search
	printf("4. Edit patient records\n");
	printf("5. Delete patient records\n");
	printf("6. Display patients of a particular blood group\n");
	printf("7. Display patients treated by a particular doctor\n");
	printf("8. Display patients of a particular diagnosis\n");
	printf("9. Display patients who visited on a particular day\n");
	printf("0. Quit the program\n");
	printf("Enter option number: ");
	scanf("%d", &option);
	printf("\n");
//Display patient records
	if(option==1)
	{
		FILE * fptr;
		fptr= fopen("records.dat", "rb");
		if(fptr==NULL)
			printf("No records to be displayed\n");
		else
		{
			print(fptr);
			fclose(fptr);
		}
	}
	
//Add patient records
	else if(option==2)
	{
		struct patient p;
add:		add_patient(&p, pid);
		pid++;
		while((c=getchar())!='\n')
			;
		printf("\nDo you want to add another patient record?(Y/N): ");
		scanf("%c", &yn);
		if(yn == 'Y' || yn == 'y')
		{
			goto add;
		}
		printf("\n");
	}
	
//Search a patient's records in the database
	else if(option==3)
	{
		search(fopen("records.dat","rb"));
	}
	
//Edit patient records
	else if(option==4)
	{
		FILE* fptr;
        	fptr=fopen("records.dat","rb");
        	printf("Enter patient id:");
        	scanf("%d", &id);
        	struct patient pat,pedit;
        	while(fread(&pedit,sizeof(pedit),1,fptr))
        	{
            		if(pedit.pid==id)
            		{
                		break;
            		}
        	}
        	edit(&pedit);
       
	        FILE* fnew=fopen("edit.dat","wb");
        	fseek(fptr,0,SEEK_SET);
        	while(fread(&pat,sizeof(pat),1,fptr))
        	{
        		if(pat.pid!=id)
            		{
                		fwrite(&pat,sizeof(pat),1,fnew);
            		}
            		else
            		{
                		fwrite(&pedit,sizeof(pedit),1,fnew);
            		}
        	}
        	fclose(fnew);
        	fclose(fptr);
        	remove("records.dat");
        	rename("edit.dat","records.dat");
	}
	
//Delete patient records
	else if(option==5)
	{
		char s[100];
		char ch[100];
		flag=0;
		struct patient pat;
		FILE *fptr=fopen("records.dat","rb");
		FILE* fnew=fopen("search.dat","wb");
del:		fseek(fptr,0,SEEK_SET);
        	printf("Enter the name of the patient whose record is to be deleted : ");
            	scanf("%s",s);
            	strlower(s,s);
            	while(fread(&pat,sizeof(pat),1,fptr))
            	{
                	strlower(pat.name,ch);
                	if(strstr(ch,s))
                	{
                    		fwrite(&pat,sizeof(pat),1,fnew);
                    		flag=1;
                	}
		}
		if(flag==0)
		{
			while((c=getchar())!='\n')
				;
			printf("\nPatient not found. Try again!\n");
			printf("Do you want to go to main menu?(Y/N): ");
			scanf("%c", &yn);
			if(yn=='Y' || yn=='y')
			{
				goto menu;
			}
			goto del;
		}
        	fclose(fptr);
        	fclose(fnew);
        	fnew=fopen("search.dat","rb");
        	printname_pid(fnew);
        	fclose(fnew);
        	while((c=getchar())!='\n')
			;
        	printf("\nEnter the patient ID of the patient whose record is to be deleted : ");
        	scanf("%d",&id);
        	delete(id);
	}
	
//Display patients of a particular blood group
	else if(option == 6)
	{
		char bgrp[10];
		while((c=getchar())!='\n')
			;
		printf("Enter blood group: ");
		scanf("%s", bgrp);
		printf("\n");
		FILE *fptr = fopen("records.dat","rb");
		bloodgroup(fptr, bgrp);
		fclose(fptr);
	}
	
//Display patients treated by a particular doctor
	else if(option == 7)
	{
		char doc[100];
		while((c=getchar())!='\n')
			;
again:		printf("Enter doctor's name: ");
		gets(doc);
		
		if(doctor(fopen("records.dat", "rb"), doc)==0)
		{
			goto again;
		}
		
	}
	
//Display patients of a particular diagnosis
	else if(option == 8)
	{
		char diag[100];
		while((c=getchar())!='\n')
			;
diag:		printf("Enter diagnosis: ");
		gets(diag);
		FILE* fptr=fopen("records.dat","rb");
		if(diagnosis(fptr, diag)==0)
		{
			goto diag;
		}
		fclose(fptr);
	}
	
//Display patients who visited on a particular day
	else if(option == 9)
	{
		int d, m, y;
		printf("Enter date(dd): "); scanf("%d", &d);
		printf("Enter month(mm): "); scanf("%d", &m);
		printf("Enter year(yyyy): "); scanf("%d", &y);
		FILE* fptr=fopen("records.dat", "rb");
		int date[3]={d, m, y};
		openfile(fptr, date);
		fclose(fptr);
	}
	else if(option==0)
	{
		printf("\nThank you for using our services.");
		exit(0);
	}
	else
	{
		printf("Enter valid option\n");
		goto menu;
	}
	while((c=getchar())!='\n')
			;
	printf("\nDo you want to perform any other operation?(Y/N): ");
	scanf("%c", &yn);
	if(yn=='Y' || yn=='y')
	{
		goto menu;
	}
	else
	{
		printf("\nThank you for using our services.");
		exit(0);
	}
	return 0;
}
