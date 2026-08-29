#include "TQueue.h"
#include <iostream>

// Constructor.
template <typename T>
TQueue<T>::TQueue(const int maxQueueSize_) {
    this->maxQueueSize = maxQueueSize_;
    this->elements = new T[maxQueueSize_];
    this->frontIndex = 0;
    this->rearIndex = -1;
    this->currentQueueSize = 0;
}

// Destructor.
template <typename T>
TQueue<T>::~TQueue() {
    delete[] this->elements;
}

// Returns true if the queue is empty.
template <typename T>
bool TQueue<T>::isQueueEmpty() const {
    return currentQueueSize == 0;
}

// Returns true if the queue is full.
template <typename T>
bool TQueue<T>::isQueueFull() const {
    return currentQueueSize == maxQueueSize;
}

// Enqueue element to the queue.
template <typename T>
void TQueue<T>::enqueue(const T& x) {
    if (isQueueFull()) {
        std::cout << "Queue overflow!" << std::endl;
        return;
    }

    rearIndex = (rearIndex + 1) % maxQueueSize;
    elements[rearIndex] = x;
    currentQueueSize++;
}

// Dequeue element from the front. Returns removed element.
template <typename T>
T TQueue<T>::dequeue() {
    if (isQueueEmpty()) {
        std::cout << "Queue underflow!" << std::endl;
        return T();
    }

    T res = elements[frontIndex];
    frontIndex = (frontIndex + 1) % maxQueueSize;
    currentQueueSize--;
    return res;
}

// Peek at the front of the queue.
template <typename T>
T TQueue<T>::front() const {
    if (isQueueEmpty()) {
        std::cout << "Queue underflow!" << std::endl;
        return T();
    }

    return elements[frontIndex];
}

// Template declarations.
template class TQueue<short>;
template class TQueue<int>;
template class TQueue<double>;
template class TQueue<unsigned short>;