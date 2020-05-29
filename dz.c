#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#define Length 200
typedef struct user
{
	char login[Length];
	char password[Length];
	int flag_book;
	int flag_student;
	struct user *next;
}Users;
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
typedef struct book
{
	char Isbn[Length];
	char authors[Length];
	char book_name[Length];
	int book_amount;
	int book_left;
	struct book *next;
}Book;
typedef struct st_book
{
	char Isbn[Length];
	char Number[Length];
	char date[Length];
	struct st_book *next;
}St_book;
Book *head_book=NULL;
Student *head_student=NULL;
Users *head_users=NULL;
St_book *head_stbook=NULL;

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
	printf("\t\t\t\t\t7->Show isbn of books of this student\n");
	printf("\t\t\t\t\tInput->");
	scanf("%d",&c);
	return c;
}
int Book_menu()
{
	int c;
	printf("\t\t\t\t\t\t*MENU*\n");
	printf("\t\t\t\t\t1->Add book\n");
	printf("\t\t\t\t\t2->Delete book\n");
	printf("\t\t\t\t\t3->Give a book\n");
	printf("\t\t\t\t\t4->Get a book\n");
	printf("\t\t\t\t\t5->Print list\n");
	printf("\t\t\t\t\t6->Save and exit\n");
	printf("\t\t\t\t\t7->Show numbers of students of this book\n");
	
	printf("\t\t\t\t\tInput->");
	scanf("%d",&c);
	return c;
}
int admin_menu()
{
	int c;
	printf("\t\t\t\t1->Student menu\n");
	printf("\t\t\t\t2->Book menu\n");
	printf("\t\t\t\t3->Exit\n");
	printf("\t\t\t\tInput->");
	scanf("%d",&c);
	return c;
}




void add_node_stbook(St_book **newstbook)
{
	(*newstbook)->next=NULL;
	St_book *temp=head_stbook;
	if(head_stbook==NULL)
	{
		head_stbook=*newstbook;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=*newstbook;
	}
}
int count_lines_stbook(void)
{
	FILE *f=fopen("student_book.csv","r");
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
	size=(count/3);
	return size;
	fclose(f);
}
void read_file_stbook(void)
{
	St_book *temp;
	int row=count_lines_stbook();
	char Isbn[Length];
	char Number[Length];
	char Date[Length];
	FILE *f=fopen("student_book.csv","r");
	int k=0,i=0;
	if(f==NULL)
	{
		printf("Cannot find  the file\n");
		return;
	}
	for(i=0;i<row;i++)
	{
		fscanf(f,"%[^;];%[^;];%[^;];\n",Isbn,Number,Date);
		temp=(St_book*)malloc(sizeof(St_book));
		strcpy(temp->Isbn,Isbn);
		strcpy(temp->Number,Number);
		strcpy(temp->date,Date);
		add_node_stbook(&temp);
	}
	fclose(f);
}
void add_stbook(void)
{
	char Isbn[Length];
	char Number[Length];
	char Date[Length];
	printf("Isbn:");
	scanf("%s",Isbn);
	printf("Number:");
	scanf("%s",Number);
	printf("Date:");
	scanf("%s",Date);
	St_book *temp=(St_book*)malloc(sizeof(St_book));
	strcpy(temp->Isbn,Isbn);
	strcpy(temp->Number,Number);
	strcpy(temp->date,Date);
	add_node_stbook(&temp);
}
save_stbook()
{
	St_book *temp=head_stbook;
	FILE *f=fopen("student_book.csv","w");
	if(head_stbook==NULL)
	{
		printf("Successful saving!\n");
		return;
	}
	else
	{
		while(temp!=NULL)
		{
			fprintf(f,"%s;",temp->Isbn);
			fprintf(f,"%s;",temp->Number);
			fprintf(f,"%s;\n",temp->date);
			temp=temp->next;
		}
	}
	fclose(f);
}
show_books()
{
	int i=0;
	St_book *temp1=head_stbook;
	char Number[Length];
	printf("Number of student:");
	scanf("%s",Number);
	while(temp1!=NULL)
	{
		if(strcmp(temp1->Number,Number)==0)
		{
			i=1;
			printf("Isbn of book:%s\tDate of return%s\n",temp1->Isbn,temp1->date);
		}
		temp1=temp1->next;
	}
	if(i==0)
	{
		printf("This student hasnt any books!\n");
	}
}
show_students()
{
	int j=0;
	char Isbn[Length];
	St_book *temp2=head_stbook;
	printf("Input  Isbn of book:");
	scanf("%s",Isbn);
	while(temp2!=NULL)
	{
		if(strcmp(temp2->Isbn,Isbn)==0)
		{
			j=1;
			printf("Student number:%s\tDate of return:%s\n",temp2->Number,temp2->date);
		}
		temp2=temp2->next;
	}
	if(j==0)
	{
		printf("Nobody borrowed this book\n");
	}
}
int check_if_st_has_book(char s[])
{
	int i=0;
	St_book *temp1=head_stbook;
	while(temp1!=NULL)
	{
		if(strcmp(temp1->Number,s)==0)
		{
			i=1;
			return i;
		}
		temp1=temp1->next;
	}
	return i;
}
int check_if_book_has_st(char s[])
{
	int i=0;
	St_book *temp1=head_stbook;
	while(temp1!=NULL)
	{
		if(strcmp(temp1->Isbn,s)==0)
		{
			i=1;
			return i;
		}
		temp1=temp1->next;
	}
	return i;
}
delete_stbook(char Isbn[],char Number[])
{
	St_book *prev3=NULL,*temp3=head_stbook;
	if((strcmp(head_stbook->Isbn,Isbn)==0)&&(strcmp(head_stbook->Number,Number)==0))
	{
		temp3=head_stbook->next;
		free(head_student);
		head_stbook=temp3;
	}
	else
	{
		if((strcmp(temp3->Isbn,Isbn)==0)&&(strcmp(temp3->Number,Number)==0))
		{
			prev3->next=temp3->next;
			free(temp3);
			temp3=prev3->next;
		}
		else
		{
			prev3=temp3;
			temp3=temp3->next;
		}
	}
}
show_min_date(char Isbn[])
{
	St_book *search=head_stbook;
	char str[Length];
	while(search!=NULL)
	{
		if(strcmp(search->Isbn,Isbn)==0)
		{
			strcpy(str,search->date);
			break;
		}
		search=search->next;
	}
	search=head_stbook;
	while(search!=NULL)
	{
		
	}
}




