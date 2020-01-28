#include "../../Framework/Interface/DisplayableObject.h"
#include "../../Framework/Engine/Scene.h"
#include <cmath>
#pragma once

class DrawObject
{
public:
    DrawObject();
    ~DrawObject();

    void DrawFillCircleTop(float circle_radius, float half_height, float color[]);
    void DrawFillCircleBottom(float circle_radius, float half_height, float color[]);
    void DrawCylinder(float circle_radius, float half_height,
                      float top_color[], float bottom_color[], float body_color[]);
    void DrawTruncatedCone(float top_circle_radius, float bottom_circle_radius,
                           float half_height, float top_offset,float bottom_offset,
                           float top_color[], float bottom_color[], float body_color[]);
    void DrawTruncatedConeWithSkipAngle(float top_circle_radius, float bottom_circle_radius,
                           float half_height, float top_offset,float bottom_offset,
                           float top_color[], float bottom_color[], float body_color[]);
    void DrawSolidSphere(float radius, float slices, float stacks);
    void DrawCube();
};
