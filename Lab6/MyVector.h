#include <stdexcept>


template<typename T>
class MyVector {
private:
    int capacity;
    int _size;
    T* elements;
    void resize();
public:
    // constructor
    MyVector();

    // add element at the end
    void pushBack(T e);

    // delete element at position i and return the deleted element
    void erase(int i);

    // returns the size of the vector
    int size() const;

    // overloaded subscript operator for element access
    T& operator[](int index) const;

    // destructor
    ~MyVector();
};


template<typename T>
MyVector<T>::MyVector() {
    capacity = 1; // initial capacity
    _size = 0; // initial size
    elements = new T[capacity]; // allocate memory for elements
}

template<typename T>
void MyVector<T>::pushBack(T e) {
    if (_size == capacity) {
        resize(); // if capacity is reached, resize the vector
    }
    elements[_size++] = e; // add the element at the end and increment size
}

template<typename T>
void MyVector<T>::erase(int i) {
    if (i < 0 || i >= _size) {
        throw std::out_of_range("Index out of range");
    }
    // Shift elements to the left starting from position i
    for (int j = i; j < _size - 1; ++j) {
        elements[j] = elements[j + 1];
    }
    // Decrease the size of the vector
    _size--;
}

template<typename T>
int MyVector<T>::size() const {
    return _size;
}

template<typename T>
T& MyVector<T>::operator[](int index) const {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] elements; // deallocate memory
}

template<typename T>
void MyVector<T>::resize() {
    int newCapacity = capacity * 2; // double the capacity

    // Allocate memory for the new array
    T* newElements = new T[newCapacity];

    // Copy elements from the old array to the new array
    for (int i = 0; i < _size; ++i) {
        newElements[i] = elements[i];
    }

    // Deallocate memory occupied by the old array
    delete[] elements;

    // Update the elements pointer to point to the new array
    elements = newElements;

    // Update the capacity
    capacity = newCapacity;
}