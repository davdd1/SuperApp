#include <iostream>

int main() {
    std::cout << "Hello, world!" << std::endl;
    int b = 69;    
    int* a = &b;
    std::cout << "Number:" << *a << std::endl;
    return 0;
}
