#include "Queue.h"

template<typename type>
Queue<type>::Queue() {
    first = nullptr;
    last = nullptr;
    mySize = 0;
}

template<typename type>
Queue<type>::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

template<typename type>
void Queue<type>::dequeue() {
    if (isEmpty()) {
        return;
    }
    QueueNode<type>* temp = first;
    first = first->next;
    delete temp;
    mySize--;
}

template<typename type>
void Queue<type>::enqueue(const type& data) {
    if (isEmpty()) {
        first = new QueueNode(data);
        last = first;
        mySize++;
        return;
    }
    QueueNode<type>* temp = first;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new QueueNode(data);
    last = temp->next;
    mySize++;
}

template<typename type>
bool Queue<type>::isEmpty() const{
    return first == nullptr;
}

template<typename type>
type Queue<type>::front() const{
    if (isEmpty()) {
        return nullptr;
    }
    return first->data;
}

template<typename type>
int Queue<type>::size() const{
    return mySize;
}