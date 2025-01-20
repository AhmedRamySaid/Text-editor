#include "Stack.h"

Stack::Stack() {
    first = nullptr;
}
Stack::~Stack() {
    if (Stack::isEmpty()) {
        return;
    }
    while (first != nullptr) {
        Stack::pop();
    }
}
void Stack::push(QString st) {
    Node *newNode = new Node(st);
    if (Stack::isEmpty()) {
        first = newNode;
        return;
    }
    newNode->next = first;
    first = newNode;
}
void Stack::pop() {
    if (Stack::isEmpty()) {
        return;
    }
    if (first->next == nullptr) {
        delete first;
        first = nullptr;
        return;
    }
    Node *temp = first->next;
    delete first;
    first = temp;
}
QString Stack::top() {
    if (Stack::isEmpty()) {
        return "";
    }
    return first->data;
}
bool Stack::isEmpty() {
    return first == nullptr;
}
void Stack::clear() {
    while(!Stack::isEmpty()) {
        Stack::pop();
    }
}