#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int verticalCount(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  int xmasCount = 0;

  // check both up and down directions
  if (rowIdx > 2 && rowIdx < static_cast<int>(input2d.size()) - 3) {
    if (input2d[rowIdx + 1][colIdx] == 'M' &&
        input2d[rowIdx + 2][colIdx] == 'A' &&
        input2d[rowIdx + 3][colIdx] == 'S') {
      xmasCount++;
    }

    if (input2d[rowIdx - 1][colIdx] == 'M' &&
        input2d[rowIdx - 2][colIdx] == 'A' &&
        input2d[rowIdx - 3][colIdx] == 'S') {
      xmasCount++;
    }
  }
  // only check down direction
  else if (rowIdx < 3) {
    if (input2d[rowIdx + 1][colIdx] == 'M' &&
        input2d[rowIdx + 2][colIdx] == 'A' &&
        input2d[rowIdx + 3][colIdx] == 'S') {
      xmasCount++;
    }
  }
  // only check up direction
  else {
    if (input2d[rowIdx - 1][colIdx] == 'M' &&
        input2d[rowIdx - 2][colIdx] == 'A' &&
        input2d[rowIdx - 3][colIdx] == 'S') {
      xmasCount++;
    }
  }

  return xmasCount;
}

int horizontalCount(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  int xmasCount = 0;
  vector<char> currentRow{input2d[rowIdx]};

  // check both left and right directions
  if (colIdx > 2 && colIdx < static_cast<int>(currentRow.size()) - 3) {
    if (currentRow[colIdx + 1] == 'M' && currentRow[colIdx + 2] == 'A' &&
        currentRow[colIdx + 3] == 'S') {
      xmasCount++;
    }

    if (currentRow[colIdx - 1] == 'M' && currentRow[colIdx - 2] == 'A' &&
        currentRow[colIdx - 3] == 'S') {
      xmasCount++;
    }
  }
  // check only right direction
  else if (colIdx < 3) {
    if (currentRow[colIdx + 1] == 'M' && currentRow[colIdx + 2] == 'A' &&
        currentRow[colIdx + 3] == 'S') {
      xmasCount++;
    }
  }
  // check only left direction
  else {
    if (currentRow[colIdx - 1] == 'M' && currentRow[colIdx - 2] == 'A' &&
        currentRow[colIdx - 3] == 'S') {
      xmasCount++;
    }
  }

  return xmasCount;
}

int diagonalDownCount(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  int xmasCount = 0;
  vector<char> currentRow{input2d[rowIdx]};

  if (rowIdx < static_cast<int>(input2d.size()) - 3) {
    // check both down diagonal left and right directions
    if (colIdx > 2 && colIdx < static_cast<int>(currentRow.size()) - 3) {
      if (input2d[rowIdx + 1][colIdx + 1] == 'M' &&
          input2d[rowIdx + 2][colIdx + 2] == 'A' &&
          input2d[rowIdx + 3][colIdx + 3] == 'S') {
        xmasCount++;
      }

      if (input2d[rowIdx + 1][colIdx - 1] == 'M' &&
          input2d[rowIdx + 2][colIdx - 2] == 'A' &&
          input2d[rowIdx + 3][colIdx - 3] == 'S') {
        xmasCount++;
      }
    }
    // check down diagonal only right direction
    else if (colIdx < 3) {
      if (input2d[rowIdx + 1][colIdx + 1] == 'M' &&
          input2d[rowIdx + 2][colIdx + 2] == 'A' &&
          input2d[rowIdx + 3][colIdx + 3] == 'S') {
        xmasCount++;
      }
    }
    // check down diagonal only left direction
    else {
      if (input2d[rowIdx + 1][colIdx - 1] == 'M' &&
          input2d[rowIdx + 2][colIdx - 2] == 'A' &&
          input2d[rowIdx + 3][colIdx - 3] == 'S') {
        xmasCount++;
      }
    }
  }
  return xmasCount;
}

int diagonalUpCount(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  int xmasCount = 0;
  vector<char> currentRow{input2d[rowIdx]};

  if (rowIdx > 2) {
    // check both up diagonal left and right directions
    if (colIdx > 2 && colIdx < static_cast<int>(currentRow.size()) - 3) {
      if (input2d[rowIdx - 1][colIdx - 1] == 'M' &&
          input2d[rowIdx - 2][colIdx - 2] == 'A' &&
          input2d[rowIdx - 3][colIdx - 3] == 'S') {
        xmasCount++;
      }

      if (input2d[rowIdx - 1][colIdx + 1] == 'M' &&
          input2d[rowIdx - 2][colIdx + 2] == 'A' &&
          input2d[rowIdx - 3][colIdx + 3] == 'S') {
        xmasCount++;
      }
    }
    // check up diagonal only right direction
    else if (colIdx < 3) {
      if (input2d[rowIdx - 1][colIdx + 1] == 'M' &&
          input2d[rowIdx - 2][colIdx + 2] == 'A' &&
          input2d[rowIdx - 3][colIdx + 3] == 'S') {
        xmasCount++;
      }
    }
    // check up diagonal only left direction
    else {
      if (input2d[rowIdx - 1][colIdx - 1] == 'M' &&
          input2d[rowIdx - 2][colIdx - 2] == 'A' &&
          input2d[rowIdx - 3][colIdx - 3] == 'S') {
        xmasCount++;
      }
    }
  }
  return xmasCount;
}

int xmasFoundCount(int rowIdx, int colIdx, vector<vector<char>> input2d) {
  return (verticalCount(rowIdx, colIdx, input2d) +
          horizontalCount(rowIdx, colIdx, input2d) +
          diagonalDownCount(rowIdx, colIdx, input2d) +
          diagonalUpCount(rowIdx, colIdx, input2d));
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
      if (allInput[i][j] == 'X') {
        cout << "X found at (" << i << ", " << j << ")\n";
        int numOfXmas{xmasFoundCount(i, j, allInput)};
        if (numOfXmas > 0) {
          count = count + numOfXmas;
          cout << numOfXmas << " xmas found\n";
        };
      }
    }
  }

  cout << "\nnum of xmas: " << count;
  cout << "\n\n";

  return 0;
}
