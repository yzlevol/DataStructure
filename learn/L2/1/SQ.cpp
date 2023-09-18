#include<iostream>
using namespace std;



/*线性表定义*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

typedef struct {
	ElemType* elem;
	int length;
	int listsize;

}SqList;

/*InitList_Sq*/
Status InitList_Sq(SqList& L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) {
		exit(OVERFLOW);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
Status ListInsert_Sq(SqList& L, int i, ElemType e)
{
	ElemType* newbase;
	if (i<1 || i>L.length + 1) {
		return ERROR;
	}
	if (L.length >= L.listsize)
	{
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType* p, * q;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)*(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}

Status ListDelete_Sq(SqList& L, int i, ElemType& e)
{
	ElemType* p, * q;
	if ((i < 1) || (i > L.length))return ERROR;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)*(p - 1) = *(p);
	--L.length;
	return OK;
}

Status LocateElem_Sq(SqList& Lq, ElemType e, Status(*Compare)(ElemType, ElemType))
{
	ElemType* p = Lq.elem;
	int i = 1;
	while (i < Lq.length && (*Compare)(*p++, e))
	{
		++i;
	}
	if (i <= Lq.length)return i;
	else return 0;
}

void MergeList_Sq(SqList La, SqList Lb, SqList& Lc)
{
	ElemType* pa, * pb, * pc;
	pa = La.elem; pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if (!pc)exit(OVERFLOW);
	ElemType* pa_last, * pb_last;
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)*pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last)*pc++ = *pa++;
	while (pb <= pb_last)*pc++ = *pb++;
}

int compare_Elem(ElemType E1, ElemType E2) 
{
	if (E1 > E2)return 1;
	else if (E1 < E2)return -1;
	else return 0;
}

void print_Sq(SqList& La)
{
	for (int i = 0; i < La.length; ++i) {
		cout << "第" << i + 1 << "个元素: " << La.elem[i] << endl;
	}
}
int main()
{
	cout << "-----InitList_Sq-----" << endl;
	SqList La;
	InitList_Sq(La);
	for (int i = 0; i < 10; ++i)
	{
		ListInsert_Sq(La, i + 1, i+1);
	}
	cout << "原始表:" << endl;
	print_Sq(La);
	cout << "-----ListDelete_Sq-----" << endl;
	ElemType delete_e;
	ListDelete_Sq(La, 3, delete_e);
	cout << "删除元素后:" << endl;
	print_Sq(La);
	cout << "删除的元素为" << delete_e << endl;
	cout << "-----LocateElem_Sq-----" << endl;
	int (*Compare)(ElemType, ElemType) = NULL;
	Compare = compare_Elem;
	int result = 0;
	int locatee = 0;
	cout << "input the number you want to locate." << endl;
	cin >> locatee;
	result = LocateElem_Sq(La, locatee, Compare);
	if (result) {
		cout << "Found the Elem:" << locatee << " at " << result << endl;
	}
	else
		cout << "not find the Elem." << endl;
	cout << "-----MergeList_Sq-----" << endl;
	SqList Lb, Lc, Ld;
	InitList_Sq(Lb);
	for (int i = 0; i < 6; ++i)
	{
		ListInsert_Sq(Lb, i + 1, i + 3);
	}
	cout << "Lb表:" << endl;
	print_Sq(Lb);
	InitList_Sq(Lc);
	for (int i = 0; i < 10; ++i)
	{
		ListInsert_Sq(Lc, i + 1, i + 2);
	}
	cout<<"Lc表:"<<endl;
	print_Sq(Lc);
	InitList_Sq(Ld);
	MergeList_Sq(Lb, Lc, Ld);
	cout << "合并后的Ld表:" << endl;
	print_Sq(Ld);
	return 0;
}