#include "PaintApplication.h"
#include <qmessagebox.h>
#include <QPushButton>
#include<QMouseEvent>
#include <QHBoxLayout>
#include <QTreeView>
#include <QSplitter>
#include <QStandardItemModel>
#include <qlabel.h>

PaintApplication::PaintApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    openglWindow = new OpenGLWindow(this);

    // Create the QTreeView widget
    treeView = new QTreeView(this); 

    // Create the model for the QTreeView
    QStandardItemModel* model = new QStandardItemModel(this);
    treeView->setModel(model);
    treeView->currentIndex();

    // Set the minimum width of the QTreeView
    treeView->setMinimumSize(200,400); 

    treeView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);


    

    // Create a QSplitter to split the openglwindow and treeview
    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    // Add the treeView widget to the splitter
    splitter->addWidget(treeView); 


    // Add the openglWindow widget to the splitter
    splitter->addWidget(openglWindow); 

     // Set the initial sizes of the splitter's widgets
    splitter->setSizes(QList<int>() << 50 << 950); // Adjust the sizes as needed


    QHBoxLayout* layout = new QHBoxLayout; 

    QLabel* label = new QLabel("Select Shape");

    // Add the QLabel to the layout
    layout->addWidget(label);

    //add buttons
    layout->addWidget(ui.Line_Button);
    layout->addWidget(ui.Circle_Button);
    layout->addWidget(ui.Rectangle_Button);
    


    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addLayout(layout);
    vLayout->addWidget(splitter);
    

   
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);


    connect(ui.Line_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawLineMode = !OpenGLWindow::drawLineMode; // Toggle the drawLineMode flag
        if (OpenGLWindow::drawLineMode)
            ui.Line_Button->setStyleSheet("background-color: green;");
        else
            ui.Line_Button->setStyleSheet("");
        });

    connect(ui.Circle_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawCircleMode = !OpenGLWindow::drawCircleMode; // Toggle the drawCircleMode flag
        if (OpenGLWindow::drawCircleMode)
            ui.Circle_Button->setStyleSheet("background-color: green;");
        else
            ui.Circle_Button->setStyleSheet("");
        });


    connect(ui.Rectangle_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawRectangleMode = !OpenGLWindow::drawRectangleMode; // Toggle the drawRectangleMode flag
        if (OpenGLWindow::drawRectangleMode)
            ui.Rectangle_Button->setStyleSheet("background-color: green;");
        else
            ui.Rectangle_Button->setStyleSheet("");
        });

    //connect(ui.Polygon_Button, &QPushButton::clicked, this, [this]() 
    //    {
    //    OpenGLWindow::drawPolygonMode = !OpenGLWindow::drawPolygonMode; // Toggle the drawPolygonMode flag
    //    if (OpenGLWindow::drawPolygonMode)
    //        ui.Polygon_Button->setStyleSheet("background-color: green;");
    //    else
    //        ui.Polygon_Button->setStyleSheet("");
    //    });

   

    connect(openglWindow, &OpenGLWindow::lineCreated, this, [model](const QString& name)
        {
        QStandardItem* item = new QStandardItem(name);
        model->appendRow(item);
        });

    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        QModelIndexList selectedIndexes = treeView->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty()) {
            QModelIndex selectedIndex = selectedIndexes.first();
            // Retrieve the necessary information from the selected item
            int lineId = selectedIndex.row();
            // Trigger a repaint of the OpenGL widget
            OpenGLWindow::isHighLighted = true;
            openglWindow->selectedGeometryList.push_back(Geometry::geometryList[lineId]);
            openglWindow->update();
        }
        });


   
}

PaintApplication::~PaintApplication()
{}



