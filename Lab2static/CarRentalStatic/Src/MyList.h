#pragma once

#include "Car.h"

typedef Car ElemType;
typedef struct MyList {
    ElemType elems[50];
    int lg;
} MyList;


/*
  Create an empty list
*/
MyList createEmpty();

/*
  Destroy list
*/
void destroyList(MyList* l);

/*
  Get an element from the list
  @param pos - position of the element, need to be valid
  @return Element from the given position, or NULL if pos is not valid
*/
ElemType get(MyList* l, int pos);

/*
  @return Number of elements in the list
*/
int size(MyList* l);

/*
  Add element at the end of the list
  @return errorno if memory allocation fails, 0 otherwise
*/
int pushBack(MyList* l, ElemType el);

void testCreateDestroyList();
void testIterateList();
void testAllList();