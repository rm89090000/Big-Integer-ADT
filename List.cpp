/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA6
* List.cpp
* Functions for List ADT
***/ 


#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

List::Node::Node(ListElement  x){
    data = x;
    prev = nullptr;
    next = nullptr;
}


List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    num_elements = 0;
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = backDummy;

}
List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor =frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node* N = L.frontDummy->next;
    while(N!=L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }

}

List::~List(){
    moveFront();
    while(length()>0){
        eraseAfter();
    }
    delete frontDummy;
    delete backDummy;
}


void List::insertAfter(ListElement x){
    if(beforeCursor==nullptr || afterCursor==nullptr){
         throw std::length_error("List::insertAfter(): Error");
    }

    Node*N = new Node(x);
    
        N->prev = beforeCursor;
        beforeCursor->next = N;
        N->next = afterCursor;
        afterCursor->prev = N;
        afterCursor = N;
        num_elements++;
    }


    void List::insertBefore(ListElement x){

    if(beforeCursor==nullptr || afterCursor==nullptr || pos_cursor<0){
         throw std::length_error("List::insertAfter(): Error");
    }
    Node*N = new Node(x);
        N->prev = beforeCursor;
        beforeCursor->next =  N;
        N->next = afterCursor;
        afterCursor->prev = N;
        beforeCursor = N;

        num_elements++;
        pos_cursor++;
    }

    void List::cleanup(){
        if(length()<=0){
             throw std::length_error("List::cleanup(): Error");
        }
        int count = 0;
        Node*first  = frontDummy->next;
        while(first!=backDummy){
            count++;
            int s = count;
            Node*second = first->next;
            while(second!=backDummy){
                if(first->data == second->data){
                         second->next->prev = second->prev;
                         second->prev->next = second->next;

                         if(second == beforeCursor){
                            beforeCursor = beforeCursor->prev;
                         }

                         if(second==afterCursor){
                            afterCursor = afterCursor->next;
                         }
                         Node*del = second;
                         second = second->next;
                        delete del;
                         num_elements--;
                         if(s<pos_cursor){
                            pos_cursor--;
                         }
                }
                else{
                    second = second->next;
                    s++;
                
            }

        }
 first = first->next;

    }
    }
    

    ListElement List::front() const{
          if(num_elements==0 ){
      throw std::length_error("List::Front(): empty List");
    }
    return(frontDummy->next->data);
    }

    ListElement List::back() const{
          if(num_elements==0 ){
      throw std::length_error("List::Back(): empty List");
    }
    return(backDummy->prev->data);
    }



int List::length() const{
    return(num_elements);
}

int List::position() const{
    if(pos_cursor<0 || pos_cursor>num_elements ){
         throw std::range_error("List::position(): Error");
    }

    return(pos_cursor);


}

ListElement List::peekNext() const{

if(pos_cursor>=num_elements){
    throw std::range_error("List::peekNext(): Error");
}
    return afterCursor->data;
}

ListElement List::peekPrev() const{
    if(pos_cursor<=0){
        throw std::range_error("List::peekPrev(): Error");
    }
    return beforeCursor->data;
}

void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::clear(){
    moveBack();
    while(length()>0){
        eraseBefore();
    }
}

void List::eraseAfter(){
    if(position()>=length() || length()==0){
        throw std::range_error("List: eraseAfter(): empty List");
    }
     else{
            Node*curr = afterCursor;
            beforeCursor->next = beforeCursor->next->next;
            curr->next->prev = beforeCursor;
            afterCursor = curr->next;
            delete curr;
            num_elements--;
    }
}


void List::eraseBefore(){
    if(position()<=0 || num_elements==0 || beforeCursor==frontDummy){
        throw std::range_error("List: eraseBefore(): empty List");
    }
     else{
        Node*curr = beforeCursor;
            afterCursor->prev = afterCursor->prev->prev;
            curr->prev->next = afterCursor;
            beforeCursor = curr->prev;
            delete curr;
            num_elements--;
            pos_cursor--;
        }

}




void List::moveBack(){
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::movePrev(){

        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
        return afterCursor->data;
    
}

 ListElement List::moveNext(){


    beforeCursor =  beforeCursor->next;
    afterCursor = beforeCursor->next;
    pos_cursor++;
    return beforeCursor->data;
   

 }

  void List::setAfter(ListElement x){
    if(pos_cursor>=num_elements){
         throw std::range_error("List::setAfter(): Error");
    }
    else{
       afterCursor->data = x;
    }
  }

void List::setBefore(ListElement x){
        if(pos_cursor<=0){
        throw std::range_error("List::setBefore(): Error");
    }
    else{
        beforeCursor->data = x;
    }

}

   int List::findNext(ListElement x){

    while(position()<length()){
    moveNext();

    if(beforeCursor->data ==x){
        return pos_cursor;
    }

    }
    return -1;
   }


    int List::findPrev(ListElement x){

        while(position()>0){
            movePrev();
            if(afterCursor->data==x){
                return pos_cursor;
            }
        }
        return -1;
   }

List List::concat(const List& L) const{
    List J;
    Node * N = this->frontDummy->next;
    Node *M = L.frontDummy->next;
    while(N!=backDummy){
        J.insertAfter(N->data);
        N = N->next;
        J.moveNext();
    }
    while(M!=L.backDummy){
        J.insertAfter(M->data);
        M = M->next;
        J.moveNext();
    }
    J.moveFront();
    return J;
}

bool List::equals(const List& R) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr; 
   eq = (this->num_elements == R.num_elements );
   N = this->frontDummy;
   M = R.frontDummy;
   while(eq && N!=backDummy){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

std::string List::to_string() const{
    Node*N = nullptr;
    std::string s = "(";
    for(N = frontDummy->next; N!=backDummy; N=N->next){
        s+=std::to_string(N->data);
        if(N->next!=backDummy){
             s+=", ";
        }
    }
    s+=")";
    return s;
}

bool operator==(const List& A, const List& B){
   return A.equals(B);
}




std::ostream& operator<<(std::ostream& stream, const List& L ) {
    return stream<<L.to_string();

}

List& List::operator=( const List& L ){
    if(this!=&L){
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }

    return *this;
}


