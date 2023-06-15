#pragma once
#include "Geometry.h"
class Rectangles :
    public Geometry
{
public:
    Rectangles() {}
    void calculateRequiredData(QPoint mousePos, int viewportWidth, int viewportHeight)override;
};

