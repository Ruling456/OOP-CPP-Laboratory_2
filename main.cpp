#include "include/Four.h"
#include <iostream>

int main() {
    try {
        Four a("1230");
        Four b("321");
        
        std::cout << "a = " << a.to_string() << std::endl;
        std::cout << "b = " << b.to_string() << std::endl;
        
        Four sum = a.add(b);
        std::cout << "a + b = " << sum.to_string() << std::endl;
        
        Four diff = a.subtract(b);
        std::cout << "a - b = " << diff.to_string() << std::endl;
        
        if (a.greater_than(b)) {
            std::cout << "a > b" << std::endl;
        } else if (a.less_than(b)) {
            std::cout << "a < b" << std::endl;
        } else {
            std::cout << "a == b" << std::endl;
        }
        
        Four c = a.copy();
        std::cout << "Copy of a = " << c.to_string() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}