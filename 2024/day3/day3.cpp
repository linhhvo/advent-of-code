#include <cstddef>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

// calculate the sum of multiplications that match mul(X,Y) instruction in a
// given string input
int calculateSum(string inputStr) {
  int sum{0};

  regex mulPattern{"mul\\((\\d+),(\\d+)\\)"};
  /** regex pattern components:
   * mul    - matches the fixed string "mul"
   * \(     - matches the opening parenthesis
   * (\d+)  - capturing group for the first number
   * ,      - matches the comma
   * (\d+)  - capturing group for the second number
   * \)     - matches the closing parenthesis
   */

  smatch matchedResults;

  while (regex_search(inputStr, matchedResults, mulPattern)) {
    // extract numbers from regex capturing groups and convert to integers
    int num1{stoi(matchedResults[1].str())};
    int num2{stoi(matchedResults[2].str())};

    sum = sum + (num1 * num2);

    // replace input string with the substring follows the end of the matched
    // result
    inputStr = matchedResults.suffix().str();
  }

  return sum;
}

int main() {

  ifstream inputFile{"input.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  stringstream ss;
  int finalSum{0};

  ss << inputFile.rdbuf();

  string subStr{ss.str()};
  size_t pos{};

  while (pos != string::npos) {
    subStr = subStr.substr(pos);

    pos = subStr.find("don't()");

    // if don't() instruction is not found
    if (pos == string::npos) {
      finalSum += calculateSum(subStr);
      break;
    }

    string untilDont{subStr.substr(0, pos)};
    finalSum += calculateSum(untilDont);

    // update substring to start after don't()
    subStr = subStr.substr(pos);

    pos = subStr.find("do()");
  }

  cout << "final result: " << finalSum << '\n';

  return 0;
}
