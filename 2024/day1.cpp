#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // read data from input file
  ifstream inputFile{"input.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  string inputStr{};

  vector<int> list1;
  vector<int> list2;

  int count{1};

  // extract data
  while (inputFile >> inputStr) {
    // convert input data to integer
    int inputNum{stoi(inputStr)};

    // extract data in each column to its own list
    if (count % 2 != 0) {
      list1.push_back(inputNum);
    } else {
      list2.push_back(inputNum);
    }

    count++;
  }

  // sort both lists in ascending order
  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());

  // calculate total distance
  int sum{0};

  for (long unsigned int i = 0; i < size(list1); i++) {
    sum = sum + abs(list1[i] - list2[i]);
  }

  cout << "total distance: " << sum << '\n';

  // calculate similarity score
  int score{0};

  for (int j : list1) {
    int elementCount{0};

    // find number of occurrence of target element
    for (int k : list2) {
      if (j == k) {
        elementCount++;
      }
    }

    score = score + (j * elementCount);
  }

  cout << "similarity score: " << score << '\n';

  return 0;
}
