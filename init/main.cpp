#include "kNN.hpp"

void tc1158()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(0, -2, 0, -1);
    Dataset dataset_extract2 = Dataset(dataset_extract);
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1160()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(30, 20, 0, -1);
    Dataset dataset_extract2 = dataset_extract;
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc_knn_score(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

int main() {
    //tc1158();
    //tc1160();
    tc_knn_score(10, 10);
    return 0;
}