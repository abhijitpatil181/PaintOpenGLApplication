#include "Circle.h"
#define M_PI 3.1415926535897932384626433832795

void Circle::calculateRequiredData(QPoint mousePos, int viewportWidth, int viewportHeight)
{
	

	float x = (2.0f * mousePos.x() / viewportWidth) - 1.0f;
	float y = 1.0f - (2.0f * mousePos.y() / viewportHeight);

	static bool centerSet = false;
	static QPointF center;
	if (!centerSet)
	{
		center = QPointF(x, y);
		centerSet = true;
	}
	else
	{
		// Number of line segments to the circle
		const int numSegments = 100;

		float radius = std::sqrt((x - center.x()) * (x - center.x()) + (y - center.y()) * (y - center.y()));


		for (int i = 0; i <= numSegments; ++i)
		{
			float angle = 2.0f * M_PI * i / numSegments;
			float cx = center.x() + radius * std::cos(angle);
			float cy = center.y() + radius * std::sin(angle);

			verticesList.push_back(cx);
			verticesList.push_back(cy);
			verticesList.push_back(0.0f);

		}

		
		
		geometryList.push_back(verticesList);
		centerSet = false;
		verticesList.clear();

	}

}