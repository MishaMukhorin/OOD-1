//
// Created by Misha on 06.04.2024.
//

#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include "../Shapes/TriangleDrawingStrategy.h"
#include "../Shapes/CircleDrawingStrategy.h"
#include "../Shapes/RectangleDrawingStrategy.h"
#include "../Shapes/LineDrawingStrategy.h"
#include "../Shapes/TextDrawingStrategy.h"
#include "../Picture/Picture.h"
#include "../Canvas/PNGCanvas.h"

#ifndef OOD_1_SHAPESCOMMANDPROCESSOR_H
#define OOD_1_SHAPESCOMMANDPROCESSOR_H


void CommandProcessor(std::istream &str);



#endif //OOD_1_SHAPESCOMMANDPROCESSOR_H
