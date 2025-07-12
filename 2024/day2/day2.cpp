#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// split input string into list of numbers
vector<int> splitStr(string inputStr) {
  stringstream ss;
  string subData{};
  vector<int> dataList;

  ss.str(inputStr);

  while (getline(ss, subData, ' ')) {
    dataList.push_back(stoi(subData));
  }
  return dataList;
}

// compare function for descending order
bool descComp(int first, int next) { return first > next; }

// check if a data report is safe
bool isSafe(vector<int> dataList) {
  // check if all data points are sorted in either order
  if (is_sorted(dataList.begin(), dataList.end()) ||
      is_sorted(dataList.begin(), dataList.end(), descComp)) {

    // check the difference between two adjacent data points
    for (int i = 0; i < static_cast<int>(size(dataList)) - 1; i++) {
      int dataDiff = abs(dataList[i] - dataList[i + 1]);
      if (dataDiff == 0 || dataDiff > 3) {
        return 0;
      }
    }
  } else {
    return 0;
  }
  return 1;
}

int main() {
  ifstream inputFile{"input.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  string inputLine{};

  int safeCount{0};

  while (getline(inputFile, inputLine)) {
    vector<int> dataList{splitStr(inputLine)};

    if (isSafe(dataList)) {
      safeCount++;
    }
  }

  cout << "safe report count: " << safeCount << '\n';

  return 0;
}
