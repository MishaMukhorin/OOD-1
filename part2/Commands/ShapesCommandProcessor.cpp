//
// Created by Misha on 29.03.2024.
//
#include "ShapesCommandProcessor.h"

using namespace std;

using ShapeFunction = function<void(string, unique_ptr<shapes::Shape>)>;

void ShapeCommandExec(const ShapeFunction& command, const string& commandType, const string& id, const string& color, const string& commandStr, shapes::Picture &picture)
{
    const string POSNUM = R"((\d+(?:\.\d+)?))";
    const string COORD = R"((-?\d+(?:\.\d+)?))";
    const string S = R"(\s+)";
    unique_ptr<shapes::Shape> newShape;

    vector<pair<regex, function<void(const smatch &match)>>> commandMap
            {
                    // Rectangle: command <id> rectangle <x> <y> <width> <height>
                    {regex(commandType + R"(\s+rectangle\s+)" + COORD + S + COORD + S + POSNUM + S + POSNUM),
                            [&newShape, id, color](const smatch &match)
                            {
                                double x = stod(match[1].str());
                                double y = stod(match[2].str());
                                double width = stod(match[3].str());
                                double height = stod(match[4].str());

                                newShape = make_unique<shapes::Rectangle>(id, color, x, y, width, height);
                            }},

                    // Circle: command <id> circle <x> <y> <radius>
                    {regex(commandType + R"(\s+circle\s+)" + COORD + S + COORD + S + POSNUM),
                            [&newShape, id, color](const smatch &match)
                            {
                                double x = stod(match[1].str());
                                double y = stod(match[2].str());
                                double radius = stod(match[3].str());

                                newShape = make_unique<shapes::Circle>(id, color, x, y, radius);
                            }},

                    // Triangle: command <id> triangle <x1> <y1> <x2> <y2> <x3> <y3>
                    {regex(commandType + R"(\s+triangle\s+)" + COORD + S + COORD + S + COORD + S + COORD +
                            S + COORD + S + COORD),[&newShape, id, color](const smatch &match)
                            {
                                double x1 = stod(match[1].str());
                                double y1 = stod(match[2].str());
                                double x2 = stod(match[3].str());
                                double y2 = stod(match[4].str());
                                double x3 = stod(match[5].str());
                                double y3 = stod(match[6].str());

                                newShape = make_unique<shapes::Triangle>(id, color, x1, y1, x2, y2, x3, y3);
                            }},

                    // Line: command <id> line <x1> <y1> <x2> <y2>
                    {regex(commandType + R"(\s+line\s+)" + COORD + S + COORD + S + COORD + S + COORD),
                            [&newShape, id, color](const smatch &match)
                            {
                                double x1 = stod(match[1].str());
                                double y1 = stod(match[2].str());
                                double x2 = stod(match[3].str());
                                double y2 = stod(match[4].str());

                                newShape = make_unique<shapes::Line>(id, color, x1, y1, x2, y2);
                            }},

                    // Text: command <id> text <x> <y> <size> <text>
                    {regex(commandType + R"(text\s+)" + COORD + S + COORD + S + POSNUM + S + R"((.+))"),
                            [&newShape, id, color](const smatch &match)
                            {
                                double x = stod(match[1].str());
                                double y = stod(match[2].str());
                                double size = stod(match[3].str());
                                string text = match[4].str();

                                newShape = make_unique<shapes::Text>(id, color, x, y, size, text);
                            }},
            };

    for (const auto& createShape : commandMap)
    {
        smatch match;
        if (regex_search(commandStr, match, createShape.first))
        {
            createShape.second(match);
            command(id, std::move(newShape));
            return;
        }
    }
    cout << "error: invalid command!" << endl;
}


