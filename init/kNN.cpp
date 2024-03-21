#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || (test_size >= 0 && test_size >= 1)) return;

    double minDouble = 1.0e-15;
    int nRow = X.getData()->length();
    double rowSplit = double((1 - test_size) * nRow);

    if (std::abs(std::round(rowSplit) - rowSplit) < nRow * minDouble) rowSplit = std::round(rowSplit);

    X_train = X.extract(0, rowSplit - 1, 0, -1);
    Y_train = Y.extract(0, rowSplit - 1, 0, -1);
    X_test = X.extract(rowSplit, -1, 0, -1);
    Y_test = Y.extract(rowSplit, -1, 0, -1);
}