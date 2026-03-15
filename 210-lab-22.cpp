#include <iostream>
#include <cstdlib>
using namespace std;
const int MIN_NR = 10,
    MAX_NR = 99,
    MIN_LS = 5,
    MAX_LS = 20;
class DoublyLinkedList {
    private: struct Node {
        int data;
        Node * prev;
        Node * next;
        Node(int val, Node * p = nullptr, Node * n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node * head;
    Node * tail;

    public:
        // constructor
        DoublyLinkedList() {
            head = nullptr;
            tail = nullptr;
        }
    void push_back(int value) {
        Node * newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty.
            head = tail = newNode;
        else {
            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;
        }
    }
    void push_front(int value) {
        Node * newNode = new Node(value);
        if (!head) // if there's no head, the list is empty.
            head = tail = newNode;
        else {
            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;
        }
    }
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node * newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node * temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp -> next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode -> next = temp -> next;
        newNode -> prev = temp;
        if (temp -> next)
            temp -> next -> prev = newNode;
        else
            tail = newNode; // Inserting at the end.
        temp -> next = newNode;
    }
    void delete_value(int value) {
        if (!head)
            return; // Empty list.
        Node * temp = head;
        while (temp && temp -> data != value)
            temp = temp -> next;
        if (!temp) {
            cout << "Value not found in the list.\n";
            return; // Value not found.
        }
        if (temp -> prev) {
            temp -> prev -> next = temp -> next;
        } else {
            head = temp -> next; // Deleting the head.
        }
        if (temp -> next) {
            temp -> next -> prev = temp -> prev;
        } else {
            tail = temp -> prev; // Deleting the tail.
        }
        delete temp;
    }
    void delete_pos(int position) // Deletes node by position rather than value.
    {
        if (position < 0) // Validate position.
        {
            cout << "Position must be >= 0." << endl;
            return;
        }
        if (!head) // If the list is empty, there's nothing to delete.
            return;
        Node * temp = head;
        for (int i = 0; i < position && temp; ++i) // Traverse to the node at the specified position.
            temp = temp -> next;
        if (!temp) // If the position exceeds the list size, do nothing.
        {
            cout << "Position exceeds list size. Node not deleted.\n";
            return;
        }
        if (temp -> prev) // If the node to delete is not the head, update the previous node's next pointer.
        {
            temp -> prev -> next = temp -> next;
        } else // If the node to delete is the head, update the head pointer.
        {
            head = temp -> next; // Deleting the head.
        }
        if (temp -> next) // If the node to delete is not the tail, update the next node's previous pointer.
        {
            temp -> next -> prev = temp -> prev;
        } else // If the node to delete is the tail, update the tail pointer.
        {
            tail = temp -> prev; // Deleting the tail.
        }
        delete temp;
    }
    void pop_front() {
        if (!head)
            return; // Empty list.
        Node * temp = head; // Store the current head to delete later.
        head = head -> next; // Move head to the next node.
        if (head) // If the list is not empty after moving head, update the new head's previous pointer.
            head -> prev = nullptr; // Update the new head's previous pointer.
        else
            tail = nullptr; // List is now empty, so update tail as well.
        delete temp; // Pops the old head node.
    }
    void pop_back() {
        if (!tail)
            return; // Empty list.
        Node * temp = tail; // Store the current tail to delete later.
        tail = tail -> prev; // Move tail to the previous node.
        if (tail) // If the list is not empty after moving tail, update the new tail's next pointer.
            tail -> next = nullptr; // Update the new tail's next pointer.
        else
            head = nullptr; // List is now empty, so update head as well.
        delete temp; // Pops the old tail node.
    }
    void print() {
        Node * current = head;
        if (!current) // If the list is empty, print a message and return.
        {
            cout << "List is empty.\n";
            return;
        }
        while (current) {
            cout << current -> data << " ";
            current = current -> next;
        }
        cout << endl;
    }
    void print_reverse() {
        Node * current = tail;
        if (!current) {
            cout << "List is empty.\n";
            return;
        }
        while (current) {
            cout << current -> data << " ";
            current = current -> prev;
        }
        cout << endl;
    }
    ~DoublyLinkedList() {
        while (head) {
            Node * temp = head;
            head = head -> next;
            delete temp;
        }
    }
};
// Driver program
int main() {
    srand(time(0)); // Seed the random number generator.
    DoublyLinkedList list; // Create an instance of the DoublyLinkedList class.
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS; // Generate a random size for the list between MIN_LS and MAX_LS.
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
    cout << "List forward: ";
    list.print();
    list.pop_front();
    cout << "After pop_front: \n";
    list.print();
    cout << "After pop_back: \n";
    list.pop_back();
    list.print();
    cout << "Deleting value at position 2: \n";
    list.delete_pos(2);
    list.print();
    cout << "Looking for value 10 and deleting it if found: \n";
    list.delete_value(10);
    list.print();
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    list.print();
    return 0;
}