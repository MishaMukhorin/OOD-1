//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_TRIANGLEDRAWINGSTRATEGY_H
#define OOD_1_TRIANGLEDRAWINGSTRATEGY_H

#include <utility>

#include "Shape.h"

namespace shapes
{
    class TriangleDrawingStrategy : public IDrawingStrategy
    {
    public:

        TriangleDrawingStrategy(double x1, double y1, double x2, double y2, double x3, double y3)
                : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3) {}

        void Draw(ICanvas& canvas, std::string color) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_x1, m_y1);
            canvas.LineTo(m_x2, m_y2);
            canvas.LineTo(m_x3, m_y3);
            canvas.LineTo(m_x1, m_y1);
        }

        void Move(double dx, double dy) override
        {
            m_x1 += dx;
            m_y1 += dy;
            m_x2 += dx;
            m_y2 += dy;
            m_x3 += dx;
            m_y3 += dy;
        }

        [[nodiscard]] std::unique_ptr<IDrawingStrategy> Clone() const override
        {
            return std::make_unique<TriangleDrawingStrategy>(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3);
        }

        [[nodiscard]] std::string GetType() const override
        {
            return "triangle";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2 << " " << m_x3 << " " << m_y3;
            return oss.str();
        }

    private:
        double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3;
    };

}


#endif //OOD_1_TRIANGLEDRAWINGSTRATEGY_H