void LineProcessor(const std::string &line, shapes::Picture &picture)
{
    const string POSNUM = R"((\d+(?:\.\d+)?))";
    const string COORD = R"((-?\d+(?:\.\d+)?))";
    const string S = R"(\s+)";
    const string COLOR = R"((#[0-9A-Fa-f]{6}))";
//
//     AddShape sh1 #ff00ff circle 100 110 15
//     AddShape circ #febb38 circle 100 200 25
//     AddShape sh2 #123456 rectangle 10 20 30 40
//     AddShape tr1 #00feta triangle 0 0 10 0 0 10
//     AddShape ln1 #fefefe line 10 20 35 -88
//     AddShape txt1 #ffaa88 text 100 100 12 HELLO WORLD

    vector<pair<regex, function<void(const smatch &match)>>> commandMap
            {
                    // AddShape <id> <parameters>
                    {regex(R"((AddShape)\s+([\w\d]+)\s+)" + COLOR + R"(.+)"),
                            [&picture](const smatch &match)
                            {
                                string commandStr = match[0].str();
                                string commandType = match[1].str() + R"(\s+[\w\d]+\s+#[0-9A-Fa-f]{6})";
                                string id = match[2].str();
                                string color = match[3].str();
                                ShapeFunction addShapeFunc;

                                addShapeFunc = [&picture](const std::string& id, std::unique_ptr<shapes::Shape> newShape) {
                                    picture.AddShape(id, std::move(newShape));  // Use std::move to transfer ownership
                                };

                                ShapeCommandExec(addShapeFunc, commandType, id, color, commandStr, picture);
                            }},
                    // ChangeShape <id> <parameters>
                    {regex(R"((ChangeShape)\s+([\w\d]+).+)"),
                            [&picture](const smatch &match)
                            {
                                string commandStr = match[0].str();
                                string commandType = match[1].str() + R"(\s+[\w\d]+\s+)";
                                string id = match[2].str();
                                string color = picture.GetShapeColorById(id);
                                ShapeFunction changeShapeFunc;

                                changeShapeFunc = [&picture](const std::string& id, std::unique_ptr<shapes::Shape> newShape) {
                                    picture.ChangeShape(id, std::move(newShape));  // Use std::move to transfer ownership
                                };

                                ShapeCommandExec(changeShapeFunc, commandType, id, color, commandStr, picture);
                            }},

                    // MoveShape <id> <dx> <dy>
                    {regex(R"(MoveShape\s+([\w\d]+)\s+)" + COORD + S + COORD),
                            [&picture](const smatch &match)
                            {
                                string id = match[1].str();
                                double dx = stod(match[2].str());
                                double dy = stod(match[3].str());

                                picture.MoveShape(id, dx, dy);
                            }},
                    // ChangeColor <id> <цвет>
                    {regex(R"(ChangeColor\s+([\w\d]+)\s+)" + S + COLOR),
                            [&picture](const smatch &match)
                            {
                                string id = match[1].str();
                                string color = match[2].str();

                                picture.ChangeColor(id, color);
                            }},
                    // MovePicture <dx> <dy>
                    {regex(R"(MovePicture)" + COORD + S + COORD),
                            [&picture](const smatch &match)
                            {
                                double dx = stod(match[1].str());
                                double dy = stod(match[2].str());

                                picture.MovePicture(dx, dy);
                            }},
                    // DeleteShape <id>
                    {regex(R"(DeleteShape\s+([\w\d]+))"),
                            [&picture](const smatch &match)
                            {
                                string id = match[1].str();

                                picture.DeleteShape(id);
                            }},
                    // List (output: <номер фигуры> <тип> <id> <цвет> <параметры фигуры>)
                    {regex(R"(List)"),
                            [&picture](const smatch &match)
                            {
                                picture.List();
                            }},
                    // DrawShape <id>
                    {regex(R"(DrawShape\s+([\w\d]+))"),
                            [&picture](const smatch &match)
                            {
                                string id = match[1].str();
                                PNGCanvas canvas(800, 600);

                                picture.DrawShape(id, canvas);
                            }},
                    // DrawPicture
                    {regex(R"(DrawPicture)"),
                            [&picture](const smatch &match)
                            {
                                PNGCanvas canvas(800, 600);

                                picture.DrawPicture(canvas);
                            }},
                    // CloneShape <id> <new-id>
                    {regex(R"(CloneShape\s+([\w\d]+)\s+([\w\d]+))"),
                            [&picture](const smatch &match)
                            {
                                string id = match[1].str();
                                string newId = match[2].str();

                                picture.CloneShape(id, newId);
                            }},
                    // Comment: Ignore comments (lines starting with //)
                    {regex(R"(\/\/.*)"),
                            [](const smatch &match) {}},
                    {regex(R"(\s*)"),
                            [](const smatch &match) {}}
            };
    std::unique_ptr<shapes::Shape> shape;

    for (const auto &cmd: commandMap)
    {
        smatch match;
        if (regex_match(line, match, cmd.first))
        {
            cmd.second(match);
            return;
        }
    }
    cout << "error: invalid command!" << endl;
}


