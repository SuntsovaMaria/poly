#pragma once
#include <iostream>
template <typename T>
class node {
public:
    T data;
    node<T>* next;

    node() : next(nullptr) {}
    node(const T& item, node<T>* ptr = nullptr) :
        data(item), next(ptr) {}
};

template <typename T>
class list {
public:
    list() {
        head = tail = new node<T>();
    }
    
  
    
    list& operator=(const list& other) {
        if (this != &other) {
            list tmp(other);
            std::swap(head, tmp.head);
            std::swap(tail, tmp.tail);
        }
        return *this;
    }
    list& operator=(list&& other) noexcept {
       std:: swap(*this, other);
        return *this;
    }
    ~list() {
        while (head->next != nullptr) {
            node<T>* next = head->next;
            delete head;
            head = next;
        }
        delete head;
    }

    list(const list& other) {
        if (other.head != nullptr) {
            head = new node<T>(other.head->data, nullptr);
            tail = head;
        }
        else {
            head = tail = nullptr;
        }
        node<T>* current = other.head->next;
        while (current != nullptr) {
            tail->next = new node<T>(current->data, nullptr);
            tail = tail->next;
            current = current->next;
        }
       
    }


    
    class iterator {
        friend class list;
    private:
        node<T>* nodePtr;
        iterator(node<T>* newPtr) : nodePtr(newPtr) {}
    public:
        iterator() : nodePtr(nullptr) {}

        bool operator!=(const iterator& itr) const {
            return nodePtr != itr.nodePtr;
        }

        T& operator*() const {
            return nodePtr->next->data;
        }

        iterator operator++(int) {
            iterator temp = *this;
            nodePtr = nodePtr->next;
            return temp;
        }
    };

    iterator begin() const {
        return iterator(head);
    }

    iterator end() const {
        return iterator(tail);
    }

    iterator insert(iterator position, const T& value) {
        node<T>* newNode = new node<T>(value, position.nodePtr->next);
        if (position.nodePtr == tail) tail = newNode;
        position.nodePtr->next = newNode;
        return position;
    }

    iterator erase(iterator position) {
        node<T>* toDelete = position.nodePtr->next;
        position.nodePtr->next = position.nodePtr->next->next;
        if (toDelete == tail) tail = position.nodePtr;
        delete toDelete;
        return position;
    }
    bool isempty() const {
        return head == tail;
    }
    

    bool operator!=(const list<T>& other) const {
        return !(*this == other);
    }

    void insertion_sort() {
        if (head->next == nullptr || head->next->next == nullptr) return;

        node<T>* sorted = head->next;
        head->next = nullptr;
        tail = head;

        while (sorted != nullptr) {
            node<T>* current = sorted;
            sorted = sorted->next;

            if (head->next == nullptr || head->next->data >= current->data) {
                current->next = head->next;
                head->next = current;
                if (tail == head) tail = current;
            }
            else {
                node<T>* temp = head->next;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
                if (current->next == nullptr) tail = current;
            }
        }
    }
    void reverse() {
        if (head == tail || head->next == nullptr) {
            return;  
        }
        node<T>* cur = head->next;
        node<T>* pr = nullptr;
        tail = cur; 
        while (cur != nullptr) {
            node<T>* next = cur->next;
            cur->next = pr;
            pr = cur;
            cur = next;
        }

        head->next = pr;
    }
    bool operator==(const list<T>& other) const {
        node<T>* current1 = head->next;
        node<T>* current2 = other.head->next;

        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data != current2->data) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return current1 == nullptr && current2 == nullptr;
    }

    
private:
    node<T>* head;
    node<T>* tail;
};