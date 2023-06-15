#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <string>
#include <QString>
#include "Geometry.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangles.h"
#include <memory>

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions 
{

   Q_OBJECT


public:
    OpenGLWindow(QWidget* parent = nullptr);
    
    //Geometry* geometry;

    std::shared_ptr<Geometry> geometry;
    static int treeItemCount;
    void initializeGL()override;
    void paintGL()override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent* event) override;
  
    static bool drawLineMode;
    static bool drawCircleMode;
    static bool drawRectangleMode;
    static bool drawPolygonMode;
    static std::vector<std::vector<float>> geometrySets;
    
    static std::vector<QString> nameList;
    static int lineCounter;
    static int circleCounter;
    static int rectangleCounter;
    static bool isHighLighted ;
    std::vector<std::vector<float>> selectedGeometryList;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
   
    QOpenGLShaderProgram* m_program;


    GLuint m_selectedGeometryVbo;
    GLuint m_geometryVbo;

    QOpenGLVertexArrayObject m_selectedGeometryVao, m_geometryVao;
      
signals:
    void lineCreated(const QString& name);

};


