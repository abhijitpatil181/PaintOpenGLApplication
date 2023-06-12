#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PaintApplication.h"
#include "OpenglWindow.h"
#include <QObject>

#include <QStandardItemModel>
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
    //QStandardItemModel* model; 


private slots:
   // void onSelectionChanged(const QModelIndex& index);
};
