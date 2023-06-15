#include "Rectangles.h"


void Rectangles::calculateRequiredData(QPoint mousePos, int viewportWidth, int viewportHeight)
{
	float x1 = (2.0f * mousePos.x() / viewportWidth) - 1.0f;
	float y1 = 1.0f - (2.0f * mousePos.y() / viewportHeight);


	if (verticesList.size() < 22) {

		if (verticesList.size() != 0)
		{
			verticesList.push_back(x1);
			verticesList.push_back(y1);
			verticesList.push_back(0.0f);
		}

		verticesList.push_back(x1);
		verticesList.push_back(y1);
		verticesList.push_back(0.0f);


		if (verticesList.size() > 18) {
			verticesList.push_back(verticesList[0]);
			verticesList.push_back(verticesList[1]);
			verticesList.push_back(verticesList[2]);


			
		
			geometryList.push_back(verticesList);

			verticesList.clear();
		}

	}
}


