//
// Created by Misha on 11.09.2024.
//

#include <gtest/gtest.h>
#include "../Picture/Picture.h"
#include "../Shapes/CircleGeometryType.h"
#include "MockCanvas.h"

TEST(PictureTest, TestAddShape) {
    // Arrange
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));

    // Act
    picture.AddShape("circle1", std::move(circle));

    // Assert (Check if the shape was added)
    EXPECT_EQ(picture.GetShapeById("circle1"), "circle #ff00ff 100 110 15");
}

TEST(PictureTest, TestMovePicture) {
    // Arrange
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));
    picture.AddShape("circle1", std::move(circle));

    // Act
    picture.MovePicture(10, 20);

    // Assert (Check if all shapes were moved)
    EXPECT_EQ(picture.GetShapeById("circle1"), "circle #ff00ff 110 130 15");
}

TEST(PictureTest, TestCloneShape) {
    // Arrange
    shapes::Picture picture;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));
    picture.AddShape("circle1", std::move(circle));

    // Act
    picture.CloneShape("circle1", "circle2");

    // Assert (Check if the shape was cloned with a new ID)
    EXPECT_EQ(picture.GetShapeById("circle2"), "circle #ff00ff 100 110 15");
}

TEST(PictureTest, TestDrawPicture) {
    // Arrange
    shapes::Picture picture;
    MockCanvas mockCanvas;
    auto circle = std::make_unique<shapes::Shape>("circle1", "#ff00ff",
                                                  std::make_unique<shapes::CircleGeometryType>(100.0, 110.0, 15.0));
    picture.AddShape("circle1", std::move(circle));

    // Expect the color to be set and an ellipse to be drawn
    EXPECT_CALL(mockCanvas, SetColor("#ff00ff"));
    EXPECT_CALL(mockCanvas, DrawEllipse(100.0, 110.0, 15.0, 15.0));

    // Act
    picture.DrawPicture(mockCanvas);
}
