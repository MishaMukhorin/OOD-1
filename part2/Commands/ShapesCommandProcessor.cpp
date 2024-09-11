//
// Created by Misha on 29.03.2024.
//
#include "ShapesCommandProcessor.h"

using namespace std;

using ShapeFunction = function<void(string, string, shapes::IGeometryType*)>;

void ShapeCommandExec(const ShapeFunction& command, const string& id, const string& color, const string& commandStr, shapes::Picture &picture)
{
    const string POSNUM = R"((\d+(?:\.\d+)?))";
    const string COORD = R"((-?\d+(?:\.\d+)?))";
    const string S = R"(\s+)";
    shapes::IGeometryType* newGeometryType;

    vector<pair<regex, function<void(const smatch &match)>>> commandMap
            {
                    // Rectangle: command <id> rectangle <x> <y> <width> <height>
                    {regex(R"(rectangle\s+)" + COORD + S + COORD + S + POSNUM + S + POSNUM),
                            [&newGeometryType](const smatch &match)
                            {
                                double x = stod(match[1].str());
                                double y = stod(match[2].str());
                                double width = stod(match[3].str());
                                double height = stod(match[4].str());

                                newGeometryType = new shapes::RectangleGeometryType(x, y, width, height);
                            }},

                    // Circle: command <id> circle <x> <y> <radius>
                    {regex(R"(circle\s+)" + COORD + S + COORD + S + POSNUM),
                            [&newGeometryType](const smatch &match)
                            {
                                double x = stod(match[1].str());
                                double y = stod(match[2].str());
                                double radius = stod(match[3].str());

                                newGeometryType = new shapes::CircleGeometryType(x, y, radius);
                            }},

                    // Triangle: command <id> triangle <x1> <y1> <x2> <y2> <x3> <y3>
                    {regex(R"(triangle\s+)" + COORD + S + COORD + S + COORD + S + COORD +
                            S + COORD + S + COORD),[&newGeometryType](const smatch &match)
                            {
                                double x1 = stod(match[1].str());
                                double y1 = stod(match[2].str());
                                double x2 = stod(match[3].str());
                                double y2 = stod(match[4].str());
                                double x3 = stod(match[5].str());
                                double y3 = stod(match[6].str());

                                newGeometryType = new shapes::TriangleGeometryType(x1, y1, x2, y2, x3, y3);
                            }},

                    // Line: command <id> line <x1> <y1> <x2> <y2>
                    {regex(R"(line\s+)" + COORD + S + COORD + S + COORD + S + COORD),
                            [&newGeometryType](const smatch &match)
                            {
                                double x1 = stod(match[1].str());
                                double y1 = stod(match[2].str());
                                double x2 = stod(match[3].str());
                                double y2 = stod(match[4].str());

                                newGeometryType = new shapes::LineGeometryType(x1, y1, x2, y2);
                            }},

                    // Text: command <id> text <x> <y> <size> <text>
                    {regex(R"(text\s+)" + COORD + S + COORD + S + POSNUM + S + R"((.+))"),
                            [&newGeometryType](const smatch &match)
                            {
                                double x = stod(match[1].str());
                                double y = stod(match[2].str());
                                double size = stod(match[3].str());
                                string text = match[4].str();
                                newGeometryType = new shapes::TextGeometryType(x, y, size, text);
                            }},
            };

    for (const auto& createShape : commandMap)
    {
        smatch match;
        if (regex_search(commandStr, match, createShape.first))
        {
            createShape.second(match);
            command(id, color, (newGeometryType));
            delete newGeometryType;
            return;
        }
    }
    cout << "error: invalid Shape command!" << endl;
}


void LineProcessor(const std::string &line, shapes::Picture &picture)
{
    const string COORD = R"((-?\d+(?:\.\d+)?))";
    const string S = R"(\s+)";
    const string COLOR = R"((#[0-9A-Fa-f]{6}))";
//
//AddShape sh1 #ff00ff circle 100 110 15
//AddShape circ #febb38 circle 100 200 25
//AddShape sh2 #123456 rectangle 10 20 30 40
//AddShape tr1 #00fefa triangle 0 0 10 0 0 10
//AddShape ln1 #000000 line 20 0 0 20
//AddShape txt1 #ffaa88 text 100 100 12 HELLO WORLD

    vector<pair<regex, function<void(const smatch &match)>>> commandMap
            {
                    // AddShape <id> <parameters>
                    {regex(R"((AddShape)\s+([\w\d]+)\s+)" + COLOR + R"((.+))"),
                            [&picture](const smatch &match)
                            {
                                string commandType = match[1].str() + R"(\s+[\w\d]+\s+#[0-9A-Fa-f]{6})";
                                string id = match[2].str();
                                string color = match[3].str();
                                string commandStr = match[4].str();
                                ShapeFunction addShapeFunc;
                                addShapeFunc = [&picture](const std::string& id, const std::string& color, shapes::IGeometryType* newGeometryType) {
                                    std::unique_ptr<shapes::Shape> newShape = make_unique<shapes::Shape>(
                                            id,
                                            color,
                                            newGeometryType->Clone());
                                    picture.AddShape(id, std::move(newShape));
                                };

                                ShapeCommandExec(addShapeFunc, id, color, commandStr, picture);
                            }},
                    // ChangeShape <id> <parameters>
                    {regex(R"((ChangeShape)\s+([\w\d]+)(.+))"),
                            [&picture](const smatch &match)
                            {
                                string commandType = match[1].str() + R"(\s+[\w\d]+\s+)";
                                string id = match[2].str();
                                string commandStr = match[3].str();
                                string color = picture.GetShapeColorById(id);
                                ShapeFunction changeShapeFunc;

                                changeShapeFunc = [&picture](const std::string& id, const std::string& color, shapes::IGeometryType* newGeometryType){
                                    picture.ChangeShape(id, newGeometryType->Clone());
                                };

                                ShapeCommandExec(changeShapeFunc, id, color, commandStr, picture);
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
            try
            {
                cmd.second(match);
                return;
            }
            catch (std::invalid_argument &e)
            {
                cout << "error: " << e.what() << endl;
                return;
            }
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