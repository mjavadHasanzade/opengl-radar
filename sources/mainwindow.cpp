#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/openglcore.h"

#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenGlCore *glw=new OpenGlCore(this);
    setCentralWidget(glw);

}

MainWindow::~MainWindow()
{
    delete ui;
}

