#include "Intersection.h"
#include<QMessageBox>
#include <iostream>

std::vector<Point> Intersection::intersectionPointList;



double Intersection::slopeFinder(std::vector<float> line) {

	double slope;

	if (line[3] != line[0]) {
		slope = ((line[4] - line[1]) / (line[3] - line[0]));
	}
	else {
		slope = 1;
	}

	return slope;
}


void Intersection::intersectionFinder(std::vector<float> line1, std::vector<float> line2) {

	double m1 = slopeFinder(line1);
	double m2 = slopeFinder(line2);

	double b1 = line1[1] - (m1 * line1[0]);
	double b2 = line2[1] - (m2 * line2[0]);

	double x, y;
	x = (b2 - b1) / (m1 - m2);
	y = (m1 * x) + b1;

	if (m1 == 1) {
		x = (b1 - b2) / (m2 - m1);
		y = (m2 * x) + b2;
	}

	Point intersectionPoint{};
	intersectionPoint.x = x;
	intersectionPoint.y = y;
	intersectionPoint.z = 0;



	// Check Valididty 
	// P = (1 - t) * P0 + (t * P1)                 -> P = P0 + t*(P1 - P0)
	// t = (P - P0) / (P1 - P0)                    0 <= t <= 1

	double u, v;
	u = (x - line1[0]) / (line1[3] - line1[0]);
	//if ((line1[3] - line1[0]) == 0) {
	//	u = (y - line1.startY) / (line1.endY - line1.startY);
	//}

	v = (x - line2[0]) / (line2[3] - line2[0]);
	//if ((line2[3] - line2[0]) == 0) {
	//	v = (y - line2.startY) / (line2.endY - line2.startY);
	//}

	//intersectionPointList.push_back(intersectionPoint);

	if (0 <= u && u <= 1 && 0 <= v && v <= 1) {
		intersectionPointList.push_back(intersectionPoint);
		
	}

}




void Intersection::findIntersectionBetItems(std::vector<float> item1, std::vector<float> item2) {

	/*int itemCount1 = 0, itemCount2 = 0,circleCount1=0, circleCount2 = 0;
	(item1.size()==303) ? itemCount1 = 3,circleCount1=3 : itemCount1 = 6,circleCount1=0;
	(item2.size()==303) ? itemCount2 = 3, circleCount2 = 3 : itemCount2 = 6, circleCount2 = 0;
	(item1.size() == 303) ? circleCount1 = 3 : circleCount1 = 0;
	(item2.size() == 303) ? circleCount2 = 3 : circleCount2 = 0;*/

	for (int i = 0; i < item1.size()-3; i+= 3)
	{
		std::vector<float>line1 = { item1[i],item1[i + 1],item1[i + 2],item1[i + 3],item1[i + 4],item1[i + 5] };
				
		for (int j = 0; j < item2.size()- 3; j+= 3)
		{
			std::vector<float>line2;
			
			line2 = { item2[j],item2[j + 1],item2[j + 2],item2[j + 3],item2[j + 4],item2[j + 5] };
			
			intersectionFinder(line1, line2);
			
		}
	}

}
