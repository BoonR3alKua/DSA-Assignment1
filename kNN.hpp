
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
    List<string>* nameCol;
    //You may need to define more
public:
    //! Hàm khởi tạo
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
    }
    //! Hàm hủy
    ~Dataset()
    {
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset& other)
    {
        if (this == &other) { 
            return;
        }

        this->nameCol = new Image<string>();
        for(int i = 0; i < other.nameCol->length(); ++i) {
            this->nameCol->push_back(other.nameCol->get(i));
        }

        this->data = new Image<List<int>*>();
        for(int i = 0; i < other.data->length(); ++i) {
            List<int>* originalList = other.data->get(i);
            List<int>* newList = new Image<int>();

            for (int j = 0; j < originalList->length(); ++j) {
                newList->push_back(originalList->get(j));
            }

            this->data->push_back(newList);
        }
    }

    Dataset& operator=(const Dataset& other)
    {
        //TODO: implement Task 2
        this->nameCol = new Image<string>();
        for(int i = 0; i < other.nameCol->length(); ++i) {
            this->nameCol->push_back(other.nameCol->get(i));
        }

        this->data = new Image<List<int>*>();
        for(int i = 0; i < other.data->length(); ++i) {
            List<int>* originalList = other.data->get(i);
            List<int>* newList = new Image<int>();

            for (int j = 0; j < originalList->length(); ++j) {
                newList->push_back(originalList->get(j));
            }

            this->data->push_back(newList);
        }
        return *this;
    }
    bool loadFromCSV(const char* fileName)
    {   
        ifstream file(fileName);
        //* kiểm tra mở file
        if(file.is_open())
        {
            string str;
            int number;

            //* xử lý hàng đầu tiên chuyển , thành ' ' dùng thư viện stringstream
            file >> str;
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == ',') str[i] = ' ';
            }
            stringstream ss(str);  
            while(ss >> str) nameCol->push_back(str);

             //* xử lý các hàng còn lại , thành ' ' dùng thư viện stringstream
            while(file >> str)
            {
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') str[i] = ' ';
                }
                stringstream ss(str);  
                List<int>* temp = new Image<int>();
                while(ss >> number) temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int& nRows, int& nCols) const
    {
        //TODO: implement Task 2
        if (this->data->length() == 0) {
            nRows = 0;
            nCols = 0;
            return;
        }
        nRows = this->data->length();
        nCols = this->data->get(0)->length();
    }
    void columns() const
    {
        //TODO: implement Task 2
        nameCol->print();
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        if(nRows <= 0 || nCols <= 0) return;
        //TODO: implement Task 2
        if(nRows > data->length()) nRows = data->length();
        if(nCols > nameCol->length()) nCols = nameCol->length();

        nameCol->printStartToEnd(0, nCols);

        for (int i = 0; i < nRows - 1; ++i) {
            data->get(i)->printStartToEnd(0, nCols);
            cout << endl;
        }
        data->get(nRows - 1)->printStartToEnd(0, nCols);
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if(nRows <= 0 || nCols <= 0)  return;
        //TODO: implement Task 2
        if(nRows > data->length()) nRows = data->length();
        if(nCols > nameCol->length()) nCols = nameCol->length();
        
        nameCol->printStartToEnd(nameCol->length() - nCols, nameCol->length());

        for (int i = data->length() - nRows; i < data->length() - 1; ++i) {
            data->get(i)->printStartToEnd(data->get(i)->length() - nCols, data->get(i)->length());
            cout << endl;
        }
        data->get(data->length() - 1)->printStartToEnd(data->get(data->length() - 1)->length() - nCols, data->get(data->length() - 1)->length());
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        //TODO: implement Task 2
        if (data->length() == 0) return false;
        if(axis == 0) {
            if(index > -1 && index < data->length()) {
                data->remove(index);
                return true;
            }
        }else if (axis == 1) {
            int i = 0;
            while(columns[i] != 'x') {
                ++i;
            }
            columns[i] = ' ';
            stringstream ss(columns);
            string row, col;
            ss >> row >> col;
            int irow = stoi(row), icol = stoi(col);
            for(int i = 0; i < data->length(); ++i) {
                data->get(i)->remove(irow*icol);
            }
            nameCol->remove(irow*icol);
            return true;
        }
        return false;
        
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        //TODO: implement Task 2
    }


    double distanceEuclidean(const List<int>* x, const List<int>* y) const{
        //TODO: implement Task 2 copy code từ implement Task 1 chỉnh
    }


    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const
    {
       //TODO: implement Task 3 
       return Dataset();
    }
    double score(const Dataset& y_test) const
    {   
        //TODO: implement Task 3 
        return -1;
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5):k(k){};
    void fit(const Dataset& X_train, const Dataset& y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset& X_test)
    { 
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset& y_test, const Dataset& y_pred)
    {   
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset& X, Dataset& Y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test)
{
    //* phân chia X
    int nRowsX, nColsX;
    X.getShape(nRowsX, nColsX);
    X_train = X.extract(0, test_size * nRowsX, 0, -1);
    X_test = X.extract(test_size * nRowsX, -1 , 0, -1);

    //* phân chia Y
    int nRowsY, nColsY;
    Y.getShape(nRowsY, nColsY);
    Y_train = Y.extract(0, test_size * nRowsY, 0, -1);
    Y_test = Y.extract(test_size * nRowsY, -1 , 0, -1);
}
// Please add more or modify as needed