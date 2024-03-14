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