void CommandProcessor(istream &str)
{
    shapes::Picture picture;
    string line;
    while (getline(str, line))
    {
        if (line == "exit")
        {
            break;
        }
        LineProcessor(line, picture);
    }
}

//// Rectangle: AddShape <id> <color> rectangle <x> <y> <width> <height>
//                    {regex(R"(AddShape\s+([\w\d]+)\s+)" + COLOR + R"(\s+rectangle\s+)" + COORD + S + COORD + S + POSNUM + S + POSNUM),
//                            [&picture](const smatch &match)
//                            {
//                                string id = match[1].str();
//                                string color = match[2].str();
//                                double x = stod(match[3].str());
//                                double y = stod(match[4].str());
//                                double width = stod(match[5].str());
//                                double height = stod(match[6].str());
//
//                                picture.AddShape(id, make_unique<shapes::Rectangle>(id, color, x, y, width, height));
//                            }},
//
//                    // Circle: AddShape <id> <color> circle <x> <y> <radius>
//                    {regex(R"(AddShape\s+([\w\d]+)\s+)" + COLOR + R"(\s+circle\s+)" + COORD + S + COORD + S + POSNUM),
//                            [&picture](const smatch &match)
//                            {
//                                string id = match[1].str();
//                                string color = match[2].str();
//                                double x = stod(match[3].str());
//                                double y = stod(match[4].str());
//                                double radius = stod(match[5].str());
//
//                                picture.AddShape(make_unique<shapes::Circle>(id, color, x, y, radius));
//                            }},
//
//                    // Triangle: AddShape <id> <color> triangle <x1> <y1> <x2> <y2> <x3> <y3>
//                    {regex(R"(AddShape\s+([\w\d]+)\s+)" + COLOR + R"(\s+triangle\s+)" + COORD + S + COORD + S + COORD + S + COORD + S + COORD + S + COORD),
//                            [&picture](const smatch &match)
//                            {
//                                string id = match[1].str();
//                                string color = match[2].str();
//                                double x1 = stod(match[3].str());
//                                double y1 = stod(match[4].str());
//                                double x2 = stod(match[5].str());
//                                double y2 = stod(match[6].str());
//                                double x3 = stod(match[7].str());
//                                double y3 = stod(match[8].str());
//
//                                picture.AddShape(make_unique<shapes::Triangle>(id, color, x1, y1, x2, y2, x3, y3));
//                            }},
//
//                    // Line: AddShape <id> <color> line <x1> <y1> <x2> <y2>
//                    {regex(R"(AddShape\s+([\w\d]+)\s+)" + COLOR + R"(\s+line\s+)" + COORD + S + COORD + S + COORD + S + COORD),
//                            [&picture](const smatch &match)
//                            {
//                                string id = match[1].str();
//                                string color = match[2].str();
//                                double x1 = stod(match[3].str());
//                                double y1 = stod(match[4].str());
//                                double x2 = stod(match[5].str());
//                                double y2 = stod(match[6].str());
//
//                                picture.AddShape(make_unique<shapes::Line>(id, color, x1, y1, x2, y2));
//                            }},
//
//                    // Text: AddShape <id> <color> text <x> <y> <size> <text>
//                    {regex(R"(AddShape\s+([\w\d]+)\s+)" + COLOR + R"(\s+text\s+)" + COORD + S + COORD + S + POSNUM + S + R"((.+))"),
//                            [&picture](const smatch &match)
//                            {
//                                string id = match[1].str();
//                                string color = match[2].str();
//                                double x = stod(match[3].str());
//                                double y = stod(match[4].str());
//                                double size = stod(match[5].str());
//                                string text = match[6].str();
//
//                                picture.AddShape(make_unique<shapes::Text>(id, color, x, y, size, text));
//                            }},
//                    // ChangeShape <id> <parameters>
//                    {regex(R"(ChangeShape\s+([\w\d]+).+)"),
//                            [&picture](const smatch &match)
//                            {
//                                string id = match[1].str();
//                                string commandStr = match[0].str();
//
//                                ChangeShapeCommandExec(id, commandStr, picture);
//                            }},

