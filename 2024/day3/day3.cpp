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

  finalSum += calculateSum(ss.str());

  cout << "multiply result: " << finalSum << '\n';

  return 0;
}
