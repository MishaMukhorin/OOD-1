//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_CIRCLE_H
#define OOD_1_CIRCLE_H

#include "../Shape.h"
namespace shapes
{
    class Circle : public Shape
    {
    public:

        Circle(std::string  id, std::string  color, double x, double y, double r)
                : id(std::move(id)), color(std::move(color)), x(x), y(y), r(r)
        {
            if (r < 0) throw std::invalid_argument("Radius must be non-negative");
        }

        void Draw(ICanvas& canvas) const override
        {
            canvas.SetColor(color);
            canvas.DrawEllipse(x, y, r, r);
        }

        void Move(double dx, double dy) override
        {
            x += dx;
            y += dy;
        }

        [[nodiscard]] std::unique_ptr<Shape> Clone(const std::string& newId) const override
        {
            return std::make_unique<Circle>(newId, color, x, y, r);
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
            return "circle";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << x << " " << y << " " << r;
            return oss.str();
        }

    private:
        std::string id;
        std::string color;
        double x, y, r;

    };

}

#endif //OOD_1_CIRCLE_H
