#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int SLDataType;
typedef struct SeqList
{
	SLDataType* a;
	int size;
	int capacity;
}SeqList,*pSeqList;
void SeqListInit(SeqList* ps);                // 初始化顺序表
void SeqListDestroy(SeqList* ps);             // 销毁顺序表
void SeqListPrint(SeqList* ps);               // 打印顺序表
void SeqListPushBack(SeqList* ps, SLDataType x); // 尾插
void SeqListPushFront(SeqList* ps, SLDataType x);// 头插
void SeqListPopFront(SeqList* ps);                // 头删
void SeqListPopBack(SeqList* ps);                 // 尾删

int SeqListFind(pSeqList ps, SLDataType x);
void SeqListInsert(pSeqList ps, int pos, SLDataType x);
void SeqListErase(pSeqList ps, int pos);