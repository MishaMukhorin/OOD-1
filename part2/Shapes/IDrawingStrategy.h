//
// Created by Misha on 10.09.2024.
//


#ifndef IDRAWINGSTRATEGY_H
#define IDRAWINGSTRATEGY_H

namespace shapes
{
    class IDrawingStrategy
    {
    public:
        virtual void Draw(ICanvas& canvas, std::string color) const = 0;

        [[nodiscard]] virtual std::string GetType() const = 0;
        [[nodiscard]] virtual std::string GetParams() const = 0;

        virtual void Move(double dx, double dy) = 0;

        [[nodiscard]] virtual std::unique_ptr<IDrawingStrategy> Clone() const = 0;
        virtual ~IDrawingStrategy() = default;
    };

}

#endif //IDRAWINGSTRATEGY_H
