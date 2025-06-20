/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA6
* BigInteger.cpp
* Functions for the Big Integer ADT
***/ 



#include<iostream>
#include<string>
#include <cstddef>
#include "BigInteger.h"

const int power = 9;
const int base = 1000000000;

BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}
BigInteger::BigInteger(long x){
    if(x==0){
        signum = 0;
        digits.insertBefore(0);
    }
    else{
        if(x<0){
            signum = -1;
        }
        else{
            signum = 1;
        }
        x = std::abs(x);
        while(x>0){
            digits.insertBefore(x%base);
            x = x/base;
        }
    }
}
BigInteger:: BigInteger(std::string s){
    if(s.empty()){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    for(unsigned int y =0; y<s.size(); y++){
        if(y==0 && (s[y]=='+'|| s[y]=='-')){
            continue;
        }
        if(!std::isdigit(s[y])){
             throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    int i =s.length();
    if(s=="0"){
        signum = 0;
        digits.insertBefore(0);
        return;
    }
    if(s[0] == '-'){
        signum = -1;
        s = s.erase(0, 1);
        i--;
    }
    else if(s[0]=='+'){
        signum = 1;
        s = s.erase(0, 1);
        i--;

    }
    else{
        signum = 1;
    }


    while(i>=0){
        int group = i-power;
        if(group<0){
            group = 0; 
        }
        std::string snew = s.substr(group, i-group);
        long val = std::stol(snew);
        digits.insertAfter(val);
        i = i-power;
    }


    while(digits.length()>1 && digits.front()==0){
        digits.eraseAfter();
    }
}
    BigInteger::BigInteger(const BigInteger& N){
        this->signum = N.signum;
        this->digits = N.digits;
    }
int BigInteger::sign() const{
    return this->signum;
}
int BigInteger::compare(const BigInteger&N) const{
    if(signum<N.signum){
        return -1;
    }
    if(N.signum<signum){
        return 1;
    }
    if(signum==0){
        return 0;
    }
    if(digits.length()<N.digits.length()){
        if(signum ==1){
            return -1;
        }
        else{
            return 1;
        }
    }
    if(digits.length()>N.digits.length()){
        if(signum ==1){
            return 1;
        }
        else{
            return -1;
        }
    }
    List first = digits;
    List second = N.digits; 
    first.moveFront();
    second.moveFront();
    while(first.position()<first.length() && second.position()<second.length()){
        if(first.peekNext()<second.peekNext()){
            if(signum == 1){
                return -1;
            }
            else{
                return 1;
            }
        }
        if(first.peekNext()>second.peekNext()){
            if(signum == 1){
                return 1;
            }
            else{
                return -1;
            }
        }
        first.moveNext();
        second.moveNext();
    }
    return 0;
}
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}
void BigInteger::negate(){
    if(signum ==0){
        signum = 0;
    }
    else if(signum == 1){
        signum = -1;
    }
    else if(signum ==-1){
        signum = 1;
    }
}
void shiftList(List&L, int p){
    L.moveBack();
    for(int i=0; i<p; i++)    {
        L.insertAfter(0);
    }
}
void scalarMultList(List&L, ListElement m){
    if(L.length()==0){
        L.clear();
        L.insertBefore(0);
        return;
    }
    
    L.moveFront();
    while(L.position()<L.length()){
        L.setAfter(L.peekNext()*m);
        L.moveNext();
    }
}
void negateList(List&L){
    if(L.length()==0){
        return;
    }
    L.moveFront();
    while(L.position()<L.length()){
        L.setAfter(-L.peekNext());
        L.moveNext();
    }
}


int normalizeList(List& L){
    if(L.length()==0){
        return 0;
    }

    int ret;

    if(L.front()>0){
        ret = 1;
    }

    if(L.front()<0){
        negateList(L);
        ret = -1;
    }

    L.moveBack();
    long c = 0;

    while(L.position()>0){
        long value = L.peekPrev()+c;

        if(value>=base){
            c = value/base;
            value = value%base;
        }

        else if(value<0){
            c = -1;
            value = value+base;
        }
        else{
            c = 0;
        }

        L.setBefore(value);
        L.movePrev();
    }

    if(c!=0){
        L.insertBefore(c);

    }
    L.moveFront();

    while(L.length()>1 && L.front()==0){
        L.eraseAfter();
    }

    if(L.front()<0){
        negateList(L);
        return normalizeList(L);
    }

    if(L.front()==0){
        ret = 0;
    }
    return ret;
}




void sumList(List&S, List A, List B, int sgn){
    S.clear();
    A.moveBack();
    B.moveBack();
    while(A.position()>0 || B.position()>0){
            long total = 0;
        if(A.position()>0){
            total += A.movePrev();
        }
        if(B.position()>0){
            total+=sgn*B.movePrev();
        }
       
       S.insertAfter(total);
}
}
    std::ostream& operator<<( std::ostream& stream, BigInteger N ){
            return stream<<N.to_string();
   }
std::string BigInteger::to_string(){
    if(signum==0){
        return "0";
    }
    std::string num;
    if(signum==-1){
        num.append("-");
    }
    List current = digits;
    current.moveFront();
    int count = 0;
    while(current.position()<current.length()){
        long value = current.peekNext();
        std::string val = std::to_string(value);
        if(count == 0){
            num.append(val);
        }
else if(count>0){
        while(val.size()<power){
            val.insert(0, "0");
        }
        num.append(val);
}
        count++;
        current.moveNext();
    }


    return num;
}
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)==0){
        return true;
    }
    else{
        return false;
    }
}
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)<0){
        return true;
    }
    else{
        return false;
    }
}
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)<=0){
        return true;
    }
    else{
        return false;
    }
}
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)>0){
        return true;
    }
    else{
        return false;
    }
}
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)>=0){
        return true;
    }
    else{
        return false;
    }
}


