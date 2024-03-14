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

void should(std::string message) {
  std::cout << std::endl;
  std::cout << "Should: "<< message << std::endl;
}

void expects(std::string input, std::string output) {
  std::cout << "Expects: " << output << std::endl;
  if (input != output) {
    std::string message = "Test Failed. Got " + input;
    std::cout << message<< std::endl;
    throw message;
  } else {
    std::cout << "Passed." << std::endl;
  }
}

int main() {
  App app = bootstrap();
  std::string output, expected;

  should("not report anything if place is not yet entered");
  app.command("MOVE");
  app.command("LEFT");
  app.command("RIGHT");
  app.command("MOVE");
  expects(app.command("REPORT"), "");

  should("properly arrive to destination");
  app.command("PLACE 0,0,NORTH");
  app.command("MOVE");
  app.command("MOVE");
  expects(app.command("REPORT"), "Output: 0,2,NORTH");

  app.command("MOVE");
  app.command("RIGHT");
  app.command("MOVE");
  expects(app.command("REPORT"), "Output: 1,3,EAST");

  app.command("LEFT");
  app.command("MOVE");
  expects(app.command("REPORT"), "Output: 1,4,NORTH");

  should("place be overridable");
  app.command("PLACE 3,2,SOUTH");
  expects(app.command("REPORT"), "Output: 3,2,SOUTH");

  should("move after override");
  app.command("MOVE");
  app.command("MOVE");
  app.command("MOVE");
  expects(app.command("REPORT"), "Output: 3,0,SOUTH");

  should("not exceed 5 units in distance");
  app.command("MOVE");
  app.command("MOVE");
  app.command("MOVE");
  expects(app.command("REPORT"), "Output: 3,0,SOUTH");
  app.command("LEFT");
  app.command("MOVE");
  app.command("MOVE");
  app.command("MOVE");
  app.command("MOVE");
  expects(app.command("REPORT"), "Output: 5,0,EAST");

  return 0;
}
