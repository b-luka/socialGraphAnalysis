#include "TStack.h"
#include <iostream>

// Constructor.
template <typename T>
TStack<T>::TStack(const int maxStackSize_) {
    this->maxStackSize = maxStackSize_;
    this->elements = new T[maxStackSize_];
    this->sp = -1;
}

// Destructor.
template <typename T>
TStack<T>::~TStack() {
    delete[] this->elements;
}

// Returns true if the stack is empty.
template <typename T>
bool TStack<T>::isStackEmpty() const {
    return sp == -1;
}

// Push element to stack.
template <typename T>
void TStack<T>::push(const T& x) {
    if (this->sp >= this->maxStackSize) {
        std::cout << "Stack overflow!" << std::endl;
        return;
    }

    this->sp++;
    this->elements[sp] = x;
}

// Remove element from top. Returns removed element.
template <typename T>
T TStack<T>::pop() {
    if (isStackEmpty()) {
        std::cout << "Stack underflow!" << std::endl;
        return T();
    }

    int res = this->elements[sp];
    this->sp--;
    return res;
}

// Peek at the top of the stack.
template <typename T>
T TStack<T>::top() {
    if (isStackEmpty()) {
        std::cout << "Stack underflow!" << std::endl;
        return T();
    }

    return this->elements[sp];
}

// Template declarations.
template class TStack<short>;
template class TStack<int>;
template class TStack<double>;
template class TStack<unsigned short>;