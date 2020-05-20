#include<stdio.h>
#include<string.h>
#include<time.h>
#include"extern.h"
void edit(struct patient *ptr)
{
	char ch, c;
	
	while((c=getchar())!='\n')
		;
	printf("\nWould you like to record the date?(Y/N): ");
	scanf("%c",&c);
	if(c=='Y'||c=='y')
	{
		ptr->fpat=fopen(ptr->name,"ab");
   		time_t T=time(NULL);
    		struct tm tm=*localtime(&T);
    		int arr[3];
    		arr[0]=tm.tm_mday;
    		arr[1]=tm.tm_mon+1;
    		arr[2]=tm.tm_year+1900;
    		fwrite(arr,sizeof(arr),1,ptr->fpat);
    		fclose(ptr->fpat);
	}
	int op;
	char dummy[100];
	char dummy1[100];
	do
	{
		printf("\nWhich field of the patient do you want to edit?\n");
		printf("1.Name\n2.Age\n3.Sex\n4.Doctor\n5.Diagnosis\n6.Height\n7.Weight\n8.BloodGroup\n9.Patient's Status\n10.Bill\n11.Amount Deposited\n");
		while((c=getchar())!='\n')
			;
		printf("Enter your option: ");
	    	scanf("%d",&op);
	    	while((c=getchar())!='\n')
			;
	    	switch(op)
	    	{
	    		case 1:
                   		
                   		strcpy(dummy,ptr->name);
                   		printf("Enter the updated name:");
				gets(ptr->name);
                   
                   		rename(dummy,ptr->name);
			       break;
	    		case 2:
			       printf("Enter the updated Age:");
			       scanf("%d",&(ptr->age));
			       break;
	    		case 3:
			       printf("Enter the updated Sex:");
			       scanf("%c",&(ptr->sex));
			       break;
	    		case 4:
			       printf("Enter the updated Doctor name:");
			       gets(dummy);
			       ptr->doc[strlen(ptr->doc)]=';';
			       strcat(ptr->doc,dummy);
			       
			       break;
	    		case 5:
	    		      
			       printf("Enter the updated Diagnosis of the Patient:");
			       gets(dummy1);
			       ptr->diag[strlen(ptr->diag)]=';';
			       strcat(ptr->diag,dummy1);
			       break;
	    		case 6:
			       printf("Enter the updated Height:");
			       scanf("%f",&(ptr->height));
			       break;
	    		case 7:
			       printf("Enter the updated Weight:");
			       scanf("%f",&(ptr->weight));
			       break;
	    		case 8:
			       printf("Enter the updated BloodGroup of the Patient:");
			       gets(ptr->bgrp);
			       break;
	    		case 9:
			   	printf("Updated status of the Patient:");
			   	scanf("%d",&(ptr->stat));
			   	break;
	    		case 10:
			   	printf("Enter the updated Bill Amount:");
			   	scanf("%lf",&(ptr->bill));
			   	break;
		    	case 11:
		    		printf("Enter the amount deposited by the patient:");
		    		scanf("%lf",&(ptr->amtdep));
		    		break;
		    	default:
		    		printf("Invalid choice...Try Again!!!");
		    		break;
	    	}
	    	while((c=getchar())!='\n')
			;
	    	printf("Do you want to continue editing more information of the Patient? (Y/N): ");
	    	scanf("%c",&ch);
	}while(ch=='y' || ch=='Y');
	if(ch=='n' || ch=='N')
	{
	printf("Information of the patient has been updated successfully!!");
	}
}
