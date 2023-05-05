#include <gtest/gtest.h>
#include "Any.h"
#include <string>
#include <iostream>

TEST(AnyTest, case1) {
    Any n;
    auto r = n.IsNull();
    if(r) {
        std::cout << "n is Null" << std::endl;
    } else {
        std::cout << "n in NOT Null" << std::endl;
    }

}

TEST(AnyTest, case2) {
    std::string s1 = "hello";
    Any n = s1;
    n.AnyCast<int> ();
}

TEST(AnyTest, case3) {
    Any n1 = 1;
    if(n1.Is<int>()) {
        std::cout << "n1 is INT" << std::endl;
    } else {
        std::cout << "n1 is NOT INT" << std::endl;
    }
}

TEST(AnyTest, case4) {
    std::string str = "test";
    Any n1 = str;
    if(n1.Is<int>()) {
        std::cout << "n1 is INT" << std::endl;
    } else {
        std::cout << "n1 is NOT INT" << std::endl;
    }
    std::cout << n1.AnyCast<std::string>() << std::endl;
}