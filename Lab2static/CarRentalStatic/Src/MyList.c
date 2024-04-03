#include "MyList.h"


MyList createEmpty() {
    MyList l;
    l.lg = 0;
    return l;
}


void destroyList(MyList* l) {
    for (int i = 0; i < l->lg; i++) {
        destroyCar(&l->elems[i]);
    }
}


ElemType get(MyList* l, int pos) {
    return l->elems[pos];
}


int size(MyList* l) {
    return l->lg;
}


int pushBack(MyList* l, ElemType el) {
    if (l->lg == 50) {
        return -1;
    }
    l->elems[l->lg] = el;
    l->lg++;
    return 0;
}


void testCreateDestroyList() {
    MyList l = createEmpty();
    assert(l.lg == 0);
    destroyList(&l);
}


void testIterateList() {
    MyList l = createEmpty();
    pushBack(&l, createCar("bc10abc", "a", "aa"));
    pushBack(&l, createCar("vn02zzz", "b", "bb"));
    pushBack(&l, createCar("cj10abc", "a", "aa"));
    pushBack(&l, createCar("ab02zzz", "b", "bb"));
    pushBack(&l, createCar("cj10abc", "a", "aa"));
    pushBack(&l, createCar("ab02zzz", "b", "bb"));
    assert(size(&l) == 6);


    assert(strcmp(get(&l, 0).licensePlate, "BC10ABC") == 0);
    assert(strcmp(get(&l, 1).licensePlate, "VN02ZZZ") == 0);
    assert(strcmp(get(&l, 2).licensePlate, "CJ10ABC") == 0);
    assert(strcmp(get(&l, 3).licensePlate, "AB02ZZZ") == 0);

    destroyList(&l);
}

void testAllList() {
    testCreateDestroyList();
    testIterateList();
}