void print_list_student(void)
{
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
			printf("\t\t\t\tNumber:%s\n",temp->Number);
			printf("\t\t\t\tName:%s\n",temp->Name);
			printf("\t\t\t\tSurname:%s\n",temp->Surname);
			printf("\t\t\t\tPatronymic:%s\n",temp->Patronymic);
			printf("\t\t\t\tFaculty:%s\n",temp->Faculty);
			printf("\t\t\t\tSpeciality:%s\n",temp->Speciality);
			i++;
			temp=temp->next;
		}
	}
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
	getchar();
	printf("Speciality:");
	scanf("%[^\n]s",Speciality);
	Student *newstudent1 ;
	newstudent1=(Student*)malloc(sizeof(Student));
	strcpy(newstudent1->Number,Number);
	strcpy(newstudent1->Name,Name);
	strcpy(newstudent1->Surname,Surname);
	strcpy(newstudent1->Patronymic,Patronymic);
	strcpy(newstudent1->Faculty,Faculty);
	strcpy(newstudent1->Speciality,Speciality);\
	add_node_student(&newstudent1);
	printf("Successfull adding!\n");
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
			if(check_if_st_has_book(str)==1)
			{
				printf("You cant delete student, that has a book!\n");
				return;
			}
			temp=head_student->next;
			free(head_student);
			head_student=temp;
			printf("Deleted!\n");
		}
		else
		{
			if(strcmp(temp->Number,str)==0)
			{
				if(check_if_st_has_book(str)==1)
				{
					printf("You cant delete student, that has a book!\n");
					return;
				}
				prev->next=temp->next;
				free(temp);
				temp=prev->next;
				printf("Deleted!\n");
			}
			else
			{
				prev=temp;
				temp=temp->next;
			}
		}
	}
}
int choose_f_student()
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
			if(choose_f_student()==1)
			{
				char Name[Length];
				printf("Changing the name:");
				scanf("%s",Name);
				strcpy(temp->Name,Name);		
			}
			printf("Want to change Surname?\n");
			if(choose_f_student()==1)
			{
				char Surname[Length];
				printf("Changing the Surname:");
				scanf("%s",Surname);
				strcpy(temp->Surname,Surname);
			}
			printf("Want to change Patronymic?\n");
			if(choose_f_student()==1)
			{
				char Patronymic[Length];
				printf("Changing the Patronymic:");
				scanf("%s",Patronymic);
				strcpy(temp->Patronymic,Patronymic);
			}
			printf("Want to change Faculty?\n");
			if(choose_f_student()==1)
			{
				char Faculty[Length];
				printf("Changing the faculty:");
				scanf("%s",Faculty);
				strcpy(temp->Faculty,Faculty);
			}
			printf("Want to change Speciality?\n");
			if(choose_f_student()==1)
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
void save_and_exit_student(void)
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





