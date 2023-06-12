#include "PaintApplication.h"
#include <qmessagebox.h>
#include <QPushButton>
#include<QMouseEvent>
#include <QHBoxLayout>
#include <QTreeView>
#include <QSplitter>
#include <QStandardItemModel>

PaintApplication::PaintApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    openglWindow = new OpenGLWindow(this);


  

    // Create the QTreeView widget
    QTreeView* treeView = new QTreeView(this); 


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
    layout->addWidget(ui.Line_Button);
    layout->addWidget(ui.Circle_Button);
    layout->addWidget(ui.Rectangle_Button);
    layout->addWidget(ui.Polygon_Button);


    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addLayout(layout);
    vLayout->addWidget(splitter);
    

   
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);


    
    
    //connect(ui.Line_Button, SIGNAL(clicked()), this, SLOT(on_Line_Button_click()));
    //connect(ui.Circle_Button, SIGNAL(clicked()), this, SLOT(on_Circle_Button_click()));
    //connect(ui.Rectangle_Button, SIGNAL(clicked()), this, SLOT(on_Rectangle_Button_click()));



    connect(ui.Line_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawLineMode = !OpenGLWindow::drawLineMode; // Toggle the drawLineMode flag
        if (OpenGLWindow::drawLineMode)
            ui.Line_Button->setStyleSheet("background-color: red;");
        else
            ui.Line_Button->setStyleSheet("");
        });

    connect(ui.Circle_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawCircleMode = !OpenGLWindow::drawCircleMode; // Toggle the drawCircleMode flag
        if (OpenGLWindow::drawCircleMode)
            ui.Circle_Button->setStyleSheet("background-color: red;");
        else
            ui.Circle_Button->setStyleSheet("");
        });


    connect(ui.Rectangle_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawRectangleMode = !OpenGLWindow::drawRectangleMode; // Toggle the drawRectangleMode flag
        if (OpenGLWindow::drawRectangleMode)
            ui.Rectangle_Button->setStyleSheet("background-color: red;");
        else
            ui.Rectangle_Button->setStyleSheet("");
        });

    connect(ui.Polygon_Button, &QPushButton::clicked, this, [this]() 
        {
        OpenGLWindow::drawPolygonMode = !OpenGLWindow::drawPolygonMode; // Toggle the drawPolygonMode flag
        if (OpenGLWindow::drawPolygonMode)
            ui.Polygon_Button->setStyleSheet("background-color: red;");
        else
            ui.Polygon_Button->setStyleSheet("");
        });

   

    connect(openglWindow, &OpenGLWindow::lineCreated, this, [model](const QString& name)
        {
        QStandardItem* item = new QStandardItem(name);
        model->appendRow(item);
        });


    //connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &PaintApplication::onSelectionChanged);
   // connect(openglWindow, &OpenGLWindow::lineCreated, this, &PaintApplication::onLineCreated);

   /* connect(treeView, &QTreeView::clicked, this, [this,model](const QModelIndex& index) {
        QStandardItem* selectedItem = model->itemFromIndex(index);
        QString shapeName = selectedItem->text();
        openglWindow->highlightShape(shapeName);
        });*/
}

PaintApplication::~PaintApplication()
{}
//void PaintApplication::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
//{
//    Q_UNUSED(deselected); // Avoid unused parameter warning
//
//    // Get the selected item from the model
//    QModelIndexList selectedIndexes = selected.indexes();
//    if (!selectedIndexes.isEmpty())
//    {
//        QModelIndex selectedIndex = selectedIndexes.first();
//        QStandardItem* selectedItem = model->itemFromIndex(selectedIndex);
//
//        // Get the selected item's text
//        QString selectedText = selectedItem->text();
//
//        // Update the OpenGLWindow based on the selected item's text
//        if (selectedText == "Line")
//        {
//            OpenGLWindow::drawLineMode = true;
//            OpenGLWindow::drawCircleMode = false;
//            OpenGLWindow::drawRectangleMode = false;
//            OpenGLWindow::drawPolygonMode = false;
//        }
//        else if (selectedText == "Circle")
//        {
//            OpenGLWindow::drawLineMode = false;
//            OpenGLWindow::drawCircleMode = true;
//            OpenGLWindow::drawRectangleMode = false;
//            OpenGLWindow::drawPolygonMode = false;
//        }
//        else if (selectedText == "Rectangle")
//        {
//            OpenGLWindow::drawLineMode = false;
//            OpenGLWindow::drawCircleMode = false;
//            OpenGLWindow::drawRectangleMode = true;
//            OpenGLWindow::drawPolygonMode = false;
//        }
//        else if (selectedText == "Polygon")
//        {
//            OpenGLWindow::drawLineMode = false;
//            OpenGLWindow::drawCircleMode = false;
//            OpenGLWindow::drawRectangleMode = false;
//            OpenGLWindow::drawPolygonMode = true;
//        }
//
//        // Trigger a repaint of the OpenGLWindow
//        openglWindow->update();
//    }
//}

//void PaintApplication::onLineCreated(const QString& lineName)
//{
//    // Add the line name to the QTreeView model
//    QStandardItem* lineItem = new QStandardItem(lineName);
//    model->appendRow(lineItem);
//}

//void PaintApplication::on_Line_Button_click()
//{
//}
//void PaintApplication::on_Circle_Button_click() {
//    QMessageBox::information(this, tr("Title"), tr("The Circle Creator"));
//}
//void PaintApplication::on_Rectangle_Button_click() {
//    QMessageBox::information(this, tr("Title"), tr("The Rectangle Creator"));
//}