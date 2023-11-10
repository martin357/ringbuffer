/*
Copyright 2023, Martin Kopecky (martin.kopecky357@gmail.com)

This file is part of Containers.

Containers is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

Containers is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
Containers. If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#define USE_ITERATORS
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
