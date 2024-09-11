#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shapes/CircleGeometryType.h"
#include "../Shapes/RectangleGeometryType.h"
#include "../Shapes/TriangleGeometryType.h"
#include "../Shapes/LineGeometryType.h"
#include "../Shapes/TextGeometryType.h"
#include "../Picture/Picture.h"
#include "MockCanvas.h"



// Test Circle
TEST(CircleTest, TestCircleDraw) {
    MockCanvas mockCanvas;
    shapes::CircleGeometryType strategy(100.0, 110.0, 15.0);

    EXPECT_CALL(mockCanvas, SetColor("#ff00ff"));
    EXPECT_CALL(mockCanvas, DrawEllipse(100.0, 110.0, 15.0, 15.0));

    strategy.Draw(mockCanvas, "#ff00ff");
}

TEST(CircleTest, TestMoveCircle) {
    shapes::CircleGeometryType strategy(100.0, 110.0, 15.0);
    strategy.Move(10, 20);
    EXPECT_EQ(strategy.GetShapeParamsString(), "110 130 15");
}

// Test Rectangle
TEST(RectangleTest, TestRectangleDraw) {
    MockCanvas mockCanvas;
    shapes::RectangleGeometryType strategy(10.0, 20.0, 30.0, 40.0);

    EXPECT_CALL(mockCanvas, SetColor("#123456"));
    EXPECT_CALL(mockCanvas, MoveTo(10.0, 20.0));
    EXPECT_CALL(mockCanvas, LineTo(40.0, 20.0));
    EXPECT_CALL(mockCanvas, LineTo(40.0, 60.0));
    EXPECT_CALL(mockCanvas, LineTo(10.0, 60.0));
    EXPECT_CALL(mockCanvas, LineTo(10.0, 20.0));

    strategy.Draw(mockCanvas, "#123456");
}

TEST(RectangleTest, TestMoveRectangle) {
    shapes::RectangleGeometryType strategy(10.0, 20.0, 30.0, 40.0);
    strategy.Move(5, 10);
    EXPECT_EQ(strategy.GetShapeParamsString(), "15 30 30 40");
}

// Test Triangle
TEST(TriangleTest, TestTriangleDraw) {
    MockCanvas mockCanvas;
    shapes::TriangleGeometryType strategy(0.0, 0.0, 10.0, 0.0, 5.0, 10.0);

    EXPECT_CALL(mockCanvas, SetColor("#00ff00"));
    EXPECT_CALL(mockCanvas, MoveTo(0.0, 0.0));
    EXPECT_CALL(mockCanvas, LineTo(10.0, 0.0));
    EXPECT_CALL(mockCanvas, LineTo(5.0, 10.0));
    EXPECT_CALL(mockCanvas, LineTo(0.0, 0.0));

    strategy.Draw(mockCanvas, "#00ff00");
}

TEST(TriangleTest, TestMoveTriangle) {
    shapes::TriangleGeometryType strategy(0.0, 0.0, 10.0, 0.0, 5.0, 10.0);
    strategy.Move(1.0, 2.0);
    EXPECT_EQ(strategy.GetShapeParamsString(), "1 2 11 2 6 12");
}

// Test Line
TEST(LineTest, TestLineDraw) {
    MockCanvas mockCanvas;
    shapes::LineGeometryType strategy(0.0, 0.0, 20.0, 20.0);

    EXPECT_CALL(mockCanvas, SetColor("#ff0000"));
    EXPECT_CALL(mockCanvas, MoveTo(0.0, 0.0));
    EXPECT_CALL(mockCanvas, LineTo(20.0, 20.0));

    strategy.Draw(mockCanvas, "#ff0000");
}

TEST(LineTest, TestMoveLine) {
    shapes::LineGeometryType strategy(0.0, 0.0, 20.0, 20.0);
    strategy.Move(5.0, 5.0);
    EXPECT_EQ(strategy.GetShapeParamsString(), "5 5 25 25");
}

// Test Text
TEST(TextTest, TestTextDraw) {
    MockCanvas mockCanvas;
    shapes::TextGeometryType strategy(100.0, 100.0, 12.0, "Hello World");

    EXPECT_CALL(mockCanvas, SetColor("#ffaa88"));
    EXPECT_CALL(mockCanvas, DrawText(100.0, 100.0, 12.0, "Hello World"));

    strategy.Draw(mockCanvas, "#ffaa88");
}

TEST(TextTest, TestMoveText) {
    shapes::TextGeometryType strategy(100.0, 100.0, 12.0, "Hello World");
    strategy.Move(10.0, 20.0);
    EXPECT_EQ(strategy.GetShapeParamsString(), "110 120 12 Hello World");
}


GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
