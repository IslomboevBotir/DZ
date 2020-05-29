#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define Length 200

typedef struct st
{
	char Number[Length];
	char Name[Length];
	char Surname[Length];
	char Patronymic[Length];
	char Faculty[Length];
	char Speciality[Length];
	struct st *next;
}Student;

Student *head_student=NULL;


int student_menu()
{
	int c;
	printf("\t\t\t\t\t\t*MENU*\n");
	printf("\t\t\t\t\t1->Add Student\n");
	printf("\t\t\t\t\t2->Delete Student\n");
	printf("\t\t\t\t\t3->Change data about Student\n");
	printf("\t\t\t\t\t4->Show the list of students\n");
	printf("\t\t\t\t\t5->Show the information about student\n");
	printf("\t\t\t\t\t6->Save and Exit\n");
	printf("\t\t\t\t\tInput->");
	scanf("%d",&c);
	return c;
}




void print_list_student(void)
{
	int listSize =count_nodes();
	int k = 0;
	Student *temp=head_student;
	
	int i=1;
	if(head_student==NULL)
	{
		printf("\t\t\t\tList is empty!\n");
		return;
	}
	else
	{
		
		while(temp != NULL   )
		{
			printf("\t\t\t\t***%d***\n",i);
			printf("\t\t\t\t%s\n",temp->Number);
			printf("\t\t\t\t%s\n",temp->Name);
			printf("\t\t\t\t%s\n",temp->Surname);
			printf("\t\t\t\t%s\n",temp->Patronymic);
			printf("\t\t\t\t%s\n",temp->Faculty);
			printf("\t\t\t\t%s\n",temp->Speciality);
			i++;
			temp=temp->next;
		}
	}
}

int count_nodes()
{
	int size=0;
	Student *temp=head_student;
	while(temp->next!=NULL)
	{
		size++;
		temp=temp->next;
	}
	return size;
}

void add_node_student(Student **newstudent)
{
	(*newstudent)->next=NULL;
	Student *temp=head_student;
	if(head_student==NULL)
	{
		head_student=*newstudent;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=*newstudent;
	}
}


int count_lines_student(void)
{
	FILE *f=fopen("student.csv","r");
	int count=0,size=0;
	char c;
	while(!feof(f))
	{
		c=getc(f);
		if(c==';')
		{
			count++;
		}
	}
	size=(count/6);
	return size;
	fclose(f);
}

void readfile_student(void)
{
	Student *newstudent;
	int row=count_lines_student();
	char Number[Length];
	char Name[Length];
	char Surname[Length];
	char Patronymic[Length];
	char Faculty[Length];
	char Speciality[Length];
	FILE *f=fopen("student.csv","r");
	int k=0,i=0;
	if(f==NULL)
	{
		printf("Cannnot find the file\n");
		return;
	}
			for(i=0;i<row;i++)
			{
				fscanf(f,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];\n",Number,Name,Surname,Patronymic,Faculty,Speciality);
				newstudent=(Student*)malloc(sizeof(Student));
				strcpy(newstudent->Number,Number);
				strcpy(newstudent->Name,Name);
				strcpy(newstudent->Surname,Surname);
				strcpy(newstudent->Patronymic,Patronymic);
				strcpy(newstudent->Faculty,Faculty);
				strcpy(newstudent->Speciality,Speciality);
				add_node_student(&newstudent);
			}
	fclose(f);
}



int search_student(char s[])
{
	Student *temp=head_student;
	while(temp!=NULL)
	{
		if(strcmp(temp->Number,s)==0)
		{
			printf("Such student exists!\n");
			return -1;
		}
		else
		{
			temp=temp->next;
		}
	}
}


void add_student(void)
{	
	char Number[Length];
	char Name[Length];
	char Surname[Length];
	char Patronymic[Length];
	char Faculty[Length];
	char Speciality[Length];
	printf("Number:");
	scanf("%s",Number);
	if(search_student(Number)==-1)
	{
		return;
	}
	printf("Name:");
	scanf("%s",Name);
	
	printf("Surname:");
	scanf("%s",Surname);
	
	printf("Patronymic:");
	scanf("%s",Patronymic);
	getchar();
	printf("Faculty:");
	scanf("%[^\n]s",Faculty);
	
	printf("Speciality:");
	scanf("%s",Speciality);
	Student *newstudent1 ;
	newstudent1=(Student*)malloc(sizeof(Student));
	strcpy(newstudent1->Number,Number);
	strcpy(newstudent1->Name,Name);
	strcpy(newstudent1->Surname,Surname);
	strcpy(newstudent1->Patronymic,Patronymic);
	strcpy(newstudent1->Faculty,Faculty);
	strcpy(newstudent1->Speciality,Speciality);\
	add_node_student(&newstudent1);
}