void print_list_book(void)
{
	Book *temp=head_book;
	int i=1;
	if(head_book==NULL)
	{
		printf("\t\t\t\tList is empty!\n");
		return;
	}
	else
	{
		while(temp!=NULL)
		{
			printf("\t\t\t\t***%d***\n",i);
			printf("\t\t\t\tISBN:%s\n",temp->Isbn);
			printf("\t\t\t\tAuthors:%s\n",temp->authors);
			printf("\t\t\t\tName:%s\n",temp->book_name);
			printf("\t\t\t\tAmount:%d\n",temp->book_amount);
			printf("\t\t\t\tLeft:%d\n",temp->book_left);
			i++;
			temp=temp->next;
		}
	}
}
void add_node_book(Book **newbook)
{
	(*newbook)->next=NULL;
	Book *temp=head_book;
	if(head_book==NULL)
	{
		head_book=*newbook;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=*newbook;
	}
}
int count_lines_book(void)
{
	FILE *f=fopen("books.csv","r");
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
	size=(count/5);
	fclose(f);
	return size;
}
void readfile_book(void)
{
	Book *newbook;
	int loop=0;
	int row=count_lines_book();
	char c;
	char Isbn[Length];
	char authors[Length];
	char book_name[Length];
	char book_amount_c[Length];
	char book_left_c[Length];
	FILE *f=fopen("books.csv","r");
	int k=0,i=0;
	if(f==NULL)
	{
		printf("Cannnot find the file\n");
		return;
	}
	for(i=0;i<row;i++)
	{
		fscanf(f,"%[^;];%[^;];%[^;];%[^;];%[^;];\n",Isbn,authors,book_name,book_amount_c,book_left_c);
		newbook=(Book*)malloc(sizeof(Book));
		strcpy(newbook->Isbn,Isbn);
		strcpy(newbook->authors,authors);
		strcpy(newbook->book_name,book_name);
		newbook->book_amount=0;
		for(loop=0;loop<strlen(book_amount_c);loop++)
		{
			newbook->book_amount=newbook->book_amount*10+(book_amount_c[loop]-'0');
		}
		newbook->book_left=0;
		for(loop=0;loop<strlen(book_left_c);loop++)
		{
			newbook->book_left=newbook->book_left*10+(book_left_c[loop]-'0');
		}
		add_node_book(&newbook);
	}
	fclose(f);
}
int search_book(char s[])
{
	Book *temp=head_book;
	while(temp!=NULL)
	{
		if(strcmp(temp->Isbn,s)==0)
		{
			printf("Such book exists!\n");
			return -1;
		}
		else
		{
			temp=temp->next;
		}
	}
}
void add_book(void)
{
	char Isbn[Length];
	char authors[Length];
	char book_name[Length];
	int book_amount;
	int book_left;
	printf("Isbn:");
	scanf("%s",Isbn);
	getchar();
	if(search_book(Isbn)==-1)
	{
		return;
	}
	printf("Authors:");
	scanf("%[^\n]s",authors);
	getchar();
	printf("Book name:");
	scanf("%[^\n]s",book_name);
	printf("Amount of book:");
	scanf("%d",&book_amount);
	book_left=book_amount;
	Book *newbook=(Book*)malloc(sizeof(Book));
	strcpy(newbook->Isbn,Isbn);
	strcpy(newbook->authors,authors);
	strcpy(newbook->book_name,book_name);
	newbook->book_amount=book_amount;
	newbook->book_left=book_left;
	add_node_book(&newbook);
}
void delete_book(void)
{
	char str[Length];
	printf("Isbn of book:");
	scanf("%s",str);
	Book *prev=NULL,*temp=head_book;
	while(temp!=NULL)
	{
		if(strcmp(head_book->Isbn,str)==0)
		{
			if(check_if_book_has_st(str)==1)
			{
				printf("You cant delete this book!\n");
				return;
			}
			temp=head_book->next;
			free(head_book);
			head_book=temp;
			printf("Deleted!\n");
		}
		else
		{
			if(strcmp(temp->Isbn,str)==0)
			{
				if(check_if_book_has_st(str)==1)
				{
					printf("You cant delete this book!\n");
					return;
				}
				prev->next=temp->next;
				free(temp);
				temp=prev->next;
				printf("Deleted!\n");
			}
			else
			{
				prev=temp;
				temp=temp->next;
			}
		}
	}
}
void give_book(void)
{
	St_book *search=head_stbook;
	Student *temp1=head_student;
	Book *temp=head_book;
	char Isbn[Length];
	char Number[Length];
	char date[Length];
	printf("Isbn of book:");
	scanf("%s",Isbn);
	printf("Number of student:");
	scanf("%s",Number);
	printf("Date of return:");
	scanf("%s",date);
	while(temp!=NULL)
	{
		if(strcmp(temp->Isbn,Isbn)==0)
		{
			if(temp->book_left==0) 
			{
				printf("Sorry, but there is no such book left\nYou can bring one at:\n");
				while(search!=NULL)
				{
					if(strcmp(search->Isbn,Isbn)==0)
					{
						printf("%s\n",search->date);
					}
					search=search->next;
				}
				return;
			}
			while(temp1!=NULL)
			{
				if(strcmp(temp1->Number,Number)==0)
				{
					temp->book_left--;
					St_book *newstbook;
					newstbook=(St_book*)malloc(sizeof(St_book));
					strcpy(newstbook->Isbn,Isbn);
					strcpy(newstbook->Number,Number);
					strcpy(newstbook->date,date);
					add_node_stbook(&newstbook);
					printf("Successful\n");
					return;
				}
				temp1=temp1->next;
			}
			printf("Wrong number of student\n");
			return;
		}
		temp=temp->next;
	}
}
void get_book(void)
{
	char str[Length];
	char Number[Length];
	printf("Isbn of a book:");
	scanf("%s",str);
	printf("Number of student:");
	scanf("%s",Number);
	St_book *temp2=head_stbook;
	Book *temp=head_book;
	while(temp!=NULL)
	{
		if(strcmp(temp->Isbn,str)==0)
		{
			if(temp->book_left==temp->book_amount)
			{
				printf("Sorry, but all of books are in the library!\n");
				return;
			}
			while(temp2!=NULL)
			{
				if(strcmp(temp->Isbn,temp2->Isbn)==0)
				{
					if(strcmp(temp2->Number,Number)==0)
					{
						delete_stbook(str,Number);
						temp->book_left++;
						printf("Successfull!\n");
						return;
					}
				}
				temp2=temp2->next;
			}	
		}
		temp=temp->next;
	}
	printf("Sorry,but you entered wrong datas!\n");
}
void save_and_exit_book(void)
{
	save_stbook();
	FILE *f=fopen("books.csv","w");
	Book *temp=head_book;
	if(head_book==NULL)
	{
		printf("Successfull saving!\n");
		return;
	}
	else
	{
		while(temp!=NULL)
		{
			fprintf(f,"%s;",temp->Isbn);
			fprintf(f,"%s;",temp->authors);
			fprintf(f,"%s;",temp->book_name);
			fprintf(f,"%d;",temp->book_amount);
			fprintf(f,"%d;\n",temp->book_left);
			temp=temp->next;
		}
	}
	printf("Successfull saving!\n");
	fclose(f);
}





