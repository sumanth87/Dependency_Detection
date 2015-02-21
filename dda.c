/*
 ============================================================================
 Name        : Dependency Detection Algorithm
 Author      : Sumanth Kumar Bandi
 Copyright   : Copyright 2014, Sumanth kumar Bandi, All rights reserved.
 Description : Program to print the dependencies
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

struct st
{
int op ;
char in_op[10];
char label[5];
char opd[3][10];
}s[MAX];

int I=0;						//register for counting no. of instructions
void split(char temp[]);
void data_dep(void);
void name_dep(void);
void control_dep(void);
FILE *wp;
int main(void)
{
	char temp[40];

	//Opening file
	FILE *fp;
	fp=fopen("code.txt","r");
	wp=fopen("output.txt","w");
	if(fp==NULL)
		{printf("error");return 0;}

//code to Read from file
	while(!feof(fp))
	{
		fgets(temp,40,fp);
		if(!strncmp(temp,"\n",1))
		{continue;}

		split(temp);
		//fscanf(fp,"%s %s",s[I].in,s[I].op);
		I++;
	}

	data_dep();
	name_dep();
	control_dep();

	printf("\nsuccess ");
	fclose(fp);
	fclose(wp);
	return 0;
}
//----------End of Main

void split(char temp[])

{
	int flag=1;

	char *store;
	int len=strlen(temp);

	for(int i=0;i<len;i++)
	{
		if(temp[i]==':')
		{flag--;}
	}
	s[I].op=0;
	printf("-%d instruction--\n\t",I+1);
	fprintf(wp,"-%d instruction--\n\t\t\t",I+1);
		store=strtok(temp,": ,   	 \n");
		do
		{
			printf("%s ",store);
			fprintf(wp,"%s ",store);
			switch(flag)
				{
				case 0:
					strcpy(s[I].label,store);
					break;
				case 1:
					strcpy(s[I].in_op,store);
					break;
				case 2:
					strcpy(s[I].opd[0],store);
					s[I].op++;
					break;
				case 3:
					strcpy(s[I].opd[1],store);
					s[I].op++;
					break;
				case 4:
					strcpy(s[I].opd[2],store);
					s[I].op++;
					break;
				}
			flag++;
		}
		while(store=strtok(NULL,": ,   	 \n"));
		printf("\n");
		fprintf(wp,"\n");

return;
}

void data_dep(void)
{
	printf("\n1. Data Dependency---------------\n");
	fprintf(wp,"\n\n1. Data Dependency------------------------------------------------\n");
	for(int i=0;i<I-1;i++)
	{
		for(int j=i+1;j<I;j++)
		{
			if(strcmp(s[i].opd[0],s[j].opd[1])==0||strcmp(s[i].opd[0],s[j].opd[2])==0)
			{
			if(s[i].op!=0)
			printf("Exists between instruction %d and %d because of register -%s- \n",i+1,j+1,s[i].opd[0]);
			fprintf(wp,"Exists between instruction %d and %d because of register -%s- \n",i+1,j+1,s[i].opd[0]);
			}
		}
	}

}

void name_dep(void)
{
	printf("\n2. Name Dependency---------------\n");
	fprintf(wp,"\n\n2. Name Dependency--------------------------------------------------------\n");
	printf("\n\t2a. Anti-Dependency---------------\n");
	fprintf(wp,"\n\t2a. Anti-Dependency---------------\n");
	for(int i=0;i<I-1;i++)
	{
		for(int j=i+1;j<I;j++)
		{
			if(strcmp(s[i].opd[1],s[j].opd[0])==0||strcmp(s[i].opd[2],s[j].opd[0])==0)
			{
				if(s[j].op!=0)
				printf("Exists between instruction %d and %d because of register -%s- \n",i+1,j+1,s[j].opd[0]);
				fprintf(wp,"Exists between instruction %d and %d because of register -%s- \n",i+1,j+1,s[j].opd[0]);
			}
		}
	}

	printf("\n\t2b. Output Dependency---------------\n");
	fprintf(wp,"\n\t2b. Output Dependency---------------\n");
		for(int i=0;i<I-1;i++)
		{
			for(int j=i+1;j<I;j++)
			{
				if(strcmp(s[i].opd[0],s[j].opd[0])==0)
				{
				if(s[j].op!=0)
				printf("Exists between instruction %d and %d because of register -%s- \n",i+1,j+1,s[j].opd[0]);
				fprintf(wp,"Exists between instruction %d and %d because of register -%s- \n",i+1,j+1,s[j].opd[0]);
				}
			}
		}

}

void control_dep(void)
{
	printf("\n3. Control Dependence-------\n");
	fprintf(wp,"\n\n3. Control Dependence-------------------------------------------------------\n");
	for(int i=0,branch=0,loop=0;i<I;i++)
	{
		int min,max=0;
		if(strcmp(s[i].in_op,"BEZ")==0||strcmp(s[i].in_op,"BNE")==0)
		{

			branch=i;
			int x=s[branch].op-1;

				for(int j=0;j<I;j++)
				{
					if(strcmp(s[j].label, s[branch].opd[x])==0)
					{
					loop=j;
					min= branch<loop?branch:loop;
					max= branch>loop?branch:loop;
					}
				}

				if(max!=0 && min!=0)
				{
				printf("Exists for branch--> %s and the instruction/'s that are dependent are:\n",s[branch].opd[x]);
				fprintf(wp,"\nExists for branch--> %s \n The instruction/'s that are dependent are from Instruction no.: %d -> %d\n ",s[branch].opd[x],min,max);
				fprintf(wp,"DependentInstructions is/are:\n");
				for(;min<max;min++)
					{

						if(strcmp(s[branch].in_op,s[min].in_op))
						{printf("%s\n",s[min].in_op);
						fprintf(wp,"%s\n",s[min].in_op);}
					}
				}


		}

	}

}
