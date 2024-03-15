/**
 * A command that moves the robot forwards to the direction it is facing.
 */
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

/**
 * A command that places the robot in an arbitrary position that the user
 * desires.
 */
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
      utils::trim(rawX);
      std::string rawY = values[1];
      utils::trim(rawY);
      direction = utils::toupper(values[2]);
      utils::trim(direction);
      x = stoi(rawX);
      y = stoi(rawY);
    } catch (std::exception& e) {
      // Fail softly. No need to do anything for invalid outputs.
      return "Invalid PLACE arguments. Should be using format like: PLACE "
             "0,0,NORTH";
    }
    bool directionSet = false;
    std::string invalidDirectionMessage =
        "Received invalid direction. Should only be one of the following: "
        "NORTH, WEST, SOUTH, EAST";
    try {
      directionSet = robot->setDirection(direction);
    } catch (std::exception& e) {
      return invalidDirectionMessage;
    }
    if (!directionSet) {
      return invalidDirectionMessage;
    }
    // Direction should be valid first before setting position.
    robot->setX(x);
    robot->setY(y);
    return "";
  }
};

/**
 * A command that turns the robot left relative to the current direction it is
 * facing.
 */
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

/**
 * A command that turns the robot right relative to the current direction it is
 * facing.
 */
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

/**
 * A command that reports the current status of the robot.
 */
class ReportCommand : public Command {
 public:
  std::string run(std::string input, Robot* robot) override {
    std::string output = "Output: " + std::to_string(robot->position.x) + "," +
                         std::to_string(robot->position.y) + "," +
                         getDirectionName(robot->direction);
    return output;
  }
};
