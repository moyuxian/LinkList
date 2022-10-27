#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
	int data;
	struct LinkNode* next;
}LinkNode, * LinkList;

//ͷ�巨
void HeadInsert(LinkList& L, int x) {
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	p->data = x;
	p->next = L->next;
	L->next = p;
}

//β�巨��������
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

//��֪LΪ��ͷ���ĵ������밴�յݹ��˼��ʵ����������
/*
1)�������е��������
2)�������еĽ����
3)������������Ԫ�ص�ƽ��ֵ
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

//��������ʵ�i�����ݽ��
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

//��i�����ǰ����Ԫ��e
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

//����㷨��Ч���Ҵ�ͷ��㵥��������m��λ�õĽ�㲢����ý��ֵ
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

//��ָ֪��La��Lb�ֱ�ָ��������ͷ���ĵ�������д������ɴ�La��ɾ����j����㿪ʼ�Ĺ�len��Ԫ�ز�����len��Ԫ�ز��뵽��Lb�е�j��Ԫ��֮ǰ
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

//�ߵ������ͷָ��ΪL�����������Ϊ�ַ������ʱ�临�Ӷ���͵��㷨�ж�ǰn/2���ַ��Ƿ�Ϊ��n/2�ַ�������ͬ������xyx��xyxy ǰһ���ַ����һ���ַ���ͬ��
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
//�ӷǵݼ�����������ɾ��ֵ��ͬ�Ķ���Ԫ��
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

//����һ���ǵݼ������������������ظ�����������㷨ȷ����xС�Ľ�����ݣ��ظ���ֻ��һ������������1 2 2 3 4 6 7 ��xΪ4 �򷵻� 3��
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

//ɾ���ǵݼ�������La��La��Lb��ͬ��Ԫ��
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

//��֪LaLbLc �����������������Ѿ���ʼ������Ԫ�ص���˳�����У�ÿ�����о����ظ�Ԫ�أ�����㷨�ڱ�LC��ɾ��ͬʱ������La��Lb�е�����Ԫ��
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

//La��Lb��ֵ�ǵݼ����鲢La��Lb���õ��µĵ�����Lc��ʹ��LcҲ��ֵ�ǵݼ��Ҳ����ظ�Ԫ�أ���ռ��ԭ���Ŀռ䡣
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

//��ͷ���ĵ�����������Ԫ�ص�����ֵ������˳�����У�ɾ�������д���min��С��max��Ԫ��
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

//������ʹ��ð������
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

//��LΪ������ͷ����ַ�������ݽ�㶼�����������ܴ�����ͬ��ֵ�Ľ�㣬���һ���ռ临�Ӷ���͵��㷨������ֱ�Ӳ�������Ѹ��������������������������ظ����ɾ��
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

//����ͷ�������С��x��Ԫ�ض�����ǰ�棬���д���x�Ķ����ں���
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

//���һ���㷨���ж�La�Ƿ�ΪLb�������������Ķ���ΪLa�еĴ�ǰ��������н������ݶ�����ԭ�е�˳�������Lb��
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

//������������ͬ�ĺ�׺�ǿ��Թ�����ͬ��׺�Ĵ洢�ռ䣬����'act'��'dict'����La��Lb�ֱ�ָ�������������ڵ������ͷ��㣬����㷨���ҹ�����׺����ʼλ�á�
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

//����Ϊn�ĵ����������������Ĵ洢�ṹ����C���Ա�дʱ�临�ӶȺͿռ临�Ӷ���С���㷨��������ת��ΪҪ��˳��
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