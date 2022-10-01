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
};

int main()
{
  Employee myObj;
  myObj.setSalary(50000);
  cout << myObj.getSalary();
  myObj.set_age(11);
  cout << "\n";
  cout << myObj.get_age();
  return 0;
}