add_node_user(Users **user)
{
	(*user)->next=NULL;
	Users *temp=head_users;
	if(head_users==NULL)
	{
		head_users=*user;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=*user;
	}
}
int count_users()
{
	char c;
	int count=0,size=0;
	FILE *f=fopen("users.csv","r");
	while(!feof(f))
	{
		c=fgetc(f);
		if(c==';')
		{
			count++;
		}
	}
	size=(count/4);
	fclose(f);
	return size;	
}
void readfile_users(void)
{
	int row=count_users();
	char Login[Length];
	char Password[Length];
	char flag_book[Length];
	char flag_student[Length];
	FILE *f=fopen("users.csv","r");
	int i=0;
	if(f==NULL)
	{
		printf("Cannot find the file\n");
		return;
	}
	for(i=0;i<row;i++)
	{
		fscanf(f,"%[^;];%[^;];%[^;];%[^;];\n",Login,Password,flag_book,flag_student);
		Users *user=(Users*)malloc(sizeof(Users));
		strcpy(user->login,Login);
		strcpy(user->password,Password);
		user->flag_book=0;
		user->flag_book=flag_book[0]-'0';
		user->flag_student=0;
		user->flag_student=flag_student[0]-'0';
		add_node_user(&user);
	}
	fclose(f);
}






