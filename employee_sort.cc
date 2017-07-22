/*
  Sort Employee Records of names and salaries.

  GfG: http://practice.geeksforgeeks.org/problems/sorting-employees/0
  My notes: https://docs.google.com/document/d/1CakL2u-1RucDExkfDlE1x1-71SjXCSAqKj3EpH4mOUo/

  Given records of employees in the form of names and salaries, sort the data by
  salary ascending, and if same salary, by name ascending.

  For the full program mode, here's an example input and output:

  Input:
    2
    3
    xbnnskd 100 geek 50 for 70
    2
    shyam 50 ram 50
  Output:
    geek 50 for 70 xbnnskd 100
    ram 50 shyam 50

  v0 (2017.07): My own MergeSort that failed on not-power-of-2 sizes.  Marked incorrect by GfG.
  v1 (2017.07): My own correct MergeSort. Marked correct by GfG. Full program mode.
      Compile & Run: g++-7 -Wall -Wextra -std=c++14 employee_sort.cc && ./a.out
*/

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

struct Employee {
    std::string name;
    int salary;
};

std::ostream& operator<< (std::ostream& os, const Employee& employee) {
    os << employee.name << " " << employee.salary;
    return os;
}

// compare first by salary, and then name
bool operator< (const Employee& e1, const Employee& e2) {
    return e1.salary < e2.salary || (e1.salary == e2.salary && e1.name < e2.name);
}

// !(e1 < e2) is supposed to be e1 >= e2
//     !(e1 < e2)
// is  !(e1.salary < e2.salary || (e1.salary == e2.salary && e1.name < e2.name))
// i.e.  e1.salary >= e2.salary && (e1.salary != e2.salary || e1.name >= e2.name)
// i.e. (e1.salary >= e2.salary && e1.salary != e2.salary) || (e1.salary >= e2.salary && e1.name >= e2.name)
// i.e.  e1.salary > e2.salary || (e1.salary >= e2.salary && e1.name >= e2.name)
// i.e.  e1.salary > e2.salary || (e1.salary == e2.salary && e1.name >= e2.name)

bool operator<= (const Employee& e1, const Employee& e2) {
    // e1 <= e2 is negation of e1 > e2 i.e. e2 < e1
    return !(e2 < e1);
}

typedef std::vector<Employee>::size_type size_type;

void Sort(std::vector<Employee>& array);
void MergeSort(std::vector<Employee>& array);
void Merge(std::vector<Employee>& input, size_type left, size_type middle, size_type right, std::vector<Employee>& output);

void Sort(std::vector<Employee>& array) {
    MergeSort(array);
}

void MergeSort(std::vector<Employee>& array) {
    auto size = array.size();
    std::vector<Employee> temp(size);
    for (size_type s = 1; s < size; s *= 2) {
        for (size_type i = 0; i < size; i += 2 * s) {
            Merge(array, i, std::min(i + s, size), std::min(i + 2 * s, size), temp);
        }
        s *= 2;
        if (s >= size) {
            copy(temp.begin(), temp.end(), array.begin());
            break;
        }
        for (size_type i = 0; i < size; i += 2 * s) {
            Merge(temp, i, std::min(i + s, size), std::min(i + 2 * s, size), array);
        }
    }
}

void Merge(std::vector<Employee>& input, size_type left, size_type middle, size_type right, std::vector<Employee>& output) {
    auto i = left;
    auto j = middle;
    auto k = left;
    while (1) {
        auto i_in_range = i < middle;
        auto j_in_range = j < right;
        if (!i_in_range && !j_in_range) break;
        if (i_in_range && (!j_in_range || input[i] <= input[j])) {
            output[k++] = input[i++];
        } else { // j_in_range && (!i_in_range || input[j] < input[i])
            output[k++] = input[j++];
        }
        // Deciphering the else predicate:
        //     !(i_in_range && (!j_in_range || input[i] <= input[j]))
        // i.e. !i_in_range || (j_in_range && input[i] > input[j])
        // i.e. (!i_in_range || j_in_range) && (!i_in_range && input[i] > input[j])
        //
        // combine that with
        //   !(!i_in_range && !j_in_range)
        // i.e. i_in_range || j_in_range
        //
        //     (i_in_range || j_in_range) && (!i_in_range || j_in_range)
        // i.e. j_in_range
    }
}

int main() {
    int testcases;
    std::cin >> testcases;
    while (testcases--) {
        std::vector<Employee> employees;
        int size;
        std::cin >> size;
        for (int i = 0; i < size; i++) {
            std::string name;
            int salary;
            std::cin >> name >> salary;
            employees.push_back({ name, salary });
        }
        Sort(employees);
        copy(employees.begin(), employees.end(),
            std::ostream_iterator<Employee>(std::cout, " "));
        std::cout << std::endl;
    }
}
