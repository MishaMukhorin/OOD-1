#include <gtest/gtest.h>
#include "../Picture/Picture.h"
#include "../Shapes/CircleGeometryType.h"
#include "../Shapes/REctangleGeometryType.h"
#include "MockCanvas.h"

// Test AddShape Command
TEST(PictureTest, TestAddShape) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    picture.AddShape("circle1", std::move(circle));

    EXPECT_EQ(picture.GetShapeById("circle1"), "circle #ff00ff 100 110 15");
}

// Test ChangeShape Command
TEST(PictureTest, TestChangeShape) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    picture.AddShape("circle1", std::move(circle));

    auto rectangleStrategy = std::make_unique<shapes::RectangleGeometryType>(10.0, 20.0, 30.0, 40.0);
    picture.ChangeShape("circle1", std::move(rectangleStrategy));

    EXPECT_EQ(picture.GetShapeById("circle1"), "rectangle #ff00ff 10 20 30 40");
}

// Test MoveShape Command
TEST(PictureTest, TestMoveShape) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    picture.AddShape("circle1", std::move(circle));

    picture.MoveShape("circle1", 10.0, 20.0);

    EXPECT_EQ(picture.GetShapeById("circle1"), "circle #ff00ff 110 130 15");
}

// Test MovePicture Command
TEST(PictureTest, TestMovePicture) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    auto rectangle = std::make_unique<shapes::Shape>("rect1", "#123456",
                                                     std::make_unique<shapes::RectangleGeometryType>(10.0, 20.0, 30.0, 40.0));

    picture.AddShape("circle1", std::move(circle));
    picture.AddShape("rect1", std::move(rectangle));

    picture.MovePicture(10.0, 20.0);

    EXPECT_EQ(picture.GetShapeById("circle1"), "circle #ff00ff 110 130 15");
    EXPECT_EQ(picture.GetShapeById("rect1"), "rectangle #123456 20 40 30 40");
}

// Test DeleteShape Command
TEST(PictureTest, TestDeleteShape) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    picture.AddShape("circle1", std::move(circle));
    picture.DeleteShape("circle1");

    EXPECT_EQ(picture.GetShapeById("circle1"), "");
}

// Test ChangeColor Command
TEST(PictureTest, TestChangeColor) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    picture.AddShape("circle1", std::move(circle));

    picture.ChangeColor("circle1", "#00ff00");

    EXPECT_EQ(picture.GetShapeById("circle1"), "circle #00ff00 100 110 15");
}

// Test CloneShape Command
TEST(PictureTest, TestCloneShape) {
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    picture.AddShape("circle1", std::move(circle));
    picture.CloneShape("circle1", "circle2");

    EXPECT_EQ(picture.GetShapeById("circle2"), "circle #ff00ff 100 110 15");
}