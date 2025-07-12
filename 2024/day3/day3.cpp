#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {

  ifstream inputFile{"input.txt"};

  if (!inputFile) {
    cerr << "Can't open input file.\n";
    return 1;
  }

  string inputStr{};
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

  while (getline(inputFile, inputStr)) {
    while (regex_search(inputStr, matchedResults, mulPattern)) {
      // extract numbers from regex capturing groups and convert to integers
      int num1{stoi(matchedResults[1].str())};
      int num2{stoi(matchedResults[2].str())};

      sum = sum + (num1 * num2);

      // replace input string with the substring follows the end of the matched
      // result
      inputStr = matchedResults.suffix().str();
    }
  }

  cout << "multiply result: " << sum << '\n';

  return 0;
}
