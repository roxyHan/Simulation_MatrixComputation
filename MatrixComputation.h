//
// Created by hanifa on 2/12/20.
//

#ifndef LAB3_MATRIXCOMPUTATION_H
#define LAB3_MATRIXCOMPUTATION_H


const int column = 2;

class MatrixComputation {

public:
    MatrixComputation();
    void interaction();
    int exit_condition(int x);
    void print();
    char& readFile(std::string filename, char arr[], int n);
    int writeToFile(std::string filename, char arr[], int n);
    void threadCreation(int x); // thread creation
    static void * computation(void* args);
    void display(int matrix[][column], int x);
};


#endif //LAB3_MATRIXCOMPUTATION_H
