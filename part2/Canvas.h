//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_Canvas_H
#define OOD_1_Canvas_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace shapes
{

    class ICanvas
    {
    public:

        virtual void SetColor(const std::string& color) = 0;

        virtual void MoveTo(double x, double y) = 0;

        virtual void LineTo(double x, double y) = 0;

        virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
        virtual void DrawText(double left, double top, double fontSize, const std::string& text) = 0;

        virtual ~ICanvas() = default;
    };

}


#endif //OOD_1_Canvas_H
