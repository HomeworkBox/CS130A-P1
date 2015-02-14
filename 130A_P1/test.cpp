//
//  test.cpp
//  130A_P1
//
//  Created by Tyler Weimin Ouyang on 10/30/14.
//  Copyright (c) 2014 Tyler Weimin Ouyang. All rights reserved.
//

#include <iostream>
#include "heapHA.h"

int main(int argc, const char * argv[]) {

    heaphash::heaphash test = heaphash(50);
    test.insert(-1183);
    test.insert(-624);
    test.insert(-177);
    test.insert(-35);
    test.insert(-21);
    test.insert(1470);
    test.insert(910);
    test.insert(1547);
    test.insert(2676);
    test.insert(2797);
    test.insert(3059);
    test.insert(3318);
    test.insert(3573);
    test.insert(3733);
    test.insert(3777);
    test.insert(3878);
    test.insert(3926);
    test.insert(3968);
    test.insert(4033);
    test.insert(4049);
    test.insert(4218);
    test.insert(4404);
    test.insert(4604);
    test.insert(4775);
    test.insert(4879);
    test.insert(4884);
    test.insert(5842);
    test.insert(6095);
    test.insert(6203);
    test.insert(6531);
    std::cout << "Hello, World!\n";
    test.Delete(910);
    test.insert(-1951);
    test.Delete(1547);
    test.insert(3322);
    test.insert(1670);
    test.Delete(2797);
    test.insert(-471);
    test.Delete(4604);

    test.print();

    std::cout << "Hello, World!\n";
    return 0;
}

