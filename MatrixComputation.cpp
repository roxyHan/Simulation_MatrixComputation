//
// Created by hanifa on 2/12/20.
//

using namespace std;

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "MatrixComputation.h"

pthread_mutex_t lock;
int n;
string filename;
int totalLength;

MatrixComputation::MatrixComputation() {}


char& MatrixComputation::readFile(std::string filename, char *arr, int n) {
    //read from file
    std::ifstream isObj(filename, std::ios::in| std::ios::binary);
    isObj.read(arr, n);
    if (!isObj) {
        std::cout << "Failed to open file" <<std::endl;
    }
    /**for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " is the element at position " << i << std::endl;
    }*/
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
    n = stoi(elementsCount);
    int M = stoi(threadsCount);
    // Ask the user for the name of the file
    cout << "Please enter the name of the file: " << endl;
    getline(cin, filename);
    totalLength = n*n;
    char* nums = new char [totalLength];
    // Populate the file with random values
    for (int i = 0; i < (n*n); ++i) {
        nums[i] = '0' + (rand() % 2);
    }
    writeToFile(filename, nums, totalLength);
    char* result = new char[totalLength];
    result = &(readFile(filename, result, totalLength));
    cout << "Starting matrix " << n << "*" << n << " : " << endl;
    display(result);
    // Create M threads
    threadCreation(M);

    // Display the final matrix
    /**cout << "Final matrix " << n << "*" << n << " : " << endl;
    display(result);
*/

}

void* MatrixComputation::computation(void *args) {
    pthread_mutex_lock(&lock);
    // generate random row number
    int rand_row = rand() % n;
    // generate random column number
    int rand_column = rand() % n;
    // Read file
    char* result = new char[totalLength];
    result = &readFile(filename, result, (n*n));

    // Check if half of the neighbor are 0 or 1
//*****************************************************************************
    int count = 0;
    int neighbors = 0;
    int linearIdx = 0;
    if (rand_row-1 >= 0) { // check row above
        if (rand_column-1 >= 0) { // check upper left column
            neighbors++;
            linearIdx = getLinearIdx(rand_row-1, rand_column-1);
            if(result[linearIdx] == '0') {
                count++;
            }
        }
        if (rand_column+1 < n) {  // check upper right column
            neighbors++;
            linearIdx = getLinearIdx(rand_row-1, rand_column+1);
            if(result[linearIdx] == '0') {
                count++;
            }
        }
        // check column above the given element
        neighbors++;
        linearIdx = getLinearIdx(rand_row-1, rand_column);
        if(result[linearIdx] == '0') {
            count++;
        }
    }
    if (rand_row+1 < n) { // check row below
        if (rand_column - 1 >= 0) { // check lower left column
            neighbors++;
            linearIdx = getLinearIdx(rand_row + 1, rand_column - 1);
            if (result[linearIdx] == '0') {
                count++;
            }
        }
        if (rand_column + 1 < n) {  // check lower right column
            neighbors++;
            linearIdx = getLinearIdx(rand_row + 1, rand_column + 1);
            if (result[linearIdx] == '0') {
                count++;
            }
        }
        // check column below the given element
        neighbors++;
        linearIdx = getLinearIdx(rand_row + 1, rand_column);
        if (result[linearIdx] == '0') {
            count++;
        }
    }
    if (rand_column-1 >= 0) {
        // check column to the left of the given element
        neighbors++;
        linearIdx = getLinearIdx(rand_row, rand_column - 1);
        if (result[linearIdx] == '0') {
            count++;
        }
    }
    if (rand_column+1 < n) {
        // check column to the right of the given element
        neighbors++;
        linearIdx = getLinearIdx(rand_row, rand_column+1);
        if(result[linearIdx] == '0') {
            count++;
        }
    }

//**************************************************************************
    int idx = getLinearIdx(rand_row, rand_column);
    char t = result[idx];
    int temp = t - '0';
    if (count >= ceil(neighbors/2.0)) {
        result[idx] = '0';
    }
    else{
        result[idx] = '1';
    }
    // Info regarding the thread
    cout << "---------------------------------------------" << endl;
    cout << "   Thread " << ((unsigned int)pthread_self()) <<  " at row " <<
    rand_row << ", column " << rand_column << endl;
    cout << "---------------------------------------------\n" << endl;

    display(result);
    cout << "Modified element from " << temp << " to " << (result[idx] - '0') << "\n"
         << endl;
    writeToFile(filename, result, totalLength);
    pthread_mutex_unlock(&lock);
    return (0) ;
}

void* MatrixComputation::isDone(void *args) {
    pthread_mutex_lock(&lock);
    char* result = new char[totalLength];
    result = &readFile(filename, result, totalLength);
    if (exit_condition(result, 1) || exit_condition(result, 0)){
        exit(10);
    }
    pthread_mutex_destroy(&lock);
}




int MatrixComputation::threadCreation(int x) {
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    pthread_t threads[x];
    // Create the threads
    for (int i = 0; i < x; ++i) {
        int * p;
        pthread_create(&threads[i], 0, computation, (void*)p);
    }

    /*// Create manager thread to check if the exit condition is met
    int*c;
    pthread_t threadManager;
    pthread_create(&threadManager, 0, isDone, (void*)c);
*/
    //  Allow the threads to be done
    for (int j = 0; j < x; ++j) {
        pthread_join(threads[j], 0);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

void MatrixComputation::display(char* arr){
    // Display matrix
    cout << endl;
    for (int i = 0; i < totalLength; ++i) {
        if ((i+1) % n == 0) {
            cout << arr[i] << endl;
        }
        else {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

int MatrixComputation::exit_condition(char* result, int x) {
    // Check that all elements are either 0 or 1
    for (int i = 0; i < totalLength; ++i) {
        if (result[i] != (x+'0')) {
            return false;
        }
    }
    return true;
}

int& MatrixComputation::getLocation(int x) {
    int* toRowColumn = new int[2];
    int row = x / n;
    int column = x - (row*n);
    toRowColumn[0] = row;
    toRowColumn[1] = column;
    return *toRowColumn;
}


int MatrixComputation::getLinearIdx(int row, int column) {
    int x = (row * n) + column;
    return x;
}
