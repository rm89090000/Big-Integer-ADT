/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA6
* BigIntegerTest.cpp
* Testing the Big Integer ADT
***/ 




#include<string>
#include <cstddef>
#include "BigInteger.h"


int main(void){
    BigInteger A =  BigInteger("+12222222222");
    BigInteger B = BigInteger("-122239009090");
    BigInteger C = BigInteger("12356756756756");
    BigInteger J = BigInteger("-12222222222");


    BigInteger D = A*B;
    BigInteger E = C+B;
    BigInteger F = A-B;
    BigInteger G = A*=B;

    BigInteger H = C+=B;

    BigInteger I = C-=A;

    BigInteger K = A.compare(J);


    std::cout<<"Print out A*B: "<<D<<std::endl;
    std::cout<<"Print out C+B: "<<E<<std::endl;
    std::cout<<"Print out A-B: "<<F<<std::endl;
    std::cout<<"Print out A*=B: "<<G<<std::endl;
    std::cout<<"Print out C+=B: "<<H<<std::endl;
    std::cout<<"Print out C-=A  "<<I<<std::endl;
    std::cout<<"Comparing BigIntegers: +12222222222 and -12222222222: "<<K<<std::endl;

}

