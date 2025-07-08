#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // read data from input file
  std::ifstream inputFile{"input.txt"};

  if (!inputFile) {
    std::cerr << "Can't open input file.\n";
    return 1;
  }

  std::string inputStr{};

  std::vector<int> list1;
  std::vector<int> list2;

  int count{1};

  // extract data
  while (inputFile >> inputStr) {
    // convert input data to integer
    int inputNum{std::stoi(inputStr)};

    // extract data in each column to its own list
    if (count % 2 != 0) {
      list1.push_back(inputNum);
    } else {
      list2.push_back(inputNum);
    }

    count++;
  }

  // sort both lists in ascending order
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  // calculate distance
  int sum{0};

  for (long unsigned int i = 0; i < std::size(list1); i++) {
    sum = sum + abs(list1[i] - list2[i]);
  }

  std::cout << sum << '\n';

  // std::cout << "List 1: \n";
  // for (int element : list1) {
  //   std::cout << element << '\n';
  // }
  //
  // std::cout << "\nList 2: \n";
  // for (int element : list2) {
  //   std::cout << element << '\n';
  // }

  return 0;
}
