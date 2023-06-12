#include "OpenglWindow.h"
#include<QMouseEvent>
#include <QOpenGLWidget>
#include<qmessagebox.h>
#include <cmath>



#define M_PI 3.1415926535897932384626433832795
static const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"uniform mat4 u_projectionMatrix;"
"uniform mat4 u_viewMatrix;"
"uniform mat4 u_modelMatrix;"
"void main()\n"
"{\n"
"    gl_Position = u_projectionMatrix *  u_viewMatrix * u_modelMatrix * vec4(position, 1.0);\n"
"}";

static const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"    fragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}";
bool OpenGLWindow::drawLineMode = false;
bool OpenGLWindow::drawCircleMode = false;
bool OpenGLWindow::drawRectangleMode = false;
bool OpenGLWindow::drawPolygonMode = false;

bool rectangleCreationStarted = true;
std::vector<QString> OpenGLWindow::nameList;


OpenGLWindow::OpenGLWindow(QWidget* parent)
	: QOpenGLWidget(parent)
{
	setMouseTracking(true);
}

void OpenGLWindow::initializeGL()
{
	initializeOpenGLFunctions();

	QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
	vertexShader->compileSourceCode(vertexShaderSource);

	QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
	fragmentShader->compileSourceCode(fragmentShaderSource);

	m_program = new QOpenGLShaderProgram(this);
	m_program->addShader(vertexShader);
	m_program->addShader(fragmentShader);
	m_program->link();

	m_posAttr = m_program->attributeLocation("position");

	/*QOpenGLVertexArrayObject::Binder vaoBinder(&m_lineVao);
	glGenBuffers(1, &m_lineVbo);

	QOpenGLVertexArrayObject::Binder vaoBinder(&m_circleVao);
	glGenBuffers(1, &m_circleVbo);*/


	glGenBuffers(1, &m_lineVbo);
	glGenBuffers(1, &m_circleVbo);
	glGenBuffers(1, &m_rectangleVbo);
	glGenBuffers(1, &m_polygonVbo);

	

	// bind the vertex array object of line
	m_lineVao.create();
	m_lineVao.bind();

	//unbind the vertex array object of line
	m_lineVao.release();

	//bind the vertex array object of circle
	m_circleVao.create();
	m_circleVao.bind();

	//unbind the vertex array object of circle
	m_circleVao.release();

	// bind the vertex array object of rectangle
	m_rectangleVao.create();
	m_rectangleVao.bind();

	//unbind the vertex array object of rectangle
	m_rectangleVao.release();

	// bind the vertex array object of rectangle
	m_polygonVao.create();
	m_polygonVao.bind();

	//unbind the vertex array object of rectangle
	m_polygonVao.release();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.5f, 0.5f, 0.0f);

	m_program->bind();
	m_program->setUniformValue("u_projectionMatrix", projectionMatrix);
	m_program->setUniformValue("u_viewMatrix", viewMatrix);
	m_program->setUniformValue("u_modelMatrix", modelMatrix);

	
	if (drawLineMode)
	{		
		QOpenGLVertexArrayObject::Binder vaoBinder(&m_lineVao);
		glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
		glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(float), lineVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(m_posAttr);
		glDrawArrays(GL_LINES, 0, lineVertices.size() / 3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	if (drawCircleMode)
	{
		for (int i = 0; i < geometrySets.size(); i++)
		{
			QOpenGLVertexArrayObject::Binder vaoBinder(&m_circleVao);
			glBindBuffer(GL_ARRAY_BUFFER, m_circleVbo);
			glBufferData(GL_ARRAY_BUFFER, geometrySets[i].size() * sizeof(float), geometrySets[i].data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(m_posAttr);
			glDrawArrays(GL_LINE_LOOP, 0, geometrySets[i].size() / 3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		
	}


	if (drawRectangleMode)
	{
		for (const auto& vertices : geometrySets)
		{
			QOpenGLVertexArrayObject::Binder vaoBinder(&m_rectangleVao);
			glBindBuffer(GL_ARRAY_BUFFER, m_rectangleVbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(m_posAttr);
			glDrawArrays(GL_LINES, 0, vertices.size() / 3);		
		}   glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	if (drawPolygonMode)
	{
		QOpenGLVertexArrayObject::Binder vaoBinder(&m_polygonVao);
		glBindBuffer(GL_ARRAY_BUFFER, m_polygonVbo);
		glBufferData(GL_ARRAY_BUFFER, polygonVertices.size() * sizeof(float), polygonVertices.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(m_posAttr);
		glDrawArrays(GL_LINES, 0, polygonVertices.size() / 3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	m_program->release();
}

void OpenGLWindow::resizeGL(int width, int height)
{
	/*glViewport(0, 0, width, height);

	projectionMatrix.setToIdentity();
	if (width <= height)
	{
		projectionMatrix.ortho(100.0f, 100.0f, -100.0f * height / width, 100.0f * height / width, -100.0f, 100.0f);
	}
	else
	{
		projectionMatrix.ortho(-100.0f * width / height, 100.0f * width / height, -100.0f, 100.0f, -100.0f, 100.0f);
	}*/
}


void OpenGLWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton&& drawLineMode)
	{
		
		QPoint mousePos = event->pos();

		createLine(mousePos);
		
		if (lineVertices.size()%6==0)
		{
			emit lineCreated("Line");
		}
		
		
	}
    else if (event->button() == Qt::LeftButton && drawCircleMode)
	{
		QPoint mousePos = event->pos();
		createCircle(mousePos);

		
	}
	else if (event->button() == Qt::LeftButton && drawRectangleMode)
	{
		QPoint mousePos = event->pos();
		createRectangle(mousePos);

		if (rectangleVertices.size() == 24)
		{
			createRectangle(mousePos);
			
		}		
		if (rectangleVertices.size() % 24 == 0)
		{

			emit lineCreated("Rectangle");

		}
		
	}

	else if (event->button() == Qt::LeftButton && drawPolygonMode)
	{
		QPoint mousePos = event->pos();
		createPolygon(mousePos);
	}

	
	QOpenGLWidget::mousePressEvent(event);
}


void OpenGLWindow::createLine(QPoint mousePos)
{
	int viewportWidth = width();
	int viewportHeight = height();

	//float x = mousePos.x();
	//float y = mousePos.y();
	float x = (2.0f * mousePos.x() / viewportWidth) - 1.0f;
	float y = 1.0f - (2.0f * mousePos.y() / viewportHeight);


	lineVertices.push_back(x);
	lineVertices.push_back(y);
	lineVertices.push_back(0.0f);

	//geometrySets.push_back(lineVertices);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
		glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(float), lineVertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	update();

	
}

void OpenGLWindow::createCircle(QPoint mousePos)
{
	int viewportWidth = width();
	int viewportHeight = height();

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

		circleVertices.clear();

		for (int i = 0; i <= numSegments; ++i)
		{
			float angle = 2.0f * M_PI * i / numSegments;
			float cx = center.x() + radius * std::cos(angle);
			float cy = center.y() + radius * std::sin(angle);

			circleVertices.push_back(cx);
			circleVertices.push_back(cy);
			circleVertices.push_back(0.0f);
			
		}

		geometrySets.push_back(circleVertices);
		glBindBuffer(GL_ARRAY_BUFFER, m_circleVbo);
		glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), circleVertices.data(),GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		centerSet = false;


		if (circleVertices.size() == 303)
		{
			emit lineCreated("Circle");
		}
	}

	update();
	
}

void OpenGLWindow::createRectangle(QPoint mousePos)
{
	int viewportWidth = width();
	int viewportHeight = height();

	float x1 = (2.0f * mousePos.x() / viewportWidth) - 1.0f;
	float y1 = 1.0f - (2.0f * mousePos.y() / viewportHeight);

	
	if (rectangleVertices.size() < 22) {

		if (rectangleVertices.size() != 0)
		{
			rectangleVertices.push_back(x1);
			rectangleVertices.push_back(y1);
			rectangleVertices.push_back(0.0f);
		}

		rectangleVertices.push_back(x1);
		rectangleVertices.push_back(y1);
		rectangleVertices.push_back(0.0f);


		if (rectangleVertices.size() > 18) {
			rectangleVertices.push_back(rectangleVertices[0]);
			rectangleVertices.push_back(rectangleVertices[1]);
			rectangleVertices.push_back(rectangleVertices[2]);


			geometrySets.push_back(rectangleVertices);

			rectangleVertices.clear();
		}

	}
	
	for (const auto& vertices : geometrySets) {
		glBindBuffer(GL_ARRAY_BUFFER, m_rectangleVbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	

	update();

}



void OpenGLWindow::createPolygon(QPoint mousePos)
{
	int viewportWidth = width();
	int viewportHeight = height();

	float x1 = (2.0f * mousePos.x() / viewportWidth) - 1.0f;
	float y1 = 1.0f - (2.0f * mousePos.y() / viewportHeight);


	if (polygonVertices.size() != 0)
	{
		polygonVertices.push_back(x1);
		polygonVertices.push_back(y1);
		polygonVertices.push_back(0.0f);
	}

	polygonVertices.push_back(x1);
	polygonVertices.push_back(y1);
	polygonVertices.push_back(0.0f);


	// Update the buffer data
	glBindBuffer(GL_ARRAY_BUFFER, m_polygonVbo);
	glBufferData(GL_ARRAY_BUFFER, polygonVertices.size() * sizeof(float), polygonVertices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	update();
}


