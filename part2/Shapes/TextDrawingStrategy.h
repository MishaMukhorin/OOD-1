//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_TEXTDRAWINGSTRATEGY_H
#define OOD_1_TEXTDRAWINGSTRATEGY_H

#include <utility>

#include "Shape.h"

namespace shapes
{
    class TextDrawingStrategy : public IDrawingStrategy
    {
    public:

        TextDrawingStrategy(double left, double top, double fontSize, std::string  text)
                : m_left(left), m_top(top), m_fontSize(fontSize), m_text(std::move(text))
        {
            if (fontSize < 0)
            {
                throw std::invalid_argument("Font size must be non-negative");
            }
        }

        void Draw(ICanvas& canvas, std::string color) const override
        {
            canvas.SetColor(color);
            canvas.DrawText(m_left, m_top, m_fontSize, m_text);
        }

        void Move(double dx, double dy) override
        {
            m_left += dx;
            m_top += dy;
        }

        [[nodiscard]] std::unique_ptr<IDrawingStrategy> Clone() const override
        {
            return std::make_unique<TextDrawingStrategy>(m_left, m_top, m_fontSize, m_text);
        }

        [[nodiscard]] std::string GetType() const override
        {
            return "text";
        }

        [[nodiscard]] std::string GetParams() const override
        {
            std::ostringstream oss;
            oss << m_left << " " << m_top << " " << m_fontSize << " " << m_text;
            return oss.str();
        }

    private:
        double m_left, m_top, m_fontSize;
        std::string m_text;
    };

}

#endif //OOD_1_TEXTDRAWINGSTRATEGY_H
