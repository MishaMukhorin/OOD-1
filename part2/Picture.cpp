//
// Created by mrLogic on 7/10/2024.
//

#include <algorithm>
#include <regex>
#include "Picture.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Circle.h"
#include "Shapes/Triangle.h"
#include "Shapes/Line.h"
#include "Shapes/Text.h"

using namespace std;

void shapes::Picture::AddShape(const std::string& id, std::unique_ptr<Shape> shape)
{
    if (shapeMap.contains(id))
    {
        throw invalid_argument("Shape with this ID already exists");
    }
    shapeMap[id] = shape.get();
    shapes.push_back(std::move(shape));
}

void shapes::Picture::MoveShape(const string &id, double dx, double dy)
{
    if (!shapeMap.contains(id))
    {
        throw invalid_argument("Shape with this ID does not exist");
    }
    return shapeMap.at(id)->Move(dx, dy);
}

void shapes::Picture::MovePicture(double dx, double dy)
{
    for (auto& shape : shapes)
    {
        shape->Move(dx, dy);
    }
}

void shapes::Picture::DeleteShape(const string &id)
{
    auto it = shapeMap.find(id);
    if (it == shapeMap.end())
    {
        throw invalid_argument("Shape with &newShape ID does not exist");
    }
    shapes.erase(remove_if(shapes.begin(), shapes.end(),
                   [&](const unique_ptr<Shape>& shape)
                   { return shape->GetId() == id; }
                   ), shapes.end());

    shapeMap.erase(it);
}

void shapes::Picture::List() const
{
    int number = 1;
    for (const auto& shape : shapes)
    {
        cout << number++ << " " << shape->GetType() << " " << shape->GetId() << " "
                  << shape->GetColor() << " " << shape->GetParams() << endl;
    }
}

string shapes::Picture::GetShapeColorById(const string& id) const
{
    if (shapeMap.contains(id))
    {
        auto shape = shapeMap.at(id);
        return shape->GetColor();
    }
    return "";
}

string shapes::Picture::GetShapeById(const string& id) const
{
    if (shapeMap.contains(id))
    {
        auto shape = shapeMap.at(id);
        return shape->GetType() + " " + shape->GetColor() + " " + shape->GetParams();
    }
    return "";
}

void shapes::Picture::ChangeColor(const string &id, const string &color)
{
    if (shapeMap.contains(id))
    {
        return shapeMap.at(id)->SetColor(color);
    }
    else
    {
        throw invalid_argument("Shape with &newShape ID does not exist");
    }
}


void shapes::Picture::ChangeShape(const string& id, unique_ptr<Shape> newShape)
{
    if (shapeMap.contains(id))
    {
        for (auto& shapePtr : shapes)
        {
            if (shapePtr->GetId() == id)
            {
                // Replace the shape in the vector with the new shape
                shapePtr = std::move(newShape);

                // Update the shapeMap to point to the new shape in the vector
                shapeMap[id] = shapePtr.get();
                break;
            }
        }
    }
    else
    {
        cout << "error: Shape with given ID not found" << endl;
    }
}




void shapes::Picture::DrawShape(const string &id, shapes::ICanvas &canvas) const
{
    if (shapeMap.contains(id))
    {
        shapeMap.at(id)->Draw(canvas);
    }
    else
    {
        throw invalid_argument("Shape with &newShape ID does not exist");
    }
}

void shapes::Picture::DrawPicture(shapes::ICanvas &canvas) const
{
    for (const auto& shape : shapes)
    {
        shape->Draw(canvas);
    }
}

void shapes::Picture::CloneShape(const string& id, const string& newId)
{
    auto clonedShape = CloneShapeInternal(id, newId);
    AddShape(newId, move(clonedShape));
}

unique_ptr<shapes::Shape> shapes::Picture::CloneShapeInternal(const string& id, const string& newId) const
{
    if (shapeMap.contains(id))
    {
        return shapeMap.at(id)->Clone(newId);
    }
    else
    {
        throw invalid_argument("Shape with given ID not found");
    }

}



