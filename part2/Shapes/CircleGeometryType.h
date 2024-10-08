//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_CIRCLEGEOMETRYTYPE_H
#define OOD_1_CIRCLEGEOMETRYTYPE_H

#include "Shape.h"
namespace shapes
{
    class CircleGeometryType : public IGeometryType
    {
    public:

        CircleGeometryType(double x, double y, double r)
                : m_x(x), m_y(y), m_r(r)
        {
            if (r < 0)
            {
                throw std::invalid_argument("Radius must be non-negative");
            }
        }

        CircleGeometryType(const CircleGeometryType &circle):
        m_x(circle.m_x), m_y(circle.m_y), m_r(circle.m_r) {}

        void Draw(ICanvas& canvas, std::string color) const override
        {
            canvas.SetColor(color);
            canvas.DrawEllipse(m_x, m_y, m_r, m_r);
        }

        void Move(double dx, double dy) override
        {
            m_x += dx;
            m_y += dy;
        }

        [[nodiscard]] std::unique_ptr<IGeometryType> Clone() const override
        {
            return std::make_unique<CircleGeometryType>(*this);
        }

        [[nodiscard]] std::string GetType() const override
        {
            return "circle";
        }

        [[nodiscard]] std::string GetShapeParamsString() const override
        {
            std::ostringstream oss;
            oss << m_x << " " << m_y << " " << m_r;
            return oss.str();
        }

    private:
        double m_x, m_y, m_r;
    };

}

#endif //OOD_1_CIRCLEGEOMETRYTYPE_H
