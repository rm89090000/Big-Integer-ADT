/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA6
* ListTest.cpp
* Testing the List ADT
***/ 
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
using namespace std;
int main(void){
    List L;
    L.moveBack();
    L.insertAfter(12223);
    L.insertBefore(56690);
    L.moveNext();
    L.setBefore(6);
    L.movePrev();
    L.setAfter(180);
    L.moveNext();
    L.insertBefore(670);
    L.insertBefore(1000000);
    L.insertAfter(8900000);
    L.insertBefore(340);
    L.insertBefore(340);
    L.insertBefore(340);
    L.insertBefore(340);
    L.insertBefore(340);
    L.insertBefore(340);
    L.insertBefore(980);
    L.eraseBefore();

    
    cout<<"Previous values are " << L.findPrev(12223)<<endl;
    cout<<"Next value is " << L.findNext(56690)<<endl;
    cout<<"The position for L is "<< L.position()<< " "<<endl;
    cout<<"Peek next for L is "<< L.peekNext()<< " "<<endl;
    cout<<"Peek prev for L is "<< L.peekPrev()<< " "<<endl;
    cout<< L <<endl;
    L.cleanup();
    cout<<"Removing Duplciates: "<< L <<endl;
    L.clear();
}