void save_and_exit(void)
{
	FILE *f=fopen("student.csv","w");
	Student *temp=head_student;
	if(head_student==NULL)
	{
		printf("Successfull saving!\n");
		return;
	}
	else
	{
		while(temp!=NULL)
		{
			fprintf(f,"%s;",temp->Number);
			fprintf(f,"%s;",temp->Name);
			fprintf(f,"%s;",temp->Surname);
			fprintf(f,"%s;",temp->Patronymic);
			fprintf(f,"%s;",temp->Faculty);
			fprintf(f,"%s;\n",temp->Speciality);
			temp=temp->next;
		}
	}
	printf("Successfull saving!\n");
	fclose(f);
}



delete_student()
{
	char str[Length];
	printf("Number of student:");
	scanf("%s",str);
	Student *prev=NULL,*temp=head_student;
	while(temp!=NULL)
	{
		if(strcmp(head_student->Number,str)==0)
		{
			temp=head_student->next;
			free(head_student);
			head_student=temp;
		}
		else
		{
			if(strcmp(temp->Number,str)==0)
			{
				prev->next=temp->next;
				free(temp);
				temp=prev->next;
			}
			else
			{
				prev=temp;
				temp=temp->next;
			}
		}
	}
}


int choose_f()
{
	int c;
	printf("1->YES;0->NO\n");
	scanf("%d",&c);
	return c;
}



void change_data_student()
{
	Student *temp=head_student;
	printf("#Changing some data#\n");
	char str[Length];
	printf("Number of student:");
	scanf("%s",str);
	while(temp!=NULL)
	{
		if(strcmp(temp->Number,str)==0)
		{
			printf("Want to change Name?\n");
			if(choose_f()==1)
			{
				char Name[Length];
				printf("Changing the name:");
				scanf("%s",Name);
				strcpy(temp->Name,Name);		
			}
			printf("Want to change Surname?\n");
			if(choose_f()==1)
			{
				char Surname[Length];
				printf("Changing the Surname:");
				scanf("%s",Surname);
				strcpy(temp->Surname,Surname);
			}
			printf("Want to change Patronymic?\n");
			if(choose_f()==1)
			{
				char Patronymic[Length];
				printf("Changing the Patronymic:");
				scanf("%s",Patronymic);
				strcpy(temp->Patronymic,Patronymic);
			}
			printf("Want to change Faculty?\n");
			if(choose_f()==1)
			{
				char Faculty[Length];
				printf("Changing the faculty:");
				scanf("%s",Faculty);
				strcpy(temp->Faculty,Faculty);
			}
			printf("Want to change Speciality?\n");
			if(choose_f()==1)
			{
				char Speciality[Length];
				printf("Changing the speciality:");
				scanf("%s",Speciality);
				strcpy(temp->Speciality,Speciality);
			}
			printf("Successfull changing!\n");
			return;
		}
		else
		{
			temp=temp->next;
		}
	}
	printf("Sorry,but such a student doesn't exist!\n");
}


void get_inf_student()
{
	char str[Length];
	printf("Number:");
	scanf("%s",str);
	Student *temp=head_student;
	while(temp!=NULL)
	{
		if(strcmp(temp->Number,str)==0)
		{
			printf("Number:%s\n",temp->Number);
			printf("Name:%s\n",temp->Name);
			printf("Surname:%s\n",temp->Surname);
			printf("Patronymic:%s\n",temp->Patronymic);
			printf("Faculty:%s\n",temp->Faculty);
			printf("Speciality:%s\n",temp->Speciality);
			return;
		}
		else
		{
			temp=temp->next;
		}
	}
	printf("Sorry, but such a student doesn't exist!\n");
}




int main()
{
	readfile_student();
	int choose;
	while(choose!=6)
	{
		choose=student_menu();
		switch(choose)
		{
		case 1: add_student(); break;
		case 2:	delete_student(); break;
		case 3:	change_data_student(); break;
		case 4:	print_list_student(); break;
		case 5: get_inf_student(); break;
		case 6: save_and_exit(); break;
		default: printf("Choose another action\n");break;
		}
	}
}
