//
//  heapHA.h
//  130A_P1
//
//  Created by Tyler Weimin Ouyang on 10/29/14.
//  Copyright (c) 2014 Tyler Weimin Ouyang. All rights reserved.
//

#ifndef ___30A_P1__heapHA__
#define ___30A_P1__heapHA__

#include <stdio.h>

struct hash {
    int status;// 1 for used, 0 for empty, -1 for deleted
    int value;
};

class heaphash{
private:
    unsigned int currentSize; // size of elements, mainly used for heap
    unsigned int maxSize; // input from the first line
    unsigned int hashTableSize;
    hash* _hash; // array of hash
    int* _heap; // array of heap
    
// helper functions, some are not used
    void percolateDown(int ); // locate a numer from any non-leaf position
    int hash_fn(int ); // hash function
    int lookupHeap(int );//lookup for heap, not print
    int lookupHash(int); // lookup for hash table, no print
    void deleteMinHeap(); // delete min of heap, no print
    void cleanTable();// unused,set hash table to initail status
    
    //void sort(); // unused, side product of print
    //void buildHeap(); //unused
    
public:
    heaphash(int );
    ~heaphash();
    void insert(int );
    void lookup(int );
    void deleteMin();
    void Delete(int );
    void print();
};

#endif /* defined(___30A_P1__heapHA__) */
