//
// Created by Misha on 10.09.2024.
//


#ifndef IDRAWINGSTRATEGY_H
#define IDRAWINGSTRATEGY_H

namespace shapes
{
    class IGeometryType // done переименовать
    {
    public:
        virtual void Draw(ICanvas& canvas, std::string color) const = 0;

        [[nodiscard]] virtual std::string GetType() const = 0;

        //другой интерфейс
        [[nodiscard]] virtual std::string GetParams() const = 0;

        virtual void Move(double dx, double dy) = 0;

        [[nodiscard]] virtual std::unique_ptr<IGeometryType> Clone() const = 0;
        virtual ~IGeometryType() = default;
    };

}

#endif //IDRAWINGSTRATEGY_H
