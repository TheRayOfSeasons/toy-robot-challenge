#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Vector2 {
 public:
  int x;
  int y;
  Vector2(int _x, int _y) : x(_x), y(_y) {}
};

namespace utils {
  // TAKEN from: https://favtutor.com/blogs/split-string-cpp
  std::vector<std::string> splitString(std::string str, char separator) {
    std::vector<std::string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
      // If we reached the end of the word or the end of the input.
      if (str[i] == separator || i == str.size()) {
        endIndex = i;
        std::string temp;
        temp.append(str, startIndex, endIndex - startIndex);
        strings.push_back(temp);
        startIndex = endIndex + 1;
      }
    }
    return strings;
  }

  // TAKEN from:
  // https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring trim from
  // start (in place)
  inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
              return !std::isspace(ch);
            }));
  }

  // TAKEN from:
  // https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring trim from
  // end (in place)
  inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                        [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }

  // TAKEN from:
  // https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring trim from
  // both ends (in place)
  inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
  }

  // TAKEN from: https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
  std::string toupper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
  }
}  // namespace utils

namespace enums {
  enum Direction : int {
    UNSET_DIRECTION = -1,
    NORTH = 0,
    WEST = 1,
    SOUTH = 2,
    EAST = 3,
  };
}

std::string getDirectionName(enums::Direction direction) {
  switch (direction) {
    case enums::NORTH:
      return "NORTH";
    case enums::WEST:
      return "WEST";
    case enums::SOUTH:
      return "SOUTH";
    case enums::EAST:
      return "EAST";
    default:
      return "";
  }
}

enums::Direction getDirectionKey(std::string directionName) {
  if (directionName == "NORTH") {
    return enums::NORTH;
  } else if (directionName == "WEST") {
    return enums::WEST;
  } else if (directionName == "SOUTH") {
    return enums::SOUTH;
  } else if (directionName == "EAST") {
    return enums::EAST;
  }
  return enums::NORTH;
}

class TableTop {
 public:
  Vector2 dimensions;
  TableTop(Vector2 _dimensions) : dimensions(_dimensions) {}
};

class Robot {
 public:
  Vector2 position = Vector2(-1, -1);
  enums::Direction direction = enums::UNSET_DIRECTION;
  TableTop table;

 public:
  Robot(TableTop _table): table(_table) {}

 public:
  bool isConfigured() {
    if (this->position.x == -1) {
      return false;
    }
    if (this->position.y == -1) {
      return false;
    }
    if (this->direction == enums::UNSET_DIRECTION) {
      return false;
    }
    return true;
  }

 public:
  void setTable(TableTop _tableTop) { this->table = _tableTop; }

 public:
  void setX(int x) {
    if (x > this->table.dimensions.x) {
      return;
    }
    if (x < 0) {
      return;
    }
    this->position.x = x;
  }

 public:
  void setY(int y) {
    if (y > this->table.dimensions.y) {
      return;
    }
    if (y < 0) {
      return;
    }
    this->position.y = y;
  }

 public:
  void setDirection(std::string directionName) {
    enums::Direction _direction = getDirectionKey(directionName);
    this->direction = _direction;
  }

 public:
  void setDirection(enums::Direction direction) { this->direction = direction; }
};

class Command {
 public:
  virtual bool requireConfigured() { return true; };
 public:
  virtual std::string run(std::string input, Robot* robot) { return ""; }
};

class App {
 public:
  Robot* robot;
  std::map<std::string, Command*> commands;

 public:
  App(Robot* _robot) : robot(_robot) {}

 public:
  void registerCommand(std::string key, Command* command) {
    this->commands[key] = command;
  }

 public:
  void setRobot(Robot* _robot) { this->robot = _robot; }

 public:
  std::string command(std::string input) {
    input = utils::toupper(input);
    utils::trim(input);
    std::string prefix = utils::splitString(input, ' ')[0];
    auto command = this->commands[prefix];
    if (command->requireConfigured() && !this->robot->isConfigured()) {
      return "";
    }
    std::string output = command->run(input, this->robot);
    std::cout << output << std::endl;
    return output;
  }
};

