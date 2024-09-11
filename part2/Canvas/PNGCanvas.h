#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "../Shapes/Shape.h"


#ifndef PNG_CANVAS_H
#define PNG_CANVAS_H





struct Color {
    uint8_t r, g, b, a;
};

std::string ColorToString(const Color& color);
Color StringToColor(const std::string& colorString);

class PNGCanvas : public shapes::ICanvas
{
public:
    PNGCanvas(int w, int h) : m_width(w), m_height(h), m_currentColor({255, 255, 255, 255}), m_currentX(0), m_currentY(0)
    {
        m_pixels.resize(m_width * m_height * 4, 255); // Белый фон
    }

    ~PNGCanvas() override
    {
        SaveToFile("output.png");
    }

    void SetColor(const std::string& color) override
    {
        m_currentColor = StringToColor(color);
    }

    void MoveTo(double x, double y) override
    {
        m_currentX = x;
        m_currentY = y;
    }

    void LineTo(double x, double y) override
    {
        DrawLine(m_currentX, m_currentY, x, y);
        MoveTo(x, y);
    }

    void DrawEllipse(double cx, double cy, double rx, double ry) override {
        int segments = 100;
        double angleStep = 2 * M_PI / segments;

        double prevX = cx + rx;
        double prevY = cy;

        for (int i = 1; i <= segments; ++i)
        {
            double angle = i * angleStep;
            double newX = cx + rx * cos(angle);
            double newY = cy + ry * sin(angle);
            DrawLine(prevX, prevY, newX, newY);
            prevX = newX;
            prevY = newY;
        }
    }

    void DrawText(double left, double top, double fontSize, const std::string &text) override;

    void SaveToFile(const std::string& filename);

private:
    int m_width, m_height;
    Color m_currentColor{};
    double m_currentX, m_currentY;
    std::vector<uint8_t> m_pixels;

    const int FONT_WIDTH = 8;
    const int FONT_HEIGHT = 8;

    void PutPixel(int x, int y)
    {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height)
        {
            int index = 4 * (y * m_width + x);
            m_pixels[index] = m_currentColor.r;
            m_pixels[index + 1] = m_currentColor.g;
            m_pixels[index + 2] = m_currentColor.b;
            m_pixels[index + 3] = m_currentColor.a;
        }
    }

    void DrawLine(double x1, double y1, double x2, double y2)
    {
        int ix1 = static_cast<int>(std::round(x1));
        int iy1 = static_cast<int>(std::round(y1));
        int ix2 = static_cast<int>(std::round(x2));
        int iy2 = static_cast<int>(std::round(y2));

        int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
        int sx = (ix1 < ix2) ? 1 : -1;
        int sy = (iy1 < iy2) ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            PutPixel(ix1, iy1);
            if (ix1 == ix2 && iy1 == iy2) break;
            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy; ix1 += sx;
            }
            if (e2 < dx) { err += dx; iy1 += sy; }
        }
    }
};

#endif // PNG_CANVAS_H
