
#include "main.hpp"


/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
class List {
public:
    //! Hàm của thầy
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    //! Hàm hỗ trợ thêm
    virtual List<T>* subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0; 
    virtual double distanceEuclidean(const List<T>* image) = 0;
};

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
        //TODO: implement task 1
        Node* newNode = new Node(value, nullptr);
        if(!head) head = tail = newNode;
        else{
            tail->next = newNode;
            tail = tail->next;
        }
        size++;
    }
    void push_front(T value) {
        //TODO: implement task 1
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
        //TODO: implement task 1
        Node* newNode = new Node(value, nullptr);
        if(!head) {
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
        //TODO: implement task 1
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
        //TODO: implement task 1
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
        //TODO: implement task 1
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
        //TODO: implement task 1
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

    void printStartToEnd(int start, int end) const{
        Node* temp = head;
        for(int i = start; i < end && i < this->size; i++)
        {
            if(i == end - 1 || i == this->size - 1) OUTPUT << temp->pointer << endl;
            else OUTPUT << temp->pointer << " ";
        }
    } 

    List<T>* subList(int start, int end){

        if (start < 0 || start >= this->size || end <= start) return nullptr;
        List<T>* result = new Image<T>();

        //TODO: implement task 1
        //^ gợi ý: dùng push_back
        end = min(end, this->size);
        Node* ptr = head;
        for (int i = 0; i < start; ++i) {
            ptr = ptr->next;
        }
        for (int i = start; i < end; ++i) {
            result->push_back(ptr->pointer);
            ptr = ptr->next;
        }
        return result;
    }

    double distanceEuclidean(const List<T>* image){
        double distance = 0.0;
        //TODO: implement task 1
        //^ gợi ý dùng length, get
        if (this->length() != image->length()) {
            int i = 0;
            int count = min(this->length(), image->length());
            for (i; i < count; ++i) {
                T diff = this->get(i) - image->get(i);
                distance += diff * diff;
            }
            if(this->length() < image->length()){
                for (i; i < image->length(); i++) {
                    distance += image->get(i) * image->get(i);
                } 
            } else {
                for (i; i < this->length(); i++) {
                    distance += this->get(i) * this->get(i);
                }
            }
        } else {
            for (int i = 0; i < this->length(); ++i) {
                T diff = this->get(i) - image->get(i);
                distance += diff * diff;
            }
        }
        return sqrt(distance);
    }
};


class Dataset {
private:
    List<List<int>*>* data;
    string* NameCol;
    //You may need to define more
public:
    //! Hàm của thầy
    Dataset();
    ~Dataset();
    Dataset(List<List<int>*>* data, string* NameCol);
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void getShape(int& nRows, int& nCols) const;
    void columns() const;




    void printHead(int nRows = 5, int nCols = 5) const
    {
        //TODO: implement task 2
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        //TODO: implement task 2
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        //TODO: implement task 2
        return true;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        //TODO: implement task 2
        return *this;
    }

    int predict(const List<int>* image)
    {
        //TODO: implement task 2
        return 1;
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5):k(5){};
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed