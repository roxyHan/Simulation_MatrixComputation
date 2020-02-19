//
// Created by hanifa on 2/12/20.
//

using namespace std;

#include <iostream>
#include <fstream>
#include "MatrixComputation.h"


MatrixComputation::MatrixComputation() {}


char& MatrixComputation::readFile(std::string filename, char *arr, int n) {
    //read from file
    std::ifstream isObj(filename, std::ios::in| std::ios::binary);
    isObj.read(arr, n);
    if (!isObj) {
        std::cout << "Failed to open file" <<std::endl;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " is the element at position " << i << std::endl;
    }
    isObj.close();
    return *arr;
}


int MatrixComputation::writeToFile(string filename, char* num, int n) {
    // Write to file
    std::ofstream osObj(filename, std::ios::out| std::ios::binary);
    osObj.write(num, n);
    osObj.close();
}


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
    int matrix[n][n];

    string filename;
    // Ask the user for the name of the file
    cout << "Please enter the name of the file: " << endl;
    getline(cin, filename);
    int totalLength = n*n;
    char* nums = new char [totalLength];
    // Populate the file with random values
    for (int i = 0; i < (n*n); ++i) {
        nums[i] = '0' + (rand() % 2);
    }
    writeToFile(filename, nums, totalLength);
    char* result;
    readFile(filename, result, totalLength);

    // Create M threads
    threadCreation(M);

    // Display the matrix, n);


}


void* MatrixComputation::computation(void *args) {
    cout << "###It's working for " << endl;
    // generate random row number
    // generate random column number
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

int MatrixComputation::exit_condition(int x) {
    // Check that all elements are either 0 or 1


}

void MatrixComputation::print() {
    //readFile();
}