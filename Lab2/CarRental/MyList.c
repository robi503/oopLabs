#include "MyList.h"


MyList* createEmpty(int type) {
    MyList* l = malloc(sizeof(MyList));
    if (l) {
        l->capacity = 5;
        l->lg = 0;
        l->elems = (ElemType*)malloc(sizeof(ElemType) * l->capacity);
        l->type = type;
    }
    return l;
}


void destroyList(MyList* l) {
    for (int i = 0; i < l->lg;i++) {
        destroyCar(l->elems[i]);
    }
    free(l->elems);
    free(l);
}


ElemType get(MyList* l, int pos) {
    if (pos >= l->lg || pos < 0) {
        return NULL;
    }
    return l->elems[pos];
}


int size(MyList* l) {
    return l->lg;
}


int pushBack(MyList* l, ElemType el) {
    if (l->lg >= l->capacity) { // Check if capacity is sufficient
        // Double the capacity
        if (l->type == 1) {
            l->capacity *= 2;
            ElemType* temp = (ElemType*)realloc(l->elems, sizeof(ElemType) * l->capacity); // Reallocate memory
            if (temp == NULL) {
                // Reallocation failed
                return errno; // Return the error code
            }
            l->elems = temp;
        }
        else {
            destroyCar(el);
            return -1;
        }
    }
    l->elems[l->lg] = el;
    l->lg++;
    return 0;
}


void testCreateDestroyList() {
    MyList* l = createEmpty(1);
    assert(l != NULL);
    assert(l->capacity == 5);
    assert(l->lg == 0);
    assert(l-> type == 1);
    destroyList(l);
}


void testIterateList() {
    MyList* l = createEmpty(1);
    pushBack(l, createCar("bc10abc", "a", "aa"));
    pushBack(l, createCar("vn02zzz", "b", "bb"));
    pushBack(l, createCar("cj10abc", "a", "aa"));
    pushBack(l, createCar("ab02zzz", "b", "bb"));
    pushBack(l, createCar("cj10abc", "a", "aa"));
    pushBack(l, createCar("ab02zzz", "b", "bb"));
    assert(size(l) == 6);

    MyList* lStatic = createEmpty(0);
    pushBack(lStatic, createCar("bc10abc", "a", "aa"));
    pushBack(lStatic, createCar("vn02zzz", "b", "bb"));
    pushBack(lStatic, createCar("cj10abc", "a", "aa"));
    pushBack(lStatic, createCar("ab02zzz", "b", "bb"));
    pushBack(lStatic, createCar("cj10abc", "a", "aa"));
    assert(pushBack(lStatic, createCar("ab02zzz", "b", "bb")) == -1);
    assert(size(lStatic) == 5);

    assert(strcmp(get(l, 0)->licensePlate, "BC10ABC") == 0);
    assert(strcmp(get(l, 1)->licensePlate, "VN02ZZZ") == 0);
    assert(strcmp(get(l, 2)->licensePlate, "CJ10ABC") == 0);
    assert(strcmp(get(l, 3)->licensePlate, "AB02ZZZ") == 0);

    assert(get(l, -1) == NULL);
    assert(get(l, 7) == NULL);

    destroyList(l);
    destroyList(lStatic);
}

void testAllList() {
    testCreateDestroyList();
    testIterateList();
}
