//
// Created by mrLogic on 7/10/2024.
//

#ifndef OOD_1_PICTURE_H
#define OOD_1_PICTURE_H

#include "Shape.h"
#include <vector>
#include <map>

namespace shapes
{
    class Picture
    {
    public:

        void AddShape(const std::string& id, std::unique_ptr<Shape> shape);
        void MoveShape(const std::string& id, double dx, double dy);
        void MovePicture(double dx, double dy);
        void DeleteShape(const std::string& id);

        [[nodiscard]] std::string GetShapeColorById(const std::string& id) const;
        [[nodiscard]] std::string GetShapeById(const std::string& id) const;
        void List() const;

        void ChangeColor(const std::string& id, const std::string& color);
        void ChangeShape(const std::string& id, std::unique_ptr<Shape> newShape);


        void DrawShape(const std::string& id, ICanvas& canvas) const;
        void DrawPicture(ICanvas& canvas) const;

        void CloneShape(const std::string& id, const std::string& newId);

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
        std::map<std::string, Shape*> shapeMap;

        [[nodiscard]] std::unique_ptr<Shape> CloneShapeInternal(const std::string& id, const std::string& newId) const;
    };

}


#endif //OOD_1_PICTURE_H
