#include <iostream>
#include <fstream>
#include "MatrixComputation.h"

int main() {
    srand(time(0));
    MatrixComputation* matrix = new MatrixComputation();
    matrix->interaction();
    return 0;
}
