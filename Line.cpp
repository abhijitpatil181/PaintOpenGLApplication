#include "Line.h"


void Line::calculateRequiredData(QPoint mousePos,int viewportWidth,int viewportHeight)
{
	
	float x = (2.0f * mousePos.x() / viewportWidth) - 1.0f;
	float y = 1.0f - (2.0f * mousePos.y() / viewportHeight);


	verticesList.push_back(x);
	verticesList.push_back(y);
	verticesList.push_back(0.0f);
	
	if (verticesList.size() % 6 == 0)
	{
		
		geometryList.push_back(verticesList);
		
		verticesList.clear();
	}
}
