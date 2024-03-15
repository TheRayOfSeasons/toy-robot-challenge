#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "lib/utils.hpp"
#include "lib/core.hpp"
#include "lib/commands.hpp"
#include "lib/bootstrap.hpp"

void should(std::string message) {
  std::cout << std::endl;
  std::cout << "Should: "<< message << std::endl;
}

void expects(std::string input, std::string output) {
  std::cout << "Expects: " << output << std::endl;
  utils::trim(input);
  if (input != output) {
    std::string message = "Test Failed. Got " + input;
    std::cout << message << std::endl;
    throw message;
  } else {
    std::cout << "Passed." << std::endl;
  }
}

int main() {
  App app = bootstrap();

  should("ignore everything if place is not yet entered");
  app.command("MOVE");
  app.command("LEFT");
  app.command("RIGHT");
  app.command("MOVE");
  expects(app.command("REPORT"), "");

  should("set place");
  app.command("PLACE 0,0,NORTH");
  expects(app.command("REPORT"), "Output: 0,0,NORTH");

  should("properly arrive to destination");
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

  should("not exceed 5 units in every direction");
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

  should("ignore invalid inputs");
  app.command("im an invalid input");
  app.command("this should be ignored");
  expects(app.command("REPORT"), "Output: 5,0,EAST");

  should("handle lowercase");
  app.command("left");
  app.command("move");
  expects(app.command("report"), "Output: 5,1,NORTH");

  should("handle untrimmed");
  app.command("     left ");
  app.command(" move     ");
  expects(app.command("report"), "Output: 4,1,WEST");

  should("handle inconsistent casing");
  app.command("     lEft ");
  app.command(" MoVe     ");
  expects(app.command("report"), "Output: 4,0,SOUTH");

  should("ignore invalid place commands");
  app.command("PLACE 1,1,q");
  app.command("PLACE -1,x,22");
  expects(app.command("report"), "Output: 4,0,SOUTH");

  should("ignore place commands with coordinates that exceed the table's dimensios");
  app.command("PLACE 7,1,NORTH");
  app.command("PLACE 7,7,EAST");
  app.command("PLACE 1,7,WEST");
  app.command("PLACE 0,37,SOUTH");
  expects(app.command("report"), "Output: 4,0,SOUTH");

  return 0;
}