int main()
{
	readfile_book();
	read_file_stbook();
	readfile_users();
	readfile_student();
	int check=0,choose_ad,choose_st,choose_bk;
	char Login[Length];
	char Password[Length];
	Users *temp;
	while(check!=1)
	{
		printf("Login:");
		scanf("%s",Login);
		printf("Password:");
		scanf("%s",Password);
		temp=head_users;
		while(temp!=NULL)
		{
			if((strcmp(temp->login,Login)==0)&&(strcmp(temp->password,Password)==0))
			{
				check=1;
				break;
			}
			temp=temp->next;
		}
		if(check==0)
		{
			printf("Incorrect authorization!\n");
		}
	}
	if((temp->flag_book==1)&&(temp->flag_student==1))
	{
		while(choose_ad!=3)
		{
			choose_ad=admin_menu();
			switch(choose_ad)
			{
				case 1:	while(choose_st!=6)
						{			
							choose_st=student_menu();
							switch(choose_st)
							{
								case 1: add_student(); break;
								case 2:	delete_student(); break;
								case 3:	change_data_student(); break;
								case 4:	print_list_student(); break;
								case 5: get_inf_student(); break;
								case 7: show_books(); break;
								case 6: save_and_exit_student(); break;
								default: printf("Choose another action\n");break;
							}
						}break;
				case 2:	while(choose_bk!=6)
						{
							choose_bk=Book_menu();
							switch(choose_bk)
							{
								case 1: add_book(); break;
								case 2:	delete_book(); break;
								case 3:	give_book(); break;
								case 4:	get_book(); break;
								case 5: print_list_book(); break;
								case 7: show_students(); break;
								case 6: save_and_exit_book(); break;
								default: printf("Choose another action\n");break;
							}
						}break;
				case 3: break;
				default: printf("Choose press appropriate action!\n");
			}choose_st=0;choose_bk=0;
		}
	}
	if((temp->flag_book==1)&&(temp->flag_student==0))
	{
		while(choose_bk!=6)
						{
							choose_bk=Book_menu();
							switch(choose_bk)
							{
								case 1: add_book(); break;
								case 2:	delete_book(); break;
								case 3:	give_book(); break;
								case 4:	get_book(); break;
								case 5: print_list_book(); break;
								case 7: show_students(); break;
								case 6: save_and_exit_book(); break;
								default: printf("Choose another action\n");break;
							}
						}
	}
	if((temp->flag_book==0)&&(temp->flag_student==1))
	{
		while(choose_st!=6)
		{			
			choose_st=student_menu();
			switch(choose_st)
			{
				case 1: add_student(); break;
				case 2:	delete_student(); break;
				case 3:	change_data_student(); break;
				case 4:	print_list_student(); break;
				case 5: get_inf_student(); break;
				case 7: show_books();break;
				case 6: save_and_exit_student(); break;
				default: printf("Choose another action\n");break;
			}
		}
	}
}
