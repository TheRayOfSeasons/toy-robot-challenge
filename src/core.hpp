class Vector2 {
 public:
  int x;
  int y;
  Vector2(int _x, int _y) : x(_x), y(_y) {}
};

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
    return output;
  }
};
