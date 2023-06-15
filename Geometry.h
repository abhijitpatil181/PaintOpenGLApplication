#ifndef GEOMETRY_H
#define GEOMETRY_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <string>
#include <QString>
#include <vector>
#include <unordered_map>
#include <QObject>

class Geometry
{
public:
	static std::vector<float> verticesList;
	static std::vector<std::vector<float>> geometryList;
	/*static std::unordered_map<QString, std::vector<float>>geometrySet;
	static int count ;*/

	Geometry(){}
	virtual void calculateRequiredData(QPoint mousePos, int viewportWidth, int viewportHeight)=0;

};

#endif

