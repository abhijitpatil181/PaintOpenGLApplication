
#include <cmath>
#include<vector>
#include<QPoint>
#include "Geometry.h"
#include <vector>

struct Point
{
	float x, y, z;
};

class Intersection {
public:

	double px, py;

	double PI = 3.14159265359;

	static std::vector<Point> intersectionPointList;
	//std::vector<Point> intersectionPointList;

	Intersection(){}

	double slopeFinder(std::vector<float> line);
	int sideIndicator(std::vector<float> line1, std::vector<float> line2);
	void intersectionFinder(std::vector<float> line1, std::vector<float> line2);
	void findIntersectionBetItems(std::vector<float> item1, std::vector<float> item2);
	

};