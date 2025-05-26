#include <iostream>
#include <string>

using namespace std;

class Stack {
private:
    struct Node {
        int value;
        Node* ptr;

        Node(int data) : value(data), ptr(nullptr) {}
    };

    Node* head;
    int size;

public:
    Stack() : head(nullptr), size(0) {}
    
    void clear() {
        while (size > 0) {
            Node* temp = head;
            head = head->ptr;
            delete temp;
            size--;
        }
        cout << "ok" << endl;
    }

    void push(int data) {
        Node* new_node = new Node(data);
        new_node->ptr = head;
        head = new_node;
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
        head = head->ptr;
        delete temp;
        size--;
    }

    void back() {
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
    
    Stack st;
    
    while (true) {
        cin >> type;
        if (type == "exit") {
            cout << "bye" << endl;
            break;
        }
        else if (type == "pop") {
            st.pop();
        } 
        else if (type == "clear") {
            st.clear();
        } 
        else if (type == "size") {
            st.psize();
        } 
        else if (type == "back") {
            st.back();
        } 
        else if (type == "push") {
            cin >> data;
            st.push(data);
        }
        else {
            cout << "error" << endl;
        }
    }
    return 0;
}