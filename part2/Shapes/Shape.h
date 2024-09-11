//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_SHAPE_H
#define OOD_1_SHAPE_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "../Canvas.h"
#include "IDrawingStrategy.h"

namespace shapes
{

    class Shape
    {
    public:

        Shape(std::string id, std::string color, std::unique_ptr<IDrawingStrategy> drawingStrategy):
                m_id(std::move(id)), m_color(std::move(color)), m_drawingStrategy(std::move(drawingStrategy))
        {}

        void Draw(shapes::ICanvas& canvas) const
        {
            m_drawingStrategy->Draw(canvas, m_color);
        }
        void Move(double dx, double dy)
        {
            m_drawingStrategy->Move(dx, dy);
        }

        [[nodiscard]] virtual std::unique_ptr<Shape> Clone(const std::string& newId) const
        {
            Shape newShape(newId, m_color, m_drawingStrategy->Clone());

        }

        [[nodiscard]] std::string GetId() const
        {
            return m_id;
        }

        [[nodiscard]] std::string GetColor() const
        {
            return m_color;
        }

        void SetColor(const std::string& col)
        {
            this->m_color = col;
        }

        [[nodiscard]] std::string GetType() const
        {
            return m_drawingStrategy->GetType();
        }

        [[nodiscard]] std::string GetParams() const
        {
            return m_drawingStrategy->GetParams();
        }

        void SetNewDrawingStrategy(std::unique_ptr<IDrawingStrategy> newDrawingStrategy)
        {
            m_drawingStrategy.reset(newDrawingStrategy.get());
        }

        virtual ~Shape() = default;
    private:
        std::string m_id;
        std::string m_color;

        std::unique_ptr<IDrawingStrategy> m_drawingStrategy;

    };

}


#endif //OOD_1_SHAPE_H