//
//void ChangeShapeCommandExec(const string& id, const string& commandStr, shapes::Picture &picture)
//{
//    const string POSNUM = R"((\d+(?:\.\d+)?))";
//    const string COORD = R"((-?\d+(?:\.\d+)?))";
//    const string S = R"(\s+)";
//    unique_ptr<shapes::Shape> newShape;
//    string color = picture.GetShapeColorById(id);
//
//    vector<pair<regex, function<void(const smatch &match)>>> commandMap
//            {
//                    // Rectangle: ChangeShape <id> rectangle <x> <y> <width> <height>
//                    {regex(R"(ChangeShape\s+([\w\d]+)\s+rectangle\s+)" + COORD + S + COORD + S + POSNUM + S + POSNUM),
//                                                  [&newShape, color](const smatch &match)
//                                                  {
//                                                      string id = match[1].str();
//                                                      double x = stod(match[2].str());
//                                                      double y = stod(match[3].str());
//                                                      double width = stod(match[4].str());
//                                                      double height = stod(match[5].str());
//
//                                                      newShape = make_unique<shapes::Rectangle>(id, color, x, y, width, height);
//                                                  }},
//
//                    // Circle: ChangeShape <id> circle <x> <y> <radius>
//                    {regex(R"(ChangeShape\s+([\w\d]+)\s+circle\s+)" + COORD + S + COORD + S + POSNUM),
//                                                  [&newShape, color](const smatch &match)
//                                                  {
//                                                      string id = match[1].str();
//                                                      double x = stod(match[2].str());
//                                                      double y = stod(match[3].str());
//                                                      double radius = stod(match[4].str());
//
//                                                      newShape = make_unique<shapes::Circle>(id, color, x, y, radius);
//                                                  }},
//
//                    // Triangle: ChangeShape <id> triangle <x1> <y1> <x2> <y2> <x3> <y3>
//                    {regex(R"(ChangeShape\s+([\w\d]+)\s+triangle\s+)" + COORD + S + COORD + S + COORD + S + COORD +
//                           S + COORD + S + COORD),[&newShape, color](const smatch &match)
//                                                  {
//                                                      string id = match[1].str();
//                                                      double x1 = stod(match[2].str());
//                                                      double y1 = stod(match[3].str());
//                                                      double x2 = stod(match[4].str());
//                                                      double y2 = stod(match[5].str());
//                                                      double x3 = stod(match[6].str());
//                                                      double y3 = stod(match[7].str());
//
//                                                      newShape = make_unique<shapes::Triangle>(id, color, x1, y1, x2, y2, x3, y3);
//                                                  }},
//
//                    // Line: ChangeShape <id> line <x1> <y1> <x2> <y2>
//                    {regex(R"(ChangeShape\s+([\w\d]+)\s+line\s+)" + COORD + S + COORD + S + COORD + S + COORD),
//                                                  [&newShape, color](const smatch &match)
//                                                  {
//                                                      string id = match[1].str();
//                                                      double x1 = stod(match[2].str());
//                                                      double y1 = stod(match[3].str());
//                                                      double x2 = stod(match[4].str());
//                                                      double y2 = stod(match[5].str());
//
//                                                      newShape = make_unique<shapes::Line>(id, color, x1, y1, x2, y2);
//                                                  }},
//
//                    // Text: ChangeShape <id> text <x> <y> <size> <text>
//                    {regex(R"(ChangeShape\s+([\w\d]+)\s+text\s+)" + COORD + S + COORD + S + POSNUM + S + R"((.+))"),
//                                                  [&newShape, color](const smatch &match)
//                                                  {
//                                                      string id = match[1].str();
//                                                      double x = stod(match[2].str());
//                                                      double y = stod(match[3].str());
//                                                      double size = stod(match[4].str());
//                                                      string text = match[5].str();
//
//                                                      newShape = make_unique<shapes::Text>(id, color, x, y, size, text);
//                                                  }},
//            };
//
//    for (const auto& command : commandMap)
//    {
//        smatch match;
//        if (regex_search(commandStr, match, command.first))
//        {
//            command.second(match);
//            picture.ChangeShape(id, std::move(newShape));
//            return;
//        }
//    }
//    cout << "error: invalid command!" << endl;
//}

//