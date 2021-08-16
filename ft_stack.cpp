#include <iostream>
#include "stack.hpp"
#include <stack>


int main ()
{
  std::stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  std::cout << "top: " << myints.top() << '\n';

	ft::stack<int> myints2;
  std::cout << "0. size: " << myints2.size() << '\n';

  for (int i=0; i<5; i++) myints2.push(i);
  std::cout << "top: " << myints2.top() << '\n';



//   myints.pop();
//   std::cout << "2. size: " << myints.size() << '\n';

  return 0;
}
