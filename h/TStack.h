#ifndef ALGPROJECT_TSTACK_H
#define ALGPROJECT_TSTACK_H

// Generic stack. Sequential implementation.
template <typename T>
class TStack {
public:
    // Constructor.
    TStack(const int maxStackSize_);

    // Destructor.
    ~TStack();

    // Push element to stack.
    void push(const T& x);

    // Peek at the top of the stack.
    T top();

    // Remove element from top. Returns removed element.
    T pop();
    
    // Returns true if the stack is empty.
    bool isStackEmpty() const;

private:
    // Internal element array.
    T* elements;

    // Pointer to the top of the stack.
    int sp;

    // Maximum stack size.
    int maxStackSize;
};

#endif
