//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_LINE_H
#define OOD_1_LINE_H

#include <utility>

#include "../Shape.h"

namespace shapes
{
    class Line : public Shape
    {
    public:

        Line(std::string  id, std::string  color, double x1, double y1, double x2, double y2)
                : id(std::move(id)), color(std::move(color)), x1(x1), y1(y1), x2(x2), y2(y2) {}

        void Draw(ICanvas& canvas) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(x1, y1);
            canvas.LineTo(x2, y2);
        }

        void Move(double dx, double dy) override
        {
            x1 += dx;
            y1 += dy;
            x2 += dx;
            y2 += dy;
        }

        [[nodiscard]] std::unique_ptr<Shape> Clone(const std::string& newId) const override
        {
            return std::make_unique<Line>(newId, color, x1, y1, x2, y2);
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
            return "line";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << x1 << " " << y1 << " " << x2 << " " << y2;
            return oss.str();
        }

    private:
        std::string id;
        std::string color;
        double x1, y1, x2, y2;
    };

}

#endif //OOD_1_LINE_H
