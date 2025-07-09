
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// split input string into list of numbers
vector<int> splitStr(string inputStr) {
  string subData{inputStr};
  vector<int> dataList;

  while (!subData.empty()) {
    size_t deliPos = subData.find(' ');

    if (deliPos != string::npos) {
      string dataPointStr{subData.substr(0, deliPos)};

      dataList.push_back(stoi(dataPointStr));
      subData = subData.substr(deliPos + 1);
    } else {
      dataList.push_back(stoi(subData));

      subData = "";
    }
  }

  return dataList;
}

// compare function for descending order
bool descComp(int first, int next) { return first > next; }

// find the first bad level from the data list
int findBadLevel(vector<int> dataList) {
  // check if all data points are sorted in either order
  if (is_sorted(dataList.begin(), dataList.end()) ||
      is_sorted(dataList.begin(), dataList.end(), descComp)) {

    // check the difference between two adjacent data points
    for (int i = 0; i < static_cast<int>(size(dataList)) - 1; i++) {
      int dataDiff = abs(dataList[i] - dataList[i + 1]);
      if (dataDiff == 0 || dataDiff > 3) {
        cout << "unsafe because of diff\n";
        return i + 1;
      }
    }
  } else {
    auto notSortedData = is_sorted_until(dataList.begin(), dataList.end());
    cout << "unsafe because of sort order\n";
    return (notSortedData - dataList.begin());
  }
  // if no bad data level
  return size(dataList);
}

int main() {
  ifstream inputFile{"test.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  string inputLine{};

  [[maybe_unused]] int safeCount{0};

  while (getline(inputFile, inputLine)) {
    vector<int> dataList{splitStr(inputLine)};

    bool isSafe{true};

    int badDataLevel = findBadLevel(dataList);

    if (badDataLevel != static_cast<int>(size(dataList))) {

      for (int i : dataList) {
        cout << i << ' ';
      }

      isSafe = false;
      cout << '\n' << badDataLevel << '\n';
    }

    if (isSafe) {
      safeCount++;
    }
  }
  //
  // cout << "safe report count: " << safeCount << '\n';

  return 0;
}
