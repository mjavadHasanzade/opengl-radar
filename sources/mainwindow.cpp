#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/openglcore.h"
#include "headers/pythoncore.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PythonCore *py=new PythonCore("D:/tut_cpp/opengl-radar/2016042220450500dBuZ.vol","D:/tut_cpp/opengl-radar", this);
    qDebug()<<py->data[0].length();

    OpenGlCore *glw=new OpenGlCore(py->data[2], py->rays[0],py->bins[0],this);
    setCentralWidget(glw);

}

MainWindow::~MainWindow()
{
    delete ui;
}

