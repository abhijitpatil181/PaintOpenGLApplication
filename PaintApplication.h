#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PaintApplication.h"
#include "OpenglWindow.h"
#include <QObject>
#include "Geometry.h"
#include <QStandardItemModel>
#include <QTreeView>
//#include "Line.h"

class PaintApplication : public QMainWindow
{
    Q_OBJECT

public:
    PaintApplication(QWidget *parent = nullptr);
    ~PaintApplication();

    QList<QString> lineNames;
    int lineCounter = 1;
    QStandardItemModel * model;

private:
    Ui::PaintApplicationClass ui;
    OpenGLWindow* openglWindow;
    QTreeView* treeView;
    Intersection ipoint;

private slots:
   
};