BigInteger BigInteger::add(const BigInteger&N) const{
    List first = this->digits;
    List second = N.digits;
    List result;
    BigInteger final;
    if(this->signum <0 &&  N.signum<0){
        sumList(result,second,first, 1);
        final.signum = normalizeList(result);
        final.signum = -1;
    }

    else if(this->signum>0 && N.signum<0){
        sumList(result, first, second, -1);
        final.signum = normalizeList(result);

    }
    else if(this->signum<0 && N.signum>0){
        sumList(result, second, first, -1);
        final.signum = normalizeList(result);
    }
    else{
        sumList(result, first, second, 1);
        final.signum = normalizeList(result);
        final.signum = 1;

    }
    final.digits = result;

    return final;

}
BigInteger BigInteger::mult(const BigInteger&N) const{
    if(this->signum==0 || N.signum==0){
        BigInteger num;
        num.makeZero();
        return num;
    }
    List create;
    List first = this->digits; 
    List second = N.digits; 
    second.moveBack();
    int move = 0;
    BigInteger multiply;
    while(second.position()>0){
        List current = this->digits;
        int a = second.peekPrev();
        scalarMultList(current, a);
        shiftList(current, move);
        sumList(create, create,current, 1);
        multiply.signum = normalizeList(create);
        move++;
        second.movePrev();
    }
    multiply.digits = create;
    multiply.signum = this->signum*N.signum;
    return multiply;
}
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}
BigInteger operator*=(BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}



BigInteger BigInteger::sub(const BigInteger& N) const {
  List first = this->digits;
    List second = N.digits;
    List result;
    BigInteger final;
    if(this->signum <0 &&  N.signum<0){
        sumList(result,second,first, -1);
        final.signum = normalizeList(result);
    }

    else if(this->signum>0 && N.signum<0){
        sumList(result, first, second, 1);
        final.signum = normalizeList(result);

    }
    else if(this->signum<0 && N.signum>0){
        negateList(first);
        negateList(second);
        sumList(result, second, first, 1);
  
        final.signum = normalizeList(result);
    }
    else{
        sumList(result, first, second, -1);
        final.signum = normalizeList(result);

    }

    final.digits = result;
    return final;
}










