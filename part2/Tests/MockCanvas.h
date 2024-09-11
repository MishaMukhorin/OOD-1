//
// Created by Misha on 11.09.2024.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Canvas.h"

class MockCanvas : public shapes::ICanvas {
public:
    MOCK_METHOD(void, SetColor, (const std::string& color), (override));
    MOCK_METHOD(void, MoveTo, (double x, double y), (override));
    MOCK_METHOD(void, LineTo, (double x, double y), (override));
    MOCK_METHOD(void, DrawEllipse, (double cx, double cy, double rx, double ry), (override));
    MOCK_METHOD(void, DrawText, (double left, double top, double fontSize, const std::string& text), (override));
};