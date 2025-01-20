#include <QMessageBox>
#ifndef STACK_H
#define STACK_H



class Stack {
    class Node {
    public:
        Node(QString st) {
            data = st;
            next = nullptr;
        }
        Node* next;
        QString data;
    };

public:
    Stack();
    ~Stack();
    void push(QString);
    void pop();
    void clear();
    QString top();
    bool isEmpty();

private:
    Node* first;
};



#endif //STACK_H
