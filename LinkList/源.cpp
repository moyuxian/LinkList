#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
	int data;
	struct LinkNode* next;
}LinkNode, * LinkList;

//头插法
void HeadInsert(LinkList& L, int x) {
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	p->data = x;
	p->next = L->next;
	L->next = p;
}

//尾插法建立链表
void TailInsert(LinkList& L, int s[], int slen) {
	L = (LinkList)malloc(sizeof(LinkNode));
	L->next = NULL;
	LinkList pre = L;
	for (int i = 0; i < slen; i++)
	{
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		p->data = s[i];
		p->next = pre->next;
		pre->next = p;
		pre = p;
	}
}

//已知L为带头结点的单链表，请按照递归的思想实现下列运算
/*
1)求链表中的最大整数
2)求链表中的结点数
3)求链表中所有元素的平均值
*/
int getMAX(LinkList L) {
	if (L == NULL) {
		return -999999;
	}
	int max;
	max = getMAX(L->next);
	return max > L->data ? max : L->data;
}
int getNodes(LinkList L) {
	if (L == NULL) {
		return 0;
	}
	return 1 + getNodes(L->next);
}
int getMean(LinkList L) {
	if (L == NULL)
	{
		return 0;
	}
	return L->data + getMean(L->next);
}

//单链表访问第i个数据结点
int getMarked(LinkList L, int i) {
	int count = 0;
	while (L != NULL && count != i)
	{
		L = L->next;
		count++;
	}
	if (L != NULL)
	{
		return L->data;
	}
}

//第i个结点前插入元素e
void insertElem(LinkList L, int e, int i) {
	LinkList pre = NULL;
	int count = 0;
	while (L != NULL && count != i)
	{
		pre = L;
		L = L->next;
		count++;
	}
	if (L != NULL)
	{
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		p->data = e;
		p->next = L;
		pre->next = p;
	}
}

//设计算法高效查找带头结点单链表倒数第m个位置的结点并输出该结点值
void findLast(LinkList L, int m) {
	LinkList pre = L;
	for (int i = 0; i < m; i++)
	{
		L = L->next;
	}
	while (L != NULL)
	{
		pre = pre->next;
		L = L->next;
	}
	printf("%d\n", pre->data);
}

//已知指针La和Lb分别指向两个无头结点的单链表。编写函数完成从La中删除第j个结点开始的共len个元素并将这len个元素插入到表Lb中的j个元素之前
void Func_7(LinkList& La, LinkList& Lb, int j, int len) {
	LinkList Ha = (LinkList)malloc(sizeof(LinkNode));
	LinkList Hb = (LinkList)malloc(sizeof(LinkNode));
	Ha = NULL; Hb = NULL;
	Ha->next = La;
	Hb->next = Lb;
	int count = 0;
	LinkList Apre = Ha;
	LinkList Bpre = Hb;
	LinkList Apj = Ha;
	LinkList Bpj = Hb;
	while (Apj != NULL && Bpj != NULL && count != j)
	{
		Apre = Apj;
		Apre = Bpj;
		Apj = Apj->next;
		Bpj = Bpj->next;
		count++;
	}
	count = 1;
	LinkList plen = Apj;
	while (plen != NULL && count != len)
	{
		plen = plen->next;
		count++;
	}
	Apre->next = plen->next;
	Bpre->next = Apj;
	plen->next = Bpj;
	La = Ha->next;
	Lb = Hb->next;
	free(Ha);
	free(Hb);
}

//蛇单链表表头指针为L，结点数据域为字符。设计时间复杂度最低的算法判断前n/2个字符是否为与n/2字符依次相同，例如xyx和xyxy 前一半字符与后一半字符相同。
bool isSym(LinkList L, int n) {
	LinkList s, e;
	s = L->next;
	e = L;
	int i = 0;
	while (e != NULL && i != (n + 3) / 2)
	{
		e = e->next;
		i++;
	}
	bool ret = false;
	for (i = 0; i < n / 2; i++)
	{
		if (s->data != e->data)
			return false;
		s = s->next;
		e = e->next;
	}
	return true;
}
//从非递减有序链表中删除值相同的多余元素
void DeleteSame(LinkList L) {
	LinkList pre = L;
	L = L->next;
	while (L != NULL)
	{
		if (pre->data == L->data)
		{
			pre->next = L->next;
			free(L);
			L = pre->next;
		}
		else
		{
			pre = L;
			L = L->next;
		}
	}
}

