#include<stdio.h>
#include "extern.h"
void delete(long int pid)
{
    	struct patient input,del;
    	FILE *fptr,*fptr1;
    	fptr = fopen("records.dat","rb");
    	fptr1 = fopen("record1.dat","wb");
    	while(fread(&input, sizeof(struct patient), 1, fptr))
    	{
        	if(input.pid!=pid)
        	{
            		fwrite(&input ,sizeof(struct patient), 1, fptr1);
        	}
        	else
        	{
        		del=input;
        	}
    	}
    	fclose(fptr);
    	fclose(fptr1);
    	remove(del.name);
    	remove("records.dat");
    	rename("record1.dat","records.dat");
    	printf("\nPatient record deleted.\n");
}
