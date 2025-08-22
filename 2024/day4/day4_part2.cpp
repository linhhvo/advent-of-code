#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int isDiagonalLeft(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  // check diagonal direction from left
  int isMAS = 0;
  vector<char> currentRow{input2d[rowIdx]};
  int colNum = static_cast<int>(input2d.size()) - 1;
  int rowNum = static_cast<int>(currentRow.size()) - 1;

  if (colIdx > 0 && colIdx < colNum && rowIdx > 0 && rowIdx < rowNum) {
    if (input2d[rowIdx - 1][colIdx - 1] == 'M' &&
        input2d[rowIdx + 1][colIdx + 1] == 'S') {
      isMAS = 1;
    } else if (input2d[rowIdx - 1][colIdx - 1] == 'S' &&
               input2d[rowIdx + 1][colIdx + 1] == 'M') {
      isMAS = 1;
    }
  }

  return isMAS;
}

int isDiagonalRight(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  // check diagonal direction from right
  int isMAS = 0;
  vector<char> currentRow{input2d[rowIdx]};
  int colNum = static_cast<int>(input2d.size()) - 1;
  int rowNum = static_cast<int>(currentRow.size()) - 1;

  if (colIdx > 0 && colIdx < colNum && rowIdx > 0 && rowIdx < rowNum) {
    if (input2d[rowIdx - 1][colIdx + 1] == 'M' &&
        input2d[rowIdx + 1][colIdx - 1] == 'S') {
      isMAS = 1;
    } else if (input2d[rowIdx - 1][colIdx + 1] == 'S' &&
               input2d[rowIdx + 1][colIdx - 1] == 'M') {
      isMAS = 1;
    }
  }

  return isMAS;
}

int crossMasFound(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  return isDiagonalLeft(rowIdx, colIdx, input2d) &&
         isDiagonalRight(rowIdx, colIdx, input2d);
}

int main() {
  // ifstream inputFile{"test.txt"};
  ifstream inputFile{"input.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  vector<vector<char>> allInput;

  string tempLine{};

  // store input in a 2D vector
  while (getline(inputFile, tempLine)) {
    vector<char> lineChar;
    for (char c : tempLine) {
      lineChar.push_back(c);
    }
    allInput.push_back(lineChar);
  }

  int count{0};

  for (size_t i{0}; i < allInput.size(); ++i) {
    for (size_t j{0}; j < allInput[i].size(); ++j) {
      if (allInput[i][j] == 'A') {
        cout << "A found at (" << i << ", " << j << ")\n";
        if (crossMasFound(i, j, allInput) == 1) {
          count++;
          cout << "X-MAS found\n";
        };
      }
    }
  }

  cout << "\nnum of X-MAS: " << count;
  cout << "\n\n";

  return 0;
}
