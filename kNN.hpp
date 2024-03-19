
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
    virtual T* getArray() const = 0;
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
        if(size == 0) return;
        Node* temp = head;
        for(int i = 0; i < this->size; i++) {
            if(i == this->size - 1) OUTPUT << temp->pointer;
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
        for(int i = 0; i < start; i++) temp = temp->next;
        
        for(int i = start; i < end && i < this->size; ++i)
        {
            if(i == end - 1 || i == this->size - 1) OUTPUT << temp->pointer;
            else OUTPUT << temp->pointer << " ";
            temp = temp->next;
        }
    } 

    List<T>* subList(int start, int end) {
        if (start < 0 || start >= this->size || end < start || head == nullptr) return nullptr;
        List<T>* result = new Image<T>();
        Node* ptr = head;
        for (int i = 0; i < start; ++i) {
            ptr = ptr->next;
        }
        if(ptr == nullptr) return nullptr;
        if (start == end) {
            result->push_back(ptr->pointer);
        } else {
            end = min(end, this->size);
            for (int i = start; i <= end && i <= this->size; ++i) {
                result->push_back(ptr->pointer);
                ptr = ptr->next;
            }
        }
        return result;
    }

    T* getArray() const {
        if (head == nullptr) return nullptr;
        T* arr = new T[this->size];
        Node* ptr = head;
        for (int i = 0; i < this->size; ++i) {
            if (ptr == nullptr) {
                delete[] arr;
                return nullptr;
            }
            arr[i] = ptr->pointer;
            ptr = ptr->next;
        }
        return arr;
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
        for (int i=0;i<data->length();i++){
            data->get(i)->clear();
        }

        for(int i = 0; i< data->length(); i++){
            delete this->data->get(i);
        }

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

    Dataset& operator=(const Dataset& other) {
        if (this != &other) {
            delete nameCol;
            for (int i = 0; i < data->length(); ++i) {
                delete data->get(i);
            }
            delete data;
            this->nameCol = new Image<string>();
            for (int i = 0; i < other.nameCol->length(); ++i) {
                this->nameCol->push_back(other.nameCol->get(i));
            }

            this->data = new Image<List<int>*>();
            for (int i = 0; i < other.data->length(); ++i) {
                List<int>* originalList = other.data->get(i);
                List<int>* newList = new Image<int>();
                for (int j = 0; j < originalList->length(); ++j) {
                    newList->push_back(originalList->get(j));
                }
                this->data->push_back(newList);
            }
        }
        return *this;
    }

    List<List<int> *> *getData() const
    {
        // ! UPDATE file thay
        return data;
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
        OUTPUT << endl;
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        int row = nRows, col = nCols;
        if(data->length() == 0) {
            this->columns();
            return;
        }
        if(nRows <= 0 || nCols <= 0) return;
        //TODO: implement Task 2
        if(nRows > this->data->length()) row = this->data->length();
        if(nCols > nameCol->length()) col = nameCol->length();

        if(nameCol->length() != 0)nameCol->printStartToEnd(0, col);
        OUTPUT << endl;
        col = nCols;
        if(nCols > this->data->get(0)->length()) col = this->data->get(0)->length();
        for (int i = 0; i < row; i++) {
            data->get(i)->printStartToEnd(0, col);
            if (i == row - 1) break;
            OUTPUT << endl;
        }
    }

    void printTail(int nRows = 5, int nCols = 5) const
    {
        if(data->length() == 0) {
            this->columns();
            return;
        }
        if(nRows <= 0 || nCols <= 0) return;
        //TODO: implement Task 2
        int tmpCols = nCols;
        if(nRows > data->length()) nRows = data->length();
        if(tmpCols > nameCol->length()) tmpCols = nameCol->length();
        
        nameCol->printStartToEnd(nameCol->length() - tmpCols, nameCol->length());
        OUTPUT << endl;

        for (int i = data->length() - nRows; i < data->length(); ++i) {
            tmpCols = nCols;
            if(tmpCols > nameCol->length()) tmpCols = nameCol->length();
            data->get(i)->printStartToEnd(data->get(i)->length() - tmpCols, data->get(i)->length());
            if(i != data->length() - 1)OUTPUT << endl;
        }
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        //TODO: implement Task 2
        if (data->length() == 0) return false;
        if(axis == 0) {
            if(index > -1 && index < data->length()) {
                data->get(index)->clear();
                delete data->get(index);
                data->remove(index);
                return true;
            }
        }else if (axis == 1) {
            if(columns == "") return false;
            int i = 0;
            while(i < nameCol->length()){
                if(columns == nameCol->get(i)) break;
                i++;
            }
            if(i == 0) {
                if(data->get(0)->length() == 1) {
                    for(int i = 0; i < data->length(); i++){
                        data->get(i)->clear();
                        delete data->get(i);
                    }
                    data->clear();
                }
                else {
                    for(i = 0; i < data->length(); ++i) {
                        data->get(i)->remove(0);
                    }
                    nameCol->remove(0);
                }
                return true;
            } else if (i < nameCol->length()) {
                int delCol = i;
                for(i = 0; i < data->length(); ++i) {
                    data->get(i)->remove(delCol);
                }
                nameCol->remove(delCol);
                return true;
            }
        }
        return false;
        
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        //TODO: implement Task 2
        int endR = endRow, endC = endCol;
        Dataset* subMatrix = new Dataset();
        if(this->data->length() == 0) return* subMatrix;
        if(endRow < 0 || endRow > data->length() - 1){
            endR = data->length() - 1;
        }
        if(endCol < 0 || endCol > data->get(0)->length() - 1){
            endC = data->get(0)->length() - 1;
        }
        if( startRow > endR || startCol > endC ||startRow > data->length() - 1 
            || startCol > data->get(0)->length() - 1) return* subMatrix;
        endC = endCol;
        if(endCol < 0 || endCol > nameCol->length() - 1){
            endC = nameCol->length() - 1;
        }
        if(startCol <= endC) subMatrix->nameCol = nameCol->subList(startCol, endC);
        else subMatrix->nameCol->push_back("");
        for(int i = startRow; i <= endR; ++i) {
            endC = endCol;
            if(endCol < 0 || endCol > data->get(i)->length() - 1){
                endC = data->get(i)->length() - 1;
            }
            subMatrix->data->push_back(data->get(i)->subList(startCol, endC));
        }
        return* subMatrix;
    }

    double distanceEuclidean(const List<int>* x, const List<int>* y) const{
        double distance = 0.0;
        int* arrX = x->getArray();
        int* arrY = y->getArray();
        //TODO: implement Task 2 copy code từ implement Task 1 chỉnh
        if (x->length() != y->length()) {
            int i = 0;
            int count = min(x->length(), y->length());
            for (i; i < count; ++i) {
                double diff = arrX[i] - arrY[i];
                distance += diff * diff;
            }
            if(x->length() < y->length()){
                for (i; i < y->length(); i++) {
                    distance += arrY[i] * arrY[i];
                } 
            } else {
                for (i; i < x->length(); i++) {
                    distance += arrX[i] * arrX[i];
                }
            }
        } else {
            for (int i = 0; i < x->length(); ++i) {
                double diff = arrX[i] - arrY[i];
                distance += diff * diff;
            }
        }
        delete[] arrX;
        delete[] arrY;
        return sqrt(distance);
    }

    void merge(double* array, int* label, int const left, int const mid,
           int const right) const {
        int const subArrayOne = mid - left + 1;
        int const subArrayTwo = right - mid;
    
        double  *leftArray = new double[subArrayOne],
                *rightArray = new double[subArrayTwo];
        int     *leftLabelArray = new int[subArrayOne],
                *rightLabelArray = new int[subArrayTwo];

        for (auto i = 0; i < subArrayOne; i++){
            leftArray[i] = array[left + i];
            leftLabelArray[i] = label[left + i];
        }
            
        for (auto j = 0; j < subArrayTwo; j++){
            rightArray[j] = array[mid + 1 + j];
            rightLabelArray[j] = label[mid + 1 + j];
        }
            
    
        auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
        int indexOfMergedArray = left;

        while (indexOfSubArrayOne < subArrayOne
            && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne]
                <= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
                label[indexOfMergedArray]
                    = leftLabelArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
                label[indexOfMergedArray]
                    = rightLabelArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }

        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            label[indexOfMergedArray]
                = leftLabelArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            label[indexOfMergedArray]
                = rightLabelArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
        delete[] leftLabelArray;
        delete[] rightLabelArray;
    }
    
    void mergeSort(double* array, int* label, int const begin, int const end) const {
        if (begin >= end)
            return;
        int mid = begin + (end - begin) / 2;
        mergeSort(array, label, begin, mid);
        mergeSort(array, label, mid + 1, end);
        merge(array, label, begin, mid, end);
    }

    int findkNNLabel(double* distances, int* label, int const length, const int k) const{
        mergeSort(distances, label, 0, length - 1);
        int i;
        int count[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        for(i = 0; i < k; ++i){
            if(count[label[i]] == -1) count[label[i]] += 2;
            else ++count[label[i]];
        }
        int max = 0;
        for (i = 0; i < 10; ++i){
            if(count[i] > max) max = count[i];
        }
        
        for(i = 0; i < 10; ++i){
            if(count[i] == max) break;
        }
        return i;
    }

    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const
    {
        Dataset result;
        if (k < 1 || this->data->length() == 0 || X_train.data->length() == 0 || Y_train.data->length() == 0)  return result;
        int newK = k;
        if(k > X_train.data->length()) newK = X_train.data->length();
        result.nameCol->push_back(Y_train.nameCol->get(0));
        int lengthTrain = min(X_train.data->length(), Y_train.data->length());
        int *label = new int[lengthTrain];
        double *distances = new double[lengthTrain];
        for (int i = 0; i < this->data->length(); i++)
        {
            if (!this->data->get(i)) {
                continue;
            }

            for (int j = 0; j < lengthTrain; j++){
                label[j] = Y_train.data->get(j)->get(0);
            }
            for (int j = 0; j < lengthTrain; ++j){
                distances[j] = distanceEuclidean(this->data->get(i), X_train.data->get(j));
            }
            
            int predictedLabel = findkNNLabel(distances, label, lengthTrain, newK);
            List<int> *tmp = new Image<int>();
            tmp->push_back(predictedLabel);
            result.data->push_back(tmp);
        }
        delete[] distances;
        delete[] label;
        return result;
    }
    double score(const Dataset& y_test) const
    {   
        //TODO: implement Task 3 
        if(this->data->length() != y_test.data->length() || this->data->length() == 0) return -1;
        int count = 0;
        for(int i = 0; i < this->data->length(); ++i){
            if(this->data->get(i)->get(0) == y_test.data->get(i)->get(0)) count++;
        }
        return static_cast<double> (count) / this->data->length();
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
        return;

    double minDouble = 1.0e-15;
    int nRow = X.getData()->length();
    double rowSplit = nRow * (1 - test_size);

    if (abs(round(rowSplit) - rowSplit) < minDouble * nRow)
        rowSplit = round(rowSplit);

    X_train = X.extract(0, rowSplit - 1, 0, -1);
    Y_train = Y.extract(0, rowSplit - 1, 0, -1);

    X_test = X.extract(rowSplit, -1, 0, -1);
    Y_test = Y.extract(rowSplit, -1, 0, -1);
}
// Please add more or modify as needed