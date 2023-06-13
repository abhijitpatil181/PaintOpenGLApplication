#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <string>

#include <QString>

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions 
{

   Q_OBJECT


public:
    OpenGLWindow(QWidget* parent = nullptr);



    void initializeGL()override;
    void paintGL()override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent* event) override;

    std::vector<float> rectangleVertices;



    void createLine(QPoint mousePos);
    void createCircle(QPoint mousePos);
    void createRectangle(QPoint mousePos);
    void createPolygon(QPoint mousePos);
    static bool drawLineMode;
    static bool drawCircleMode;
    static bool drawRectangleMode;
    static bool drawPolygonMode;
    void updateName();

    static std::vector<QString> nameList;
    int LineCount = 0;
    int CircleCount = 0;
    int RectangleCount = 0;


private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
   
    QOpenGLShaderProgram* m_program;


    GLuint m_lineVbo;
    GLuint m_circleVbo;
    GLuint m_rectangleVbo;
    GLuint m_polygonVbo;

    QOpenGLVertexArrayObject m_lineVao, m_circleVao, m_rectangleVao, m_polygonVao;
  
    std::vector<float> lineVertices;
    std::vector<float> circleVertices;


    std::vector<std::vector<float>> geometrySets;
    std::vector<std::vector<float>> rectangleSets;

    std::vector<std::vector<float>> polygonSets;
   
    std::vector<float> polygonVertices;

    
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 modelMatrix;
    QMatrix4x4 viewMatrix;
 

signals:
    void lineCreated(const QString& name);


};

