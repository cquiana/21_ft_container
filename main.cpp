#include <iostream>
#include <list>
#include <vector>
#include <limits>
// constructing lists


int main ()
{
  std::vector<int> myvector;

//   // set some content in the vector:
//   for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size()  << "\n";
   std::cout << sizeof(myvector) << std::endl;
  std::cout << ULONG_MAX << std::endl;
  std::cout << ULONG_MAX / sizeof(myvector) << std::endl;

  return 0;
}

// // new_op_new.cpp
// // compile with: /EHsc
// #include<new>
// #include<iostream>

// using namespace std;

// class MyClass
// {
// public:
//    MyClass( )
//    {
//       cout << "Construction MyClass." << this << endl;
//    };

//    ~MyClass( )
//    {
//       imember = 0; cout << "Destructing MyClass." << this << endl;
//    };
//    int imember;
// };



// int main( )
// {
//    // The first form of new delete
//    MyClass* fPtr = new MyClass;
//    delete fPtr;

//    // The second form of new delete
//    MyClass* fPtr2 = new( nothrow ) MyClass;
//    delete fPtr2;

//    // The third form of new delete
//    char x[sizeof( MyClass )];
//    MyClass* fPtr3 = new( &x[0] ) MyClass;
//    fPtr3 -> ~MyClass();
//    cout << "The address of x[0] is : " << ( void* )&x[0] << endl;
// }
