//
// Created by Misha on 11.09.2024.
//
#include <gtest/gtest.h>
#include "../Shapes/CircleGeometryType.h"
#include "MockCanvas.h"

TEST(ShapeTest, TestCircleDraw) {
    // Arrange
    MockCanvas mockCanvas;
    shapes::CircleGeometryType strategy(100.0, 110.0, 15.0);
    shapes::Shape circle("circle1", "#ff00ff", std::make_unique<shapes::CircleGeometryType>(strategy));

    // Expect the color to be set and an ellipse to be drawn
    EXPECT_CALL(mockCanvas, SetColor("#ff00ff"));
    EXPECT_CALL(mockCanvas, DrawEllipse(100.0, 110.0, 15.0, 15.0));

    // Act
    circle.Draw(mockCanvas);
}

TEST(ShapeTest, TestMoveCircle) {
    // Arrange
    shapes::CircleGeometryType strategy(100.0, 110.0, 15.0);
    shapes::Shape circle("circle1", "#ff00ff", std::make_unique<shapes::CircleGeometryType>(strategy));

    // Act
    circle.Move(10, 20);

    // Assert (Check if position has been updated)
    EXPECT_EQ(circle.GetShapeParamsString(), "110 130 15");
}


GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
