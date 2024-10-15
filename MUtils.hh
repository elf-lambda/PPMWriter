//
// Created by elff on 10/15/2024.
//

#ifndef MUTILS_HH
#define MUTILS_HH

#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>


template <typename... T>
auto mprint(T... args) -> void {
    ((std::cout << args << " "), ...) << std::endl;
}

#endif //MUTILS_HH
