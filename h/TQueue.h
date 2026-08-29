#ifndef ALGPROJECT_TQUEUE_H
#define ALGPROJECT_TQUEUE_H

// Generic queue. Sequential implementation.
template <typename T>
class TQueue {
public:
    // Constructor.
    TQueue(const int maxQueueSize_);

    // Destructor.
    ~TQueue();

    // Enqueue element to the queue.
    void enqueue(const T& x);

    // Dequeue element from the front. Returns removed element.
    T dequeue();

    // Peek at the front of the queue.
    T front() const;

    // Returns true if the queue is empty.
    bool isQueueEmpty() const;

    // Returns true if the queue is full.
    bool isQueueFull() const;

private:
    // Internal element array.
    T* elements;

    // Pointer to the front of the queue.
    int frontIndex;

    // Pointer to the rear of the queue.
    int rearIndex;

    // Maximum queue size.
    int maxQueueSize;

    // Current queue size.
    int currentQueueSize;
};

#endif
