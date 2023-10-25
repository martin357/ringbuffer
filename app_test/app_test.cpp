#include <iostream>
#include <llist.hpp>


int main(int argc, char ** argv) {
    LList<int> list;
    for(int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    std::cout << "{ ";
    for(auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << "}" << std::endl;
}
