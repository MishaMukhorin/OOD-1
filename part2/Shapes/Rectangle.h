//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_RECTANGLE_H
#define OOD_1_RECTANGLE_H

#include "../Shape.h"

namespace shapes
{
    class Rectangle : public Shape
    {
    public:

        Rectangle(std::string  id, std::string  color, double left, double top, double width, double height)
                : id(std::move(id)), color(std::move(color)), left(left), top(top), width(width), height(height)
        {
            if (width < 0 || height < 0)
                throw std::invalid_argument("Width and height must be non-negative");
        }

        void Draw(ICanvas& canvas) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(left, top);
            canvas.LineTo(left + width, top);
            canvas.LineTo(left + width, top + height);
            canvas.LineTo(left, top + height);
            canvas.LineTo(left, top);
        }

        void Move(double dx, double dy) override
        {
            left += dx;
            top += dy;
        }

        [[nodiscard]] std::unique_ptr<Shape> Clone(const std::string& newId) const override
        {
            return std::make_unique<Rectangle>(newId, color, left, top, width, height);
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
            return "rectangle";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << left << " " << top << " " << width << " " << height;
            return oss.str();
        }

    private:
        std::string id;
        std::string color;
        double left, top, width, height;
    };

}
#endif //OOD_1_RECTANGLE_H
