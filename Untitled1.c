#include<stdio.h>
#include<math.h>



void input_a(double *p)
{
	printf("Input a:");
	double x;
	while(1)
	{
		scanf("%lf",&x);
		if(getchar()!='\n')
		{
			printf("You can only input the numbers, not characters!\nInput a:");
		}
		else
		{
			*p=x;
			break;
		}
	}
}
void input_b(double *q)
{
	printf("Input b:");
	double x;
	while(1)
	{
		scanf("%lf",&x);
		if(getchar()!='\n')
		{
			printf("You can only input the numbers, not characters!\nInput b:");
		}
		else
		{
			*q=x;
			break;
		}
	}
}
void input_c(double *r)
{
	printf("Input c:");
	double x;
	while(1)
	{
		scanf("%lf",&x);
		if(getchar()!='\n')
		{
			printf("You can only input the numbers, not characters!\nInput c:");
		}
		else
		{
			*r=x;
			break;
		}
	}
}

void root0(double a,double b)
{
	double x=-b/(2*a);
	printf("x = %lf",x);
}

void root1(double a,double b,double D)
{
	double x1=(-b+sqrt(D))/(2*a);
	double x2=(-b-sqrt(D))/(2*a);
	printf("x1 = %lf\nx2 = %lf\n",x1,x2);
}


int main()
{
	double a,b,c;
	input_a(&a);
	input_b(&b);
	input_c(&c);
	double D;
	D=pow(b,2)-4*a*c;
	if(D==0)
	{
		root0(a,b);
	}
	else if(D<0)
	{
		printf("The equation doesn't has any root!\n");
	}
	else if(D>0)
	{
		root1(a,b,D);
	}
	return 0;
}
