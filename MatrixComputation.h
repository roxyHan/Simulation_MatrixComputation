//
// Created by hanifa on 2/12/20.
//

#ifndef LAB3_MATRIXCOMPUTATION_H
#define LAB3_MATRIXCOMPUTATION_H


class MatrixComputation {

public:
    MatrixComputation();
    void interaction();
    static int exit_condition(char* result, int x);
    int& getLocation(int x);
    static int getLinearIdx(int row, int column);
    static char& readFile(std::string filename, char arr[], int n);
    static int writeToFile(std::string filename, char arr[], int n);
    int threadCreation(int x); // thread creation
    static void * computation(void* args);
    static void * isDone(void* args);
    static void display(char* resultat);
};


#endif //LAB3_MATRIXCOMPUTATION_H
