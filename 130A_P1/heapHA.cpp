//
//  heapHA.cpp
//  130A_P1
//
//  Created by Tyler Weimin Ouyang on 10/29/14.
//  Copyright (c) 2014 Tyler Weimin Ouyang. All rights reserved.
//

#include "heapHA.h"
//#include <algorithm>

heaphash::heaphash(int size){
    currentSize = 0;
    if ((int(size*1.4))%2 == 0)
        hashTableSize=int(size*1.4)+1;
    else
        hashTableSize=int(size*1.4);//make a table with a maximum LF 0.71
    maxSize = size;
    _hash = new struct hash[hashTableSize];
    _heap = new int[size+1];
    cleanTable();// initialize
}

heaphash::~heaphash(){
    delete _hash;
    delete _heap;
}

void heaphash::insert(const int num){
    // hash insert
    if (lookupHash(num)!=-1){
        // when num is found in hash table
        printf("%d already present\n",num);
        return;
    }
    int pos = hash_fn(num);
    // get num's pos in hash table
    if (_hash[pos].status==0 || _hash[pos].status==-1){
        // if pos is available, set the value and status
        _hash[pos].status=1;
        _hash[pos].value = num;
    }
    else{
        bool success = false;
        int i = pos+1;
        do {
            if (_hash[i].status==0 || _hash[i].status==-1){
                _hash[i].status=1;
                _hash[i].value=num;
                success = true;
                break;
            }
            i = (i+1)%hashTableSize;
        }while ( i != pos);
        /*
        while ( i < hashTableSize) {
            // find a spot after pos if pos is taken
            if (_hash[i].status==0 || _hash[i].status==-1){
                _hash[i].status=1;
                _hash[i].value=num;
                success = true;
                break;
            }
            i++;
        }
        if (!success) {
            // find a spot before pos from the beginning
            i=0;
            while ( i < pos) {
//                printf("sta is %d val is %d pos is %d\n",hash[pos].status,hash[pos].value, i);
                if (_hash[i].status==0 || _hash[i].status==-1){
                    _hash[i].status=1;
                    _hash[i].value=num;
                    success = true;
                    break;
                }
                i++;
            }
        }*/
        if (!success) {
            // unexpected accident, should never show
            printf("no space\n");
            return;
        }
    }
    printf("%d inserted\n",num);
    // heap insert
    // insert check
    int hole = ++currentSize; // insert at the end of heap
    for (; num<_heap[hole/2] && hole > 1; hole /= 2) {
        _heap[hole]=_heap[hole/2];
        //percolateUp
    }
    _heap[hole]=num;
    //currentSize++; // update size
}

void heaphash::lookup(int num){
    // hash lookup
    // hash it then check the hash table
    int pos = hash_fn(num);
    if (_hash[pos].status==0){
        // unused slot
        printf("%d not found\n",num);
        return;
    }
    else{
        int i = pos;
        do {
            if (_hash[i].value==num && _hash[i].status!=-1){
                printf("%d found\n",num);
                return;
            }
            if (_hash[i].status==0){
                printf("%d not found\n",num);
                return;
            }
            i = (i+1)%hashTableSize;
        }while ( i != pos);
        /*{
            // check following slots
            // not deleted and match
            if (_hash[i].value==num && _hash[i].status!=-1){
                printf("%d found\n",num);
                return;
            }
            if (_hash[i].status==0){
                printf("%d not found\n",num);
                return;
            }
            i++;
        }
        i=0;
        while ( i < pos) {
            // start from the beginning
            if (_hash[i].status==0){
                printf("%d not found\n",num);
                return;
            }
            if (_hash[i].value==num  && _hash[i].status!=-1){
                printf("%d found\n",num);
                return;
            }
            i++;
        }
         */
    }
         
    printf("%d not found\n",num);
}

void heaphash::deleteMin(){
    // deleteMin of heap
    int min=_heap[1];
    _heap[1]=_heap[currentSize];// move the last to the top
    currentSize--; // update size
    percolateDown(1); // relocate it
    
    
    // hash it and delete it in hash table
    int pos=lookupHash(min);
    _hash[pos].status=-1;
    printf("Minimum key %d deleted\n", min);
}

