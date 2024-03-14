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