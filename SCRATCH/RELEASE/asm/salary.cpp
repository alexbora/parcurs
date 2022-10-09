/**
 * @author      : alex (alex@mac.local)
 * @file        : salary
 * @created     : Sâmbătă Oct 01, 2022 09:18:21 EEST
 */

#include <iostream>
using namespace std;

class Employee
{
private:
  // Private attribute
  int      salary;
  unsigned age;
  unsigned height;

public:
  // Setter
  void setSalary(int s)
  {
    salary = s;
  }
  // Getter
  int getSalary()
  {
    return salary;
  }
  void set_age(unsigned x)
  {
    age = x;
  }
  unsigned get_age()
  {
    return age;
  }
  void set_height(unsigned h)
  {
    height = h;
  }
  unsigned get_height()
  {
    return height;
  }
};

int main()
{
  Employee myObj;
  myObj.setSalary(50000);
  cout << myObj.getSalary();
  myObj.set_age(11);
  cout << "\n";
  cout << myObj.get_age();
  cout << "\n";
  myObj.set_height(175);
  cout << "\n";
  cout << myObj.get_height();
  cout << "\n";
  return 0;
}