void heaphash::Delete(int num){
    // lookup in hash then delete
    int pos=lookupHash(num);
    if (pos==-1) {
        printf("%d not found\n",num);
        return;
    }
    _hash[pos].status=-1;
    printf("%d deleted\n",num);
    
    // lookup in heap then delete
    // when this piece is executed, the num mut be in the data structure
    pos=lookupHeap(num);
    if (pos == 1) {
        _heap[1]=_heap[currentSize];// move the last to the top
        currentSize--; // update size
        percolateDown(1); // relocate it
        return;
    }
    _heap[pos]=_heap[currentSize];
    currentSize--;
    
    if (!(_heap[pos]<_heap[pos/2])) {
        percolateDown(pos);
    }
    else {
        int tmp = _heap[pos];
        for (; tmp < _heap[pos/2] && pos > 1; pos /= 2) {
            _heap[pos]=_heap[pos/2];
            //percolateUp
        }
        _heap[pos]=tmp;
    }
}

void heaphash::print(){
    // sort heap then print
    int times = currentSize;
    int *temp = new int[maxSize+1]; // new array
    
    for (int i=1; i<= times; i++) {
        temp[i]=_heap[1];
        printf("%d ", _heap[1]);
        deleteMinHeap();
        // elements in new array temp are sorted
    }
    printf("\n");
    delete _heap;
    _heap = temp;// swtich pointer
    currentSize=times; // update size
/* the above sorting method is utilizing the property of min-heap, but it is not space efficient the follwoing is using the std sort
 
    std::sort (_heap+1, heap+currentSize+1);
    for (int i=1; i <= currentSize; i++) {
        printf("%d ", _heap[i]);
    }
    printf("\n");
 */
}



// helper fucntions

int heaphash::lookupHeap(int num){
    // heap lookup
    // return -1 if num is not found
    // else return the position of num in hash table
    // O(n) complecity, simple iteration
    for (int i=1; i<=currentSize; i++) {
        if (_heap[i]==num) {
            return i;
        }
    }
    return -1;
}

int heaphash::lookupHash(int num){
    // hash lookup
    // hash it then check the hash table
    // return -1 if num is not found
    // else return the position of num in hash table
    int pos = hash_fn(num);
    if (_hash[pos].status==0){
        // unused slot
        return -1;
    }
    else{
        int i = pos;
        while ( i < hashTableSize) {
            // scan slots after pos
            if (_hash[i].status==0)
                return -1;
            if (_hash[i].value==num && _hash[i].status!=-1)
                // value should both match and valid
                return i;
            i++;
        }
        i=0;
        while ( i < pos) {
            // scan slots before pos
            if (_hash[i].status==0)
                return -1;
            if (_hash[i].value==num && _hash[i].status!=-1)
                return i;
            i++;
        }
    }
    return -1;
}

void heaphash::deleteMinHeap(){
    // deleteMin of heap
    _heap[1]=_heap[currentSize];
    currentSize--;
    percolateDown(1);
}

int heaphash::hash_fn(int key){
    if (key>=0) {
        return key % hashTableSize;
    }
    else {
        return ((key % hashTableSize)+hashTableSize)%hashTableSize;
    }
    
}

void heaphash::percolateDown(int index){
    int child;
    int tmp = _heap[index];
 //   int times = currentSize;
//    printf("--\n");
//    for (int i=1; i<= times; i++) {
//        printf("%d:%d ", i, _heap[i]);
//    }
//    printf("\n");
    for (; index*2 <= currentSize; index = child) {
        child = index*2;
        if ( child != currentSize && _heap[child]>_heap[child+1])
            child++;
        if (_heap[child]<tmp)
            _heap[index]=_heap[child];
        else
            break;
//        for (int i=1; i<= times; i++) {
//            printf("%d:%d ",i, _heap[i]);
//        }
//        printf("\n");
    }
    
    _heap[index]=tmp;
}

void heaphash::cleanTable(){
    for ( int i=0; i < hashTableSize; i++){
        _hash[i].status=0;
        _hash[i].value=0;
    }
}

/*
void heaphash::sort(){
    // sort heap
    int times = currentSize;
    int *temp = new int[maxSize+1];
    for (int i=1; i<= times; i++) {
        temp[i]=heap[1];
        deleteMin();
    }
    delete heap;
    heap = temp;
    currentSize=times;
}

void heaphash::buildHeap(){
    // may be used for sortung a heap
    for( int i = currentSize / 2; i > 0; --i )
        percolateDown( i );
}

 void heaphash::cleanTable(){
    for ( int i=0; i < hashTableSize; i++){
        hash[i].status=0;
        hash[i].value=0;
    }
}
 */

