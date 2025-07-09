
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream inputFile{"input.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  string inputLine{};

  int safeCount{0};

  while (getline(inputFile, inputLine)) {

    string subData{inputLine};
    vector<int> dataList;

    // extract each data point to a data list
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

    bool isSafe{true};

    vector<int> dataListRev(size(dataList));

    reverse_copy(dataList.begin(), dataList.end(), dataListRev.begin());

    // check if all data points are sorted in either order
    if (is_sorted(dataList.begin(), dataList.end()) ||
        is_sorted(dataListRev.begin(), dataListRev.end())) {

      // check the difference between two adjacent data points
      for (int i = 0; i < static_cast<int>(size(dataList)) - 1; i++) {
        int dataDiff = abs(dataList[i] - dataList[i + 1]);
        if (dataDiff == 0 || dataDiff > 3) {
          isSafe = false;
          break;
        }
      }
    } else {
      isSafe = false;
    }

    if (isSafe) {
      safeCount++;
    }
  }

  cout << "safe report count: " << safeCount << '\n';

  return 0;
}
