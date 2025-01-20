#ifndef QUEUE_H
#define QUEUE_H

template<typename type>
struct QueueNode {
    type data;
    QueueNode(type value) : data(value), next(nullptr) {}
    QueueNode* next;
};

template<typename type>
class Queue {
private:
    QueueNode<type> *first;
    QueueNode<type> *last;
    int mySize;

public:
    Queue();
    ~Queue();
    void enqueue(const type&);
    void dequeue();
    type front() const;
    bool isEmpty() const;
    int size() const;
};



#endif //QUEUE_H