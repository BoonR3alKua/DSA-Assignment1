#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

template<typename T>
class Image : public List<T>
{
private:
    class Node{
    public:
        T pointer;
        Node* next;
    public:
        Node(T pointer, Node* next = nullptr) : pointer(pointer), next(next) {}
    };
private:
    Node* head;
    Node* tail;
    int size;
public:
    Image(){
        head = tail = nullptr;
        size = 0;
    }
    ~Image(){
        this->clear();
    }
    void push_back(T value){
        Node* newNode = new Node(value, nullptr);
        if(!head) head = tail = newNode;
        else{
            tail->next = newNode;
            tail = tail->next;
        }
        size++;
    }
    void push_front(T value) {
        Node* newNode = new Node(value, nullptr);
        if(!head) head = tail = newNode;
        else{
            newNode->next = head;
            head = newNode;
        }
        size++;       
    }
    void insert(int index, T value){
        if(index < 0 || index > size) return;
        Node* newNode = new Node(value, nullptr);
        if(!head && index == 0) {
            head = tail = newNode;
        } else if(index == 0) {
            newNode->next = head;
            head = newNode;
        } else if(index == size) {
            tail->next = newNode;
            tail = newNode;
        } else {
            Node* ptr = head;
            for(int i = 0; i < index - 1; ++i){
                ptr = ptr->next;
            }
            Node* next = ptr->next;
            ptr->next = newNode;
            newNode->next = next;
        }
        size++;
    }
    void remove(int index){
        if(index < 0 || index >= size) return;
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (size == 1) tail = nullptr;
        } else {
            Node* prev = nullptr;
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                prev = current;
                current = current->next;
            }
            prev->next = current->next;
            if (index == size - 1) tail = prev;
            delete current;
        }
        size--;
    }


    T& get(int index) const{
        if(index < 0 || index >= this->size) throw std::out_of_range("get(): Out of range");
        Node* ptr = head;
        for(int i = 0; i < index; ++i){
            ptr = ptr->next;
        }
        return ptr->pointer;
    }

    int length() const{
        return size;
    }

    void clear(){
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    void print() const {
        if(size == 0) OUTPUT << "nullptr" << endl;
        Node* temp = head;
        for(int i = 0; i < this->size; i++)
        {
            if(i == this->size - 1) OUTPUT << temp->pointer << endl;
            else OUTPUT << temp->pointer << " ";
            temp = temp->next;
        }
    }

    void reverse(){  
        Node* current = head;
        Node* prev = nullptr;
        Node* next = nullptr;
        tail = head;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
};