//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_TEXT_H
#define OOD_1_TEXT_H

#include <utility>

#include "../Shape.h"

namespace shapes
{
    class Text : public Shape
    {
    public:

        Text(std::string  id, std::string  color, double left, double top, double fontSize, std::string  text)
                : id(std::move(id)), color(std::move(color)), left(left), top(top), fontSize(fontSize), text(std::move(text))
        {
            if (fontSize < 0) throw std::invalid_argument("Font size must be non-negative");
        }

        void Draw(ICanvas& canvas) const override
        {
            canvas.SetColor(color);
            canvas.DrawText(left, top, fontSize, text);
        }

        void Move(double dx, double dy) override
        {
            left += dx;
            top += dy;
        }

        [[nodiscard]] std::unique_ptr<Shape> Clone(const std::string& newId) const override
        {
            return std::make_unique<Text>(newId, color, left, top, fontSize, text);
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
            return "text";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << left << " " << top << " " << fontSize << " " << text;
            return oss.str();
        }

    private:
        std::string id;
        std::string color;
        double left, top, fontSize;
        std::string text;
    };

}

#endif //OOD_1_TEXT_H
