//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_TRIANGLE_H
#define OOD_1_TRIANGLE_H

#include <utility>

#include "../Shape.h"

namespace shapes
{
    class Triangle : public Shape
    {
    public:

        Triangle(std::string  id, std::string  color, double x1, double y1, double x2, double y2, double x3, double y3)
                : id(std::move(id)), color(std::move(color)), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {}

        void Draw(ICanvas& canvas) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(x1, y1);
            canvas.LineTo(x2, y2);
            canvas.LineTo(x3, y3);
            canvas.LineTo(x1, y1);
        }

        void Move(double dx, double dy) override
        {
            x1 += dx;
            y1 += dy;
            x2 += dx;
            y2 += dy;
            x3 += dx;
            y3 += dy;
        }

        [[nodiscard]] std::unique_ptr<Shape> Clone(const std::string& newId) const override
        {
            return std::make_unique<Triangle>(newId, color, x1, y1, x2, y2, x3, y3);
        }

        [[nodiscard]] std::string GetId() const override
        {
            return id;
        }

        [[nodiscard]] std::string GetColor() const override
        {
            return color;
        }

        void SetColor(const std::string& col) override
        {
            this->color = col;
        }

        [[nodiscard]] std::string GetType() const override
        {
            return "triangle";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3;
            return oss.str();
        }

    private:
        std::string id;
        std::string color;
        double x1, y1, x2, y2, x3, y3;
    };

}


#endif //OOD_1_TRIANGLE_H
