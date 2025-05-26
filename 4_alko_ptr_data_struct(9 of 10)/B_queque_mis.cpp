#include <iostream>
#include <string>

using namespace std;

class Deque {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;

        Node(int data) : value(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    Deque() : head(nullptr), tail(nullptr), size(0) {}
    
    void clear() {
        while (size > 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
        tail = nullptr;
        cout << "ok" << endl;
    }

    void push(int data) {
        Node* new_node = new Node(data);
        if (size == 0) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        size++;
        cout << "ok" << endl;
    }

    void pop() {
        if (size == 0) {
            cout << "error" << endl;
            return;
        }
        Node* temp = head;
        cout << temp->value << endl;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void front() {
        if (size > 0) {
            cout << head->value << endl;
        } else {
            cout << "error" << endl;
        }
    }

    void psize() {
        cout << size << endl;
    }

};

int main() {
    string type;
    int data;
    
    Deque dq;
    
    while (true) {
        cin >> type;
        if (type == "exit") {
            cout << "bye" << endl;
            break;
        }
        else if (type == "pop") {
            dq.pop();
        } 
        else if (type == "clear") {
            dq.clear();
        } 
        else if (type == "size") {
            dq.psize();
        } 
        else if (type == "front") {
            dq.front();
        } 
        else if (type == "push") {
            cin >> data;
            dq.push(data);
        }
        else {
            cout << "error" << endl;
        }
    }
    return 0;
}