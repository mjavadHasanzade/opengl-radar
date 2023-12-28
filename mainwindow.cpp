#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglcore.h"

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

