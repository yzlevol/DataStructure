// Date: 2023/9/21
// Description: LinkList.cpp
// Author: Yan Hyoung
// 线性链表
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define  ERROR 0
#define  OK    1
typedef int ElemType;
typedef int Status;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;


/*取元素*/
Status GetElem_L(LinkList L, int i, ElemType& e)
{
	LinkList p;
	int j = 1;
	p = L->next;
	j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i)return ERROR;
	e = p->data;
	return OK;
}
/*插入元素*/
Status ListInsert_L(LinkList& L, int i, ElemType& e)
{
	LinkList p = L,s;
	int j = 0;
	while (p && j < i - 1) { p = p->next; ++j; }
	if (!p || j > i - 1)return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	if (!s) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	s->data = e; s->next = p->next;
	p->next = s;
	return OK;
}
/*删除元素*/
Status ListDelete_L(LinkList& L, int i, ElemType& e)
{
	LinkList p = L,q;
	int j = 0;
	while (p && j < i - 1) { p = p->next; ++j; }
	if (!p || j > i - 1)return ERROR;
	e = p->next->data;
	q = p->next;
	p->next = p->next->next;
	free(q);
	return OK;
}
/*建立链表-头插法*/
void CreateList_H(LinkList& L, int n)
{
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = n; i > 0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		if (!p) {
			printf("Memory allocation failed.\n");
			exit(1);
		}
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
}
/*建立链表-尾插法*/
void CreateList_T(LinkList& L, int n)
{
	LinkList p,q;
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	L->next = NULL;
	p = L;
	for (int i = 0; i < n; ++i)
	{
		q = (LinkList)malloc(sizeof(LNode));
		if (!q) {
			printf("Memory allocation failed.\n");
			exit(1);
		}
		scanf("%d", &q->data);
		q->next = NULL;
		p->next = q;
		p = p->next;
	}
	
}
/*有序链表的合并*/
void MergeList_L(LinkList& La, LinkList& Lb, LinkList& Lc)
{
	LinkList pa, pb, pc;
	pa = La->next, pb = Lb->next;
	Lc = pc = NULL;
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			if (!Lc) {
				Lc = pc = pa;
			}
			else {
				pc->next = pa; pc = pa;
			}
			pa = pa->next;
			}
			else {
				if (!Lc)
				{
					Lc = pc = pb;
				}
				else
				{
					pc->next = pb;
					pc = pb;
				}
				pb = pb->next;
			}
		}
		pc->next = pa ? pa : pb;
	}

int compare(ElemType e1, ElemType e2)
{
	if (e1 == e2)return 1;
	else return 0;
}

/*查找*/
int LocateElem_L(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		++i;
		if (compare(p->data, e))return i;
		p = p->next;
	}
	return 0;
}

/*输出列表*/
// Function to print a linked list
void print_L(LinkList L)
{
	LinkList p = L->next;
	if (p == NULL) {
		printf("The list is empty.\n");
		return;
	}
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

/*初始化*/
Status InitList_L(LinkList& L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) {
		cout << "failed to init List." << endl;
		exit(OVERFLOW);
	}
	L->next = NULL;
	return OK;
}
Status ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		++i;
		p = p->next;
	}
	return i;
}
Status DestoryList_L(LinkList& L)
{
	LinkList q;
	while (L)
	{
		q = L->next;
		free(L);
		L = q;
	}
	return OK;
}
Status ClearList_L(LinkList& L)
{
	LinkList p,q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}
Status ListEmpty_L(LinkList L)
{
	if (L->next)
		return false;
	else
		return true;
}
int main()
{
	LinkList La,Lb,Lc;
	Lc = NULL;
	CreateList_H(La, 5);
	print_L(La);
	CreateList_T(Lb, 3);
	print_L(Lb);
	MergeList_L(La, Lb, Lc);
	print_L(Lc);
	cout << "find at" << LocateElem_L(Lc, 60, compare) << endl;
	return 0;
}