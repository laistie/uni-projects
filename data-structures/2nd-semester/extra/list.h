#include "libraries.h"
#include "info.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

#ifndef LIST_H
#define LIST_H

typedef void* List;
typedef void* ListNode;
typedef void* Element; //INFO FROM TREE NODE

List newList();
void insertList(List list, Element element);

int getListSize(List list);
bool checkIsInList(Element element);
bool checkIsEmptyList(List list);
Element getElementAtPos(int position);
Element getLastElement();

int getListSize();

void reportSelections(FILE* pTxt, FILE* pSvg);
void reportDeletions(FILE* pTxt);

void mergeLists(List l1, List l2);

void printList();

void freeList(List list);

#endif