//
//  main.cpp
//  130A_P1
//
//  Created by Tyler Weimin Ouyang on 10/29/14.
//  Copyright (c) 2014 Tyler Weimin Ouyang. All rights reserved.
//

#include <iostream>
#include "heapHA.h"

int main(int argc, const char * argv[]) {

    int maxNum;
    scanf("%d",&maxNum);
    if (maxNum<1) {
        return 0;
    }
    heaphash* test = new heaphash(maxNum);
    int comdNum;
    scanf("%d",&comdNum);
    for (int i=0; i<comdNum; i++) {
        int type;
        int parameter;
        scanf("%d",&type);
        switch (type) {
            case 0:
                scanf("%d",&parameter);
                test->insert(parameter);
                break;
                
            case 1:
                scanf("%d",&parameter);
                test->lookup(parameter);
                break;
                
            case 2:
                test->deleteMin();
                break;
                
            case 3:
                scanf("%d",&parameter);
                test->Delete(parameter);
                break;
                
            case 4:
                test->print();
                break;
        }
    }
    
    return 0;
}

