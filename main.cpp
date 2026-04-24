#include <iostream>

// The OJ will include and test the CrossArray class from the header named "code".
// To align with the repository rules, we include it here so the build outputs an executable named `code`.

#include "src.hpp"

int main() {
    // Minimal self-check (no external libraries): construct and basic operations
    sjtu::CrossArray ca(2);
    int a[3] = {1,2,3};
    ca.InsertArrays(a, 3);
    int b[2] = {4,5};
    ca.InsertArrays(b, 2);
    // basic access
    std::cout << ca.At(0,0) << " " << ca.At(1,1) << "\n";
    return 0;
}
