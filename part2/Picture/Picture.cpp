//
// Created by mrLogic on 7/10/2024.
//

#include <algorithm>
#include "Picture.h"
#include "../Shapes/TriangleDrawingStrategy.h"

using namespace std;

void shapes::Picture::AddShape(const std::string& id, std::unique_ptr<Shape> shape)
{
    if (m_shapes.contains(id))
    {
        throw invalid_argument("Shape with this ID already exists");
    }
    m_shapes.emplace(id, std::move(shape));
}

void shapes::Picture::MoveShape(const string &id, double dx, double dy)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with this ID does not exist");
    }
    return m_shapes.at(id)->Move(dx, dy);
}

void shapes::Picture::MovePicture(double dx, double dy)
{
    for (auto& shape : m_shapes)
    {
        shape.second->Move(dx, dy);
    }
}

void shapes::Picture::DeleteShape(const string &id)
{
    auto it = m_shapes.find(id);
    if (it == m_shapes.end())
    {
        throw invalid_argument("Shape with &newShape ID does not exist");
    }
    m_shapes.erase(it);
}

void shapes::Picture::List() const
{
    int number = 1;
    for (const auto& shape : m_shapes)
    {
        cout << number++ << " " << shape.second->GetType() << " " << shape.second->GetId() << " "
                  << shape.second->GetColor() << " " << shape.second->GetParams() << endl;
    }
}

string shapes::Picture::GetShapeColorById(const string& id) const
{
    if (!m_shapes.contains(id))
    {
        return "";
    }
    auto shape = m_shapes.at(id).get();
    return shape->GetColor();
}

string shapes::Picture::GetShapeById(const string& id) const
{
    if (!m_shapes.contains(id))
    {
        return "";
    }

    auto shape = m_shapes.at(id).get();
    return shape->GetType() + " " + shape->GetColor() + " " + shape->GetParams();
}

void shapes::Picture::ChangeColor(const string &id, const string &color)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with &newShape ID does not exist");
    }

    return m_shapes.at(id)->SetColor(color);
}


void shapes::Picture::ChangeShape(const string& id, std::unique_ptr<IDrawingStrategy> newShapeDrawingStrategy)
{
    if (!m_shapes.contains(id))
    {
        cout << "error: Shape with given ID not found" << endl;
    }

    m_shapes.at(id)->SetNewDrawingStrategy(std::move(newShapeDrawingStrategy));
}

// использовать стратегию для рисования фигур и не будет наследников шейп


void shapes::Picture::DrawShape(const string &id, shapes::ICanvas &canvas) const
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with &newShape ID does not exist");
    }
    m_shapes.at(id)->Draw(canvas);
}

void shapes::Picture::DrawPicture(shapes::ICanvas &canvas) const
{
    for (const auto& shape : m_shapes)
    {
        shape.second->Draw(canvas);
    }
}

void shapes::Picture::CloneShape(const string& id, const string& newId)
{
    auto clonedShape = CloneShapeInternal(id, newId);
    AddShape(newId, std::move(clonedShape));
}

unique_ptr<shapes::Shape> shapes::Picture::CloneShapeInternal(const string& id, const string& newId) const
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID not found");
    }

    return m_shapes.at(id)->Clone(newId);

}



