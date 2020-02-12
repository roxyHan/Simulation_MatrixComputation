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

    void threadCreation(int x); // thread creation
    static void * computation(void* args);
    void display(int matrix[][column], int x);
};


#endif //LAB3_MATRIXCOMPUTATION_H
