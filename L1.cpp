#include <iostream>
#include <string>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void addFirst(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void addAtIndex(int index, int value) {
        Node* newNode = new Node;
        newNode->data = value;

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1 && current != nullptr; i++) {
                current = current->next;
            }
            if (current != nullptr) {
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    void addLast(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void removeFirst() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void removeLast() {
        if (head != nullptr) {
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
            } else {
                Node* current = head;
                while (current->next->next != nullptr) {
                    current = current->next;
                }
                delete current->next;
                current->next = nullptr;
            }
        }
    }

    void removeAtIndex(int index) {
        if (index == 0) {
            removeFirst();
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1 && current != nullptr; i++) {
                current = current->next;
            }
            if (current != nullptr && current->next != nullptr) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
    }

    void updateAtIndex(int index, int value) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        if (current != nullptr) {
            current->data = value;
        }
    }

    int findByIndex(int index) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        if (current != nullptr) {
            return current->data;
        }
        return 0;
    }

    int findByValue(int value) {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }
};

int main() {
    LinkedList list;
    list.addFirst(10);
    list.addLast(20);
    list.addLast(30);
    list.addAtIndex(1, 15);

    std::cout << "Список:" << std::endl;
    std::cout << list.findByIndex(0) << std::endl;
    std::cout << list.findByIndex(1) << std::endl;
    std::cout << list.findByIndex(2) << std::endl;
    std::cout << list.findByIndex(3) << std::endl;

    list.removeFirst();
    list.removeLast();
    list.removeAtIndex(1);
    list.updateAtIndex(0, 100);

    std::cout << "Измененный список:" << std::endl;
    std::cout << list.findByIndex(0) << std::endl;
    return 0;
}
