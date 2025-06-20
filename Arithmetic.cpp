/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA6
* Arithmetic.cpp
* Arithmetic for the Big Integer ADT
***/ 





#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"

using namespace std;


int main(int argc, char*argv[]){
    ifstream in;
   ofstream out;
       if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }



   in.open(argv[1]);
      if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }


out.open(argv[2]);
  if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   string one;
   string two;
   string three;

   getline(in, one);
   getline(in, two);
   getline(in, three);


    BigInteger first = BigInteger(one);
   BigInteger third = BigInteger(three);

    BigInteger plus = first+third;

     BigInteger minus = first-third;

     BigInteger equals = first-first;

     BigInteger four = 3*first-2*third;

     BigInteger five = first*third;

     BigInteger six = first*first;

     BigInteger seven = third*third;

     BigInteger eight = (9*first*first*first*first) + (16*third*third*third*third*third);


   out<<first<<"\n\n";
   out<<third<<"\n\n";
      out<<plus<<"\n\n";
     out<<minus<<"\n\n";
    out<<equals<<"\n\n";
        out<<four<<"\n\n";

        out<<five<<"\n\n";

        out<<six<<"\n\n";
         out<<seven<<"\n\n";

        out<<eight<<"\n\n";

           in.close();
   out.close();

   return(EXIT_SUCCESS);


}
