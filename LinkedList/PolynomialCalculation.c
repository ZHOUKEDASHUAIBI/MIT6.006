#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int coefficient;
	int exponent;
	struct Node* next;
};

typedef struct Node* polynomial;

polynomial read();
polynomial polyAdd(polynomial poly1, polynomial poly2);
polynomial polyprod(polynomial poly1, polynomial poly2);
void polynomial_print(polynomial poly1);

int main()
{
	polynomial poly1;
	polynomial poly2;
	
	polynomial polyproduct;
	poly1 = read();
	poly2 = read();
	//polySum = polyAdd(poly1,poly2);
	polyproduct = polyprod(poly1,poly2);
	polynomial_print(polyproduct);
	
	return 0;
}

polynomial read(void)
{
	int n_item;
	int coef, exp;
	scanf("%d",&n_item);
	polynomial poly1 = (polynomial)malloc(sizeof(struct Node));
	polynomial rear, t1;
	poly1->next = NULL;
	rear = poly1;
	while(n_item--)
	{
		polynomial ptr = (polynomial)malloc(sizeof(struct Node));
		scanf("%d %d",&coef,&exp);
		ptr->coefficient = coef;
		ptr->exponent = exp;
		ptr->next = rear->next;
		rear->next = ptr;
		rear = rear->next;
	}
	t1 = poly1;
	poly1 = poly1->next;
	free(t1);
	return poly1;
}

polynomial polyAdd(polynomial poly1, polynomial poly2)
{
	polynomial polySum = (polynomial)malloc(sizeof(struct Node));
	polynomial rear,t1;
	polySum->next = NULL;
	rear = polySum;
	while(poly1 && poly2)
	{	
		polynomial tempcell = (polynomial)malloc(sizeof(struct Node)); 
		if(poly1->exponent > poly2->exponent)
		{
			tempcell = poly1;
			poly1 = poly1->next;
			tempcell->next = rear->next;
			rear->next = tempcell;
			rear = rear->next;
			//free(tempcell);
		}
		else if (poly1->exponent < poly2->exponent)
		{
			tempcell = poly2;
			poly2 = poly2->next;
			tempcell->next = rear->next;
			rear->next = tempcell;
			rear = rear->next;
			//free(tempcell);
		}
		else if (poly1->exponent == poly2->exponent)
		{
			tempcell->coefficient = poly1->coefficient + poly2->coefficient;
			tempcell->exponent = poly1->exponent;
			if(tempcell->coefficient)
			{
				tempcell->next = rear->next;
				rear->next = tempcell;
				rear = rear->next;
			}
			poly1 = poly1->next;
			poly2 = poly2->next;
			//free(tempcell);
		}
	}
	while(poly1)
	{
		polynomial tempcell = (polynomial)malloc(sizeof(struct Node));
		tempcell = poly1;
		poly1 = poly1->next;
		tempcell->next = rear->next;
		rear->next = tempcell;
		rear = rear->next;
		//free(tempcell);
	}
	while(poly2)
	{
		polynomial tempcell = (polynomial)malloc(sizeof(struct Node));
		tempcell = poly2;
		poly2 = poly2->next;
		tempcell->next = rear->next;
		rear->next = tempcell;
		rear = rear->next;
		//free(tempcell);
	}
	t1 = polySum;
	polySum = polySum->next;
	free(t1);
	return polySum;
}

polynomial polyprod(polynomial poly1, polynomial poly2)
{
	polynomial polyprod1 = (polynomial)malloc(sizeof(struct Node));
	polynomial polyprod2 = (polynomial)malloc(sizeof(struct Node));
	polynomial tmp1;
	polynomial tmp2;
	polynomial rear1;
	polynomial rear2;
	polynomial t1;
	polynomial temp = (polynomial)malloc(sizeof(struct Node));
	tmp1 = poly1;
	tmp2 = poly2;
	polyprod1->next = NULL;
	polyprod2->next = NULL;
	rear1 = polyprod1;
	rear2 = polyprod2;
	
	while(tmp2)
	{	
		polynomial temp = (polynomial)malloc(sizeof(struct Node));
		temp->coefficient = tmp1->coefficient * tmp2->coefficient;
		temp->exponent = tmp1->exponent + tmp2->exponent;
		temp->next = rear1->next;
		rear1->next = temp;
		rear1 = rear1->next;
		tmp2 = tmp2->next;
	}
	
	tmp1 = tmp1->next;
	tmp2 = poly2;
	
	while(tmp1)
	{
		while(tmp2)
		{	
			polynomial temp = (polynomial)malloc(sizeof(struct Node));
			temp->coefficient = tmp1->coefficient * tmp2->coefficient;
			temp->exponent = tmp1->exponent + tmp2->exponent;
			temp->next = rear2->next;
			rear2->next = temp;
			rear2 = rear2->next;
			tmp2 = tmp2->next;
		}
		
		polyprod1 = polyAdd(polyprod1, polyprod2);
		polyprod2->next = NULL;                           //polyprod2置空（初始化） 
		rear2 = polyprod2;								  // rear置空（初始化） 
		tmp2 = poly2;									  //tmp2初始化 
		tmp1 = tmp1->next;
	}
	
	t1 = polyprod1;
	polyprod1 = polyprod1->next;
	free(t1);
	return polyprod1;
}

void polynomial_print(polynomial poly1)
{
	while(poly1)
	{
		printf("%d %d ",poly1->coefficient,poly1->exponent);
		poly1 = poly1->next;
	} 
}
