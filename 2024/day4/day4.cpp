#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int isXmasVertical(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  int isXmas = 0;

  // check both up and down directions
  if (rowIdx > 2 && rowIdx < static_cast<int>(input2d.size()) - 3) {
    if (input2d[rowIdx + 1][colIdx] == 'M' &&
        input2d[rowIdx + 2][colIdx] == 'A' &&
        input2d[rowIdx + 3][colIdx] == 'S') {
      isXmas = 1;
    } else if (input2d[rowIdx - 1][colIdx] == 'M' &&
               input2d[rowIdx - 2][colIdx] == 'A' &&
               input2d[rowIdx - 3][colIdx] == 'S') {
      isXmas = 1;
    }
  }
  // only check down direction
  else if (rowIdx < 3) {
    if (input2d[rowIdx + 1][colIdx] == 'M' &&
        input2d[rowIdx + 2][colIdx] == 'A' &&
        input2d[rowIdx + 3][colIdx] == 'S') {
      isXmas = 1;
    }
  }
  // only check up direction
  else {
    if (input2d[rowIdx - 1][colIdx] == 'M' &&
        input2d[rowIdx - 2][colIdx] == 'A' &&
        input2d[rowIdx - 3][colIdx] == 'S') {
      isXmas = 1;
    }
  }

  return isXmas;
}

int isXmasHorizontal(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  int isXmas = 0;
  vector<char> currentRow{input2d[rowIdx]};

  // check both left and right directions
  if (colIdx > 2 && colIdx < static_cast<int>(currentRow.size()) - 3) {
    if (currentRow[colIdx + 1] == 'M' && currentRow[colIdx + 2] == 'A' &&
        currentRow[colIdx + 3] == 'S') {
      isXmas = 1;
    } else if (currentRow[colIdx - 1] == 'M' && currentRow[colIdx - 2] == 'A' &&
               currentRow[colIdx - 3] == 'S') {
      isXmas = 1;
    }
  }
  // check only right direction
  else if (colIdx < 3) {
    if (currentRow[colIdx + 1] == 'M' && currentRow[colIdx + 2] == 'A' &&
        currentRow[colIdx + 3] == 'S') {
      isXmas = 1;
    }
  }
  // check only left direction
  else {
    if (currentRow[colIdx - 1] == 'M' && currentRow[colIdx - 2] == 'A' &&
        currentRow[colIdx - 3] == 'S') {
      isXmas = 1;
    }
  }

  return isXmas;
}

int isXmasFound(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  if (isXmasVertical(rowIdx, colIdx, input2d) ||
      isXmasHorizontal(rowIdx, colIdx, input2d)) {
    return 1;
  }

  return 0;
}

int main() {
  ifstream inputFile{"test.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  vector<vector<char>> allInput;

  string tempLine{};

  // store input in a 2D vector
  while (getline(inputFile, tempLine)) {
    vector<char> lineInput;
    for (char c : tempLine) {
      lineInput.push_back(c);
    }
    allInput.push_back(lineInput);
  }

  int count{0};

  for (size_t i{0}; i < allInput.size(); ++i) {
    for (size_t j{0}; j < allInput[i].size(); ++j) {
      if (allInput[i][j] == 'X') {
        cout << "X found at (" << i << ", " << j << ")\n";
        if (isXmasFound(i, j, allInput) == 1) {
          count++;
          cout << "xmas found\n";
        };
      }
      // cout << allInput[i][j] << ", ";
    }
    // cout << '\n';
  }

  cout << count;
  cout << '\n';

  return 0;
}