class MoveCommand : public Command {
 public:
  std::string run(std::string input, Robot* robot) override {
    switch (robot->direction) {
      case enums::NORTH:
        robot->setY(robot->position.y + 1);
        break;
      case enums::WEST:
        robot->setX(robot->position.x - 1);
        break;
      case enums::SOUTH:
        robot->setY(robot->position.y - 1);
        break;
      case enums::EAST:
        robot->setX(robot->position.x + 1);
        break;
      default:
        break;
    }
    return "";
  }
};

class PlaceCommand : public Command {
 public:
  bool requireConfigured() override { return false; };
 public:
  std::string run(std::string input, Robot* robot) override {
    int x, y;
    std::string direction;
    std::string rawValues = utils::splitString(input, ' ')[1];
    std::vector<std::string> values = utils::splitString(rawValues, ',');
    try {
      std::string rawX = values[0];
      std::string rawY = values[1];
      direction = utils::toupper(values[2]);
      x = stoi(rawX);
      y = stoi(rawY);
    } catch (std::exception& e) {
      // Fail softly. No need to do anything for invalid outputs.
      return "Invalid PLACE arguments. Should be using format like: PLACE "
             "0,0,NORTH";
    }
    robot->setX(x);
    robot->setY(y);
    try {
      robot->setDirection(direction);
    } catch (std::exception& e) {
      return "Received invalid direction. Should only be one of the following: "
             "NORTH, WEST, SOUTH, EAST";
    }
    return "";
  }
};

class LeftCommand : public Command {
 public:
  std::string run(std::string input, Robot* robot) override {
    switch (robot->direction) {
      case enums::NORTH:
        robot->setDirection(enums::WEST);
        break;
      case enums::WEST:
        robot->setDirection(enums::SOUTH);
        break;
      case enums::SOUTH:
        robot->setDirection(enums::EAST);
        break;
      case enums::EAST:
        robot->setDirection(enums::NORTH);
        break;
      default:
        break;
    }
    return "";
  }
};

class RightCommand : public Command {
 public:
  std::string run(std::string input, Robot* robot) override {
    switch (robot->direction) {
      case enums::NORTH:
        robot->setDirection(enums::EAST);
        break;
      case enums::WEST:
        robot->setDirection(enums::NORTH);
        break;
      case enums::SOUTH:
        robot->setDirection(enums::WEST);
        break;
      case enums::EAST:
        robot->setDirection(enums::SOUTH);
        break;
      default:
        break;
    }
    return "";
  }
};

class ReportCommand : public Command {
 public:
  std::string run(std::string input, Robot* robot) override {
    std::string output = "Output: " + std::to_string(robot->position.x) + "," +
                         std::to_string(robot->position.y) + "," +
                         getDirectionName(robot->direction);
    return output;
  }
};

App bootstrap() {
  Vector2 tableDimensions(5, 5);
  TableTop* table = new TableTop(tableDimensions);
  Robot* robot = new Robot(*table);
  App* app = new App(robot);

  MoveCommand* moveCommand = new MoveCommand();
  PlaceCommand* placeCommand = new PlaceCommand();
  LeftCommand* leftCommand = new LeftCommand();
  RightCommand* rightCommand = new RightCommand();
  ReportCommand* reportCommand = new ReportCommand();
  app->registerCommand("MOVE", moveCommand);
  app->registerCommand("PLACE", placeCommand);
  app->registerCommand("LEFT", leftCommand);
  app->registerCommand("RIGHT", rightCommand);
  app->registerCommand("REPORT", reportCommand);

  return *app;
}

int main() {
  App app = bootstrap();

  do {
    std::string input;
    std::getline(std::cin, input);
    if (utils::toupper(input) == "EXIT") {
      break;
    }
    app.command(input);
  } while (true);

  return 0;
}
