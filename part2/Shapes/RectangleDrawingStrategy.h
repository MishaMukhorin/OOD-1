//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_RECTANGLEDRAWINGSTRATEGY_H
#define OOD_1_RECTANGLEDRAWINGSTRATEGY_H

#include "Shape.h"

namespace shapes
{
    class RectangleDrawingStrategy : public IDrawingStrategy
    {
    public:

        RectangleDrawingStrategy(double left, double top, double width, double height)
                : m_left(left), m_top(top), m_width(width), m_height(height)
        {
            if (width < 0 || height < 0)
            {
                throw std::invalid_argument("Width and height must be non-negative");
            }
        }

        void Draw(ICanvas& canvas, std::string color) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_left, m_top);
            canvas.LineTo(m_left + m_width, m_top);
            canvas.LineTo(m_left + m_width, m_top + m_height);
            canvas.LineTo(m_left, m_top + m_height);
            canvas.LineTo(m_left, m_top);
        }

        void Move(double dx, double dy) override
        {
            m_left += dx;
            m_top += dy;
        }

        [[nodiscard]] std::unique_ptr<IDrawingStrategy> Clone() const override
        {
            return std::make_unique<RectangleDrawingStrategy>(m_left, m_top, m_width, m_height);
        }

        [[nodiscard]] std::string GetType() const override
        {
            return "rectangle";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << m_left << " " << m_top << " " << m_width << " " << m_height;
            return oss.str();
        }

    private:
        double m_left, m_top, m_width, m_height;
    };

}
#endif //OOD_1_RECTANGLEDRAWINGSTRATEGY_H
