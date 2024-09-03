//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_SHAPE_H
#define OOD_1_SHAPE_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "Canvas.h"

namespace shapes
{

    class Shape
    {
    public:

        virtual void Draw(shapes::ICanvas& canvas) const = 0;
        virtual void Move(double dx, double dy) = 0;

        [[nodiscard]] virtual std::unique_ptr<Shape> Clone(const std::string& newId) const = 0;

        [[nodiscard]] virtual std::string GetId() const = 0;
        [[nodiscard]] virtual std::string GetColor() const = 0;

        virtual void SetColor(const std::string& color) = 0;

        [[nodiscard]] virtual std::string GetType() const = 0;
        [[nodiscard]] virtual std::string GetParams() const = 0;

        virtual ~Shape() = default;
    };

}


#endif //OOD_1_SHAPE_H
