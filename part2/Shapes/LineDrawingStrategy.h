//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_LINEDRAWINGSTRATEGY_H
#define OOD_1_LINEDRAWINGSTRATEGY_H

#include <utility>

#include "Shape.h"

namespace shapes
{
    class LineDrawingStrategy : public IDrawingStrategy
    {
    public:

        LineDrawingStrategy(double x1, double y1, double x2, double y2)
                : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}

        void Draw(ICanvas& canvas, std::string color) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_x1, m_y1);
            canvas.LineTo(m_x2, m_y2);
        }

        void Move(double dx, double dy) override
        {
            m_x1 += dx;
            m_y1 += dy;
            m_x2 += dx;
            m_y2 += dy;
        }

        [[nodiscard]] std::unique_ptr<IDrawingStrategy> Clone() const override
        {
            return std::make_unique<LineDrawingStrategy>(m_x1, m_y1, m_x2, m_y2);
        }

        [[nodiscard]] std::string GetType() const override
        {
            return "line";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2;
            return oss.str();
        }

    private:
        double m_x1, m_y1, m_x2, m_y2;
    };

}

#endif //OOD_1_LINEDRAWINGSTRATEGY_H
