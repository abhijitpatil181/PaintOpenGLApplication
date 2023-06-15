#include "OpenglWindow.h"
#include<QMouseEvent>
#include <QOpenGLWidget>
#include<qmessagebox.h>
#include <cmath>



#define M_PI 3.1415926535897932384626433832795
static const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"    gl_Position =  vec4(position, 1.0);\n"
"}";

static const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 fragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"    fragColor = color;\n"
"}";
bool OpenGLWindow::drawLineMode = false;
bool OpenGLWindow::drawCircleMode = false;
bool OpenGLWindow::drawRectangleMode = false;
bool OpenGLWindow::drawPolygonMode = false;

bool rectangleCreationStarted = true;
std::vector<QString> OpenGLWindow::nameList;
std::vector<std::vector<float>> OpenGLWindow::geometrySets;

int OpenGLWindow::treeItemCount = 0;

int OpenGLWindow::lineCounter=1;
int OpenGLWindow::circleCounter=1;
int OpenGLWindow::rectangleCounter=1;
bool OpenGLWindow::isHighLighted = false;


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


	glGenBuffers(1, &m_selectedGeometryVbo);
	glGenBuffers(1, &m_geometryVbo);
	
	// bind the vertex array object of line
	m_selectedGeometryVao.create();
	m_selectedGeometryVao.bind();

	//unbind the vertex array object of line
	m_selectedGeometryVao.release();

	//bind the vertex array object of circle
	m_geometryVao.create();
	m_geometryVao.bind();

	//unbind the vertex array object of circle
	m_geometryVao.release();

	
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.5f, 0.5f, 0.0f);

	m_program->bind();
	


	if (!Geometry::geometryList.empty())
	{
		m_program->setUniformValue("color", QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
		for (int i = 0; i < Geometry::geometryList.size(); i++)
		{
			QOpenGLVertexArrayObject::Binder vaoBinder(&m_geometryVao);
			glBindBuffer(GL_ARRAY_BUFFER, m_geometryVbo);
			glBufferData(GL_ARRAY_BUFFER, Geometry::geometryList[i].size() * sizeof(float), Geometry::geometryList[i].data(), GL_DYNAMIC_DRAW);
			glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(m_posAttr);
			glDrawArrays(GL_LINE_LOOP, 0, Geometry::geometryList[i].size() / 3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (isHighLighted)
		{
			m_program->setUniformValue("color", QVector4D(0.0f, 0.0f, 1.0f, 1.0f));
			for (int i = 0; i < selectedGeometryList.size(); i++)
			{
				QOpenGLVertexArrayObject::Binder vaoBinder(&m_selectedGeometryVao);
				glBindBuffer(GL_ARRAY_BUFFER, m_selectedGeometryVbo);
				glBufferData(GL_ARRAY_BUFFER, selectedGeometryList[i].size() * sizeof(float), selectedGeometryList[i].data(), GL_DYNAMIC_DRAW);
				glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableVertexAttribArray(m_posAttr);
				glDrawArrays(GL_LINE_LOOP, 0, selectedGeometryList[i].size() / 3);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			selectedGeometryList.clear();
			isHighLighted = false;
		}

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

	if (event->button() == Qt::LeftButton)
	{
		QPoint mousePos = event->pos();
		int viewportWidth = width();
		int viewportHeight = height();

		if (drawLineMode)
		{
			geometry = std::make_shared<Line>();
			//geometry= new Line();
			geometry->calculateRequiredData(mousePos, viewportWidth, viewportHeight);
			update();

			if (Geometry::geometryList.size() != 0)
			{
				if (Geometry::geometryList[Geometry::geometryList.size() - 1].size() % 6 == 0 && Geometry::geometryList.size() != treeItemCount)
				{
					//LineCount++;
					emit lineCreated("Line-" + QString::number(lineCounter));
					treeItemCount = Geometry::geometryList.size();
					lineCounter++;
				}
			}
		}
		else if (drawCircleMode)
		{
			
			//geometry = new Circle();
			geometry = std::make_shared<Circle>();
			geometry->calculateRequiredData(mousePos, viewportWidth, viewportHeight);
			update();
			if (Geometry::geometryList.size() != 0)
			{
				if (Geometry::geometryList[Geometry::geometryList.size() - 1].size() % 303 == 0 && Geometry::geometryList.size() != treeItemCount)
				{
					//LineCount++;
					emit lineCreated("Circle -" + QString::number(circleCounter));
					treeItemCount = Geometry::geometryList.size();
					circleCounter++;

				}
			}

		}
		else if (drawRectangleMode)
		{
			
			//geometry = new Rectangles();
			geometry = std::make_shared<Rectangles>();
			geometry->calculateRequiredData(mousePos, viewportWidth, viewportHeight);
			update();

			if (Geometry::geometryList.size() != 0)
			{
				if (Geometry::geometryList[Geometry::geometryList.size() - 1].size() % 24 == 0 && Geometry::geometryList.size() != treeItemCount)
				{
					//LineCount++;
					emit lineCreated("Rectangle-"+ QString::number(rectangleCounter));
					treeItemCount = Geometry::geometryList.size();
					rectangleCounter++;
				}
			}

		}

	}	

	QOpenGLWidget::mousePressEvent(event);
}













