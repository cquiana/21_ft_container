// #include <iostream>
// #include <list>
// #include <vector>
// // constructing lists


// int main ()
// {
//   // constructors used in the same order as described above:
//   std::list<int> first;                                // empty list of ints
//   std::list<int> second (4,100);                       // four ints with value 100
//   std::list<int> third (second.begin(),second.end());  // iterating through second
//   std::list<int> fourth (third);                       // a copy of third

//   // the iterator constructor can also be used to construct from arrays:
//   int myints[] = {16,2,77,29};
//   std::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//   std::cout << "The contents of fifth are: ";
//   for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
//     std::cout << *it << ' ';

//   std::cout << '\n';

//   return 0;
// }

// new_op_new.cpp
// compile with: /EHsc
#include<new>
#include<iostream>

using namespace std;

class MyClass
{
public:
   MyClass( )
   {
      cout << "Construction MyClass." << this << endl;
   };

   ~MyClass( )
   {
      imember = 0; cout << "Destructing MyClass." << this << endl;
   };
   int imember;
};



int main( )
{
   // The first form of new delete
   MyClass* fPtr = new MyClass;
   delete fPtr;

   // The second form of new delete
   MyClass* fPtr2 = new( nothrow ) MyClass;
   delete fPtr2;

   // The third form of new delete
   char x[sizeof( MyClass )];
   MyClass* fPtr3 = new( &x[0] ) MyClass;
   fPtr3 -> ~MyClass();
   cout << "The address of x[0] is : " << ( void* )&x[0] << endl;
}
