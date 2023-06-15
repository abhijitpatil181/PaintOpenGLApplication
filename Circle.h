
#include "Geometry.h"
#include <cmath>

class Circle :
    public Geometry
{
public:
    Circle(){}
    void calculateRequiredData(QPoint mousePos, int viewportWidth, int viewportHeight)override;
};

