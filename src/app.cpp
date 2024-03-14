#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"
#include "core.hpp"
#include "commands.hpp"
#include "bootstrap.hpp"

int main() {
  App app = bootstrap();

  do {
    std::string input;
    std::getline(std::cin, input);
    if (utils::toupper(input) == "EXIT") {
      break;
    }
    std::string output = app.command(input);
    std::cout << output << std::endl;
  } while (true);

  return 0;
}
