#include "Geometry.h"

class Line:public Geometry
{
public:
	Line(){}

	void calculateRequiredData(QPoint mousePos, int viewportWidth, int viewportHeight) override;
};