//设有一个非递减的正整数单链表（有重复数），设计算法确定比x小的结点数据（重复的只算一个）。（例如1 2 2 3 4 6 7 若x为4 则返回 3）
int littleNum(LinkList L, int x)
{
	int count = 0;
	LinkList pre = L->next;
	while (pre->next != NULL && pre->data < x) {
		count++;
		int temp = pre->data;
		while (temp == pre->data)
		{
			pre = pre->next;
		}
	}
	return count;
}

//删除非递减单链表La中La与Lb相同的元素
void DeleteLaSame(LinkList La, LinkList Lb) {
	LinkList a = La->next;
	LinkList b = Lb->next;
	LinkList pre = La;
	while (a && b)
	{
		if (a->data = b->data) {
			pre->next = a->next;
			free(a);
			a = pre->next;
		}
		else if (a->data > b->data)
		{
			b = b->next;
		}
		else
		{
			pre = a;
			a = a->next;
		}
	}
}

//已知LaLbLc 是三个链表，且它们已经初始化，其元素递增顺序排列，每个表中均无重复元素，设计算法在表LC中删除同时出现在La和Lb中的所有元素
void DeleteLcSame(LinkList La, LinkList Lb, LinkList Lc) {
	LinkList a = La->next;
	LinkList b = Lb->next;
	LinkList c = Lc->next;
	LinkList pre = Lc;
	while (a && b && c)
	{
		if (a->data == b->data) {
			if (c->data < a->data)
			{
				pre = c;
				c = c->next;
			}
			else if (c->data == a->data)
			{
				pre->next = c->next;
				free(c);
				c = pre->next;
			}
		}
		else if (a->data > b->data) {
			b = b->next;
		}
		else
		{
			a = a->next;
		}
	}
}

//La和Lb按值非递减，归并La和Lb，得到新的单链表Lc，使得Lc也按值非递减且不含重复元素，并占用原来的空间。
void tailInsert(LinkList& tail, LinkList ins) {
	if (tail->data == ins->data)
	{
		free(ins);
	}
	else {
		ins->next = NULL;
		tail->next = ins;
		tail = tail->next;
	}
}
LinkList combineLaLb(LinkList La, LinkList Lb) {
	LinkList Lc = La;
	LinkList pre = La;
	LinkList pLa = La->next;
	LinkList pLb = Lb->next;
	LinkList temp;
	free(Lb);
	while (pLa && pLb)
	{
		if (pLa->data < pLb->data) {
			temp = La;
			La = La->next;
			tailInsert(pre, temp);
		}
		else if (pLa->data > pLb->data)
		{
			temp = Lb;
			Lb = Lb->next;
			tailInsert(pre, temp);
		}
		else
		{
			temp = La;
			La = La->next;
			tailInsert(pre, temp);
			temp = Lb;
			Lb = Lb->next;
			tailInsert(pre, temp);
		}
	}
	while (pLa)
	{
		temp = La;
		La = La->next;
		tailInsert(pre, temp);
	}
	while (pLb)
	{
		temp = Lb;
		Lb = Lb->next;
		tailInsert(pre, temp);
	}
	return Lc;
}

//带头结点的单链表中所有元素的数据值按递增顺序排列，删除链表中大于min且小于max的元素
void deleteNode(int max, int min, LinkList L) {
	LinkList p = L->next;
	LinkList pre = L;
	while (p != NULL)
	{
		if (p->data >= max)
		{
			break;
		}
		if (p->data > min && p->data < max) {
			pre->next = p->next;
			free(p);
			p = pre->next;
		}
		else
		{
			pre = p;
			p = p->next;
		}

	}
}

//对链表使用冒泡排序
void linkPopSort(LinkList L) {
	LinkList p = L->next;
	while (p->next != NULL)
	{
		if (p->data > p->next->data)
		{
			int tmp = p->data;
			p->data = p->next->data;
			p->next->data = tmp;
		}
		p = p->next;
	}
}

