#include <iostream>

#include "Commands/ShapesCommandProcessor.h"

using namespace shapes;

int main()
{
    CommandProcessor(std::cin);
    return 0;
}


//void ParseCommand(const std::string& line, Picture& picture)
//{
//    std::istringstream iss(line);
//    std::string command;
//    iss >> command;
//
//    if (command == "AddShape")
//    {
//        std::string id, color, type;
//        iss >> id >> color >> type;
//
//        std::vector<double> params;
//        double param;
//        while (iss >> param)
//        {
//            params.push_back(param);
//        }
//
//        std::unique_ptr<Shape> shape;
//        if (type == "circle")
//        {
//            shape = std::make_unique<Circle>(id, color, params[0], params[1], params[2]);
//        }
//        else if (type == "rectangle")
//        {
//            shape = std::make_unique<Rectangle>(id, color, params[0], params[1], params[2], params[3]);
//        }
//        else if (type == "triangle")
//        {
//            shape = std::make_unique<Triangle>(id, color, params[0], params[1], params[2], params[3], params[4], params[5]);
//        } else if (type == "line")
//        {
//            shape = std::make_unique<Line>(id, color, params[0], params[1], params[2], params[3]);
//        } else if (type == "text")
//        {
//            std::ostringstream text;
//            for (size_t i = 3; i < params.size(); ++i)
//            {
//                text << params[i] << " ";
//            }
//            shape = std::make_unique<Text>(id, color, params[0], params[1], params[2], text.str());
//        }
//
//        picture.AddShape(std::move(shape));
//    }
//    else if (command == "MoveShape")
//    {
//        std::string id;
//        double dx, dy;
//        iss >> id >> dx >> dy;
//        picture.MoveShape(id, dx, dy);
//    }
//    else if (command == "MovePicture")
//    {
//        double dx, dy;
//        iss >> dx >> dy;
//        picture.MovePicture(dx, dy);
//    }
//    else if (command == "DeleteShape")
//    {
//        std::string id;
//        iss >> id;
//        picture.DeleteShape(id);
//    }
//    else if (command == "List") {
//        picture.List();
//    }
//    else if (command == "ChangeColor")
//    {
//        std::string id, color;
//        iss >> id >> color;
//        picture.ChangeColor(id, color);
//    }
//    else if (command == "ChangeShape")
//    {
//        std::string id, type;
//        iss >> id >> type;
//        std::vector<double> params;
//        double param;
//        while (iss >> param)
//        {
//            params.push_back(param);
//        }
//        picture.ChangeShape(id, type, params);
//    }
//    else if (command == "DrawShape")
//    {
//        std::string id;
//        iss >> id;
//        PNGCanvas canvas(800, 600);
//        picture.DrawShape(id, canvas);
//    }
//    else if (command == "DrawPicture")
//    {
//        PNGCanvas canvas(800, 600);
//        picture.DrawPicture(canvas);
//        std::cout << "draw " << std::endl;
//    }
//    else if (command == "CloneShape")
//    {
//        std::string id, newId;
//        iss >> id >> newId;
//        picture.CloneShape(id, newId);
//    }
//}
