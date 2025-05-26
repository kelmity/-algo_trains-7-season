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

    void push_front(int data) {
        Node* new_node = new Node(data);
        if (size == 0) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size++;
        cout << "ok" << endl;
    }

    void push_back(int data) {
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

    void pop_front() {
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

    void pop_back() {
        if (size == 0) {
            cout << "error" << endl;
            return;
        }
        Node* temp = tail;
        cout << temp->value << endl;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
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

    void back() {
        if (size > 0) {
            cout << tail->value << endl;
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
        else if (type == "pop_front") {
            dq.pop_front();
        }
        else if (type == "pop_back") {
            dq.pop_back();
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
        else if (type == "back") {
            dq.back();
        }
        else if (type == "push_front") {
            cin >> data;
            dq.push_front(data);
        }
        else if (type == "push_back") {
            cin >> data;
            dq.push_back(data);
        }
        else {
            cout << "error" << endl;
        }
    }
    return 0;
}