//设L为单链表头结点地址，其数据结点都是正整数可能存在相同数值的结点，设计一个空间复杂度最低的算法，利用直接插入排序把该链表整理成有序递增的链表并将重复结点删除
void insertSort(LinkList L) {
	LinkList p = L->next;
	L->next = NULL;
	while (p != NULL)
	{
		LinkList pcur = L->next;
		LinkList precur = L;
		while (pcur != NULL && p->data > pcur->data) {
			precur = pcur;
			pcur = pcur->next;
		}
		LinkList tmp = p;
		p = p->next;
		if (pcur != NULL && pcur->data == tmp->data) {
			free(tmp);
		}
		else
		{
			tmp->next = precur->next;
			precur->next = tmp;
		}
	}
}

//将带头结点所有小于x的元素都排在前面，所有大于x的都排在后面
void order(LinkList L, int x)
{
	LinkList p = L->next;
	LinkList xn = (LinkList)malloc(sizeof(LinkNode));
	xn->data = x;
	xn->next = NULL;
	L->next = xn;
	LinkList precur = L;
	while (p != NULL)
	{

		LinkList tmp = p;
		p = p->next;
		if (tmp->data < x) {
			tmp->next = L->next;
			L->next = tmp;
			if (L == precur)
			{
				precur = tmp;
			}
		}
		else if (tmp->data > x)
		{
			tmp->next = xn->next;
			xn->next = tmp;
		}
		else
		{
			tmp->next = precur->next;
			precur->next = tmp;
			precur = tmp;
		}
	}
	precur->next = xn->next;
	free(xn);
}

//设计一个算法，判断La是否为Lb的子链，子链的定义为La中的从前到后的所有结点的数据都按照原有的顺序出现在Lb中
bool isSubLink(LinkList La, LinkList Lb) {
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pstart = Lb->next;
	while (pa != NULL && pb != NULL)
	{
		if (pa->data == pb->data) {
			pa = pa->next;
			pb = pb->next;
		}
		else
		{
			pa = La->next;
			pstart = pstart->next;
			pb = pstart;
		}
	}
	if (pa == NULL)
	{
		return true;
	}
	return false;
}

//两个单词有相同的后缀是可以共享相同后缀的存储空间，例如'act'和'dict'。设La和Lb分别指向两个单词所在单链表的头结点，设计算法查找公共后缀的起始位置。
int getLength(LinkList L) {
	int count = 1;
	LinkList p = L;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}
LinkNode* getSameNode(LinkList La, LinkList Lb) {
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	int lenA = getLength(La);
	int lenB = getLength(La);
	if (lenA > lenB)
	{
		for (int i = 0; i < lenA - lenB; i++)
		{
			pa = pa->next;
		}
	}
	else
	{
		for (int i = 0; i < lenB - lenA; i++)
		{
			pb = pb->next;
		}
	}
	while (pa != pb)
	{
		pa = pa->next;
		pb = pb->next;
	}
	return pa;
}

//长度为n的单链表，请给出单链表的存储结构并用C语言编写时间复杂度和空间复杂度最小的算法将单链表转换为要求顺序
// 1 2 3 4 5 6 7 8 9 10 -> 1 10 2 9 3 8 4 7 5 6
void convertLink(LinkList L, int n) {
	LinkList start = L->next;
	LinkList tail = start;
	L->next = NULL;
	LinkList pre = L;
	for (int i = 0; i < (n - 1) / 2; i++)
	{
		tail = tail->next;
	}
	LinkList p = tail->next;
	tail->next = NULL;
	while (p != NULL)
	{
		LinkList tmp = p;
		p = p->next;
		tmp->next = tail->next;
		tail->next = tmp;
	}
	tail = tail->next;
	for (int i = 0; i < n; i++)
	{
		LinkList tmp;
		if (i % 2) {
			tmp = tail;
			tail = tail->next;
		}
		else
		{
			tmp = start;
			start = start->next;
		}
		tmp->next = pre->next;
		pre->next = tmp;
		pre = tmp; /
	}
	pre->next = NULL;
}
int  main() {
	LinkList L = NULL;
	int s[] = { 1,2,3,4,6,5,7,8,9,10,11 };
	TailInsert(L, s, 11);
	convertLink(L, 11);
}