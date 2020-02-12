//
// Created by hanifa on 2/12/20.
//

using namespace std;

#include <iostream>
#include "MatrixComputation.h"


MatrixComputation::MatrixComputation() {}


void MatrixComputation::interaction() {
    string elementsCount, threadsCount;
    // Ask the user to enter the number of elements n and the number of threads M
    cout << "Please enter the number of elements for the matrix: " << endl;
    getline(cin, elementsCount);
    cout << "Now, please enter the number of threads for this computation: " << endl;
    getline(cin, threadsCount);
    int n = stoi(elementsCount);
    int M = stoi(threadsCount);
    // Create square matrix
    int matrix[M][M];

    // Populate matrix with random values
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    // Create M threads
    threadCreation(M);

    // Display the matrix, n);


}


void* MatrixComputation::computation(void *args) {
    cout << "###It's working for " << endl;

    return (0) ;
}



void MatrixComputation::threadCreation(int x) {
    pthread_t threads[x];

    // Create the threads
    for (int i = 0; i < x; ++i) {
        int * p;
        pthread_create(&threads[i], 0, computation, (void*)p);
    }

    //  Allow the threads to be done
    for (int j = 0; j < x; ++j) {
        pthread_join(threads[j], 0);
    }
}

void MatrixComputation::display(int matrix[][column],int x){
// Display matrix
    for (int a = 0; a < x; ++a) {
        for (int b = 0; b < x; ++b) {
            cout << matrix[a][b] << " ,";
        }
        cout << endl;
    }
}
