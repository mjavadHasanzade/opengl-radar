#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/openglcore.h"
#include "headers/pythoncore.h"
#include <QLabel>
#include<QHBoxLayout>
#include<QSpinBox>
#include<QLabel>
#include <QDir>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PythonCore *py = new PythonCore("D:/tut_cpp/opengl-radar/2022080617001200dBZ.vol",QDir::currentPath(), this);
//    qDebug() << py->data[activeElevation].length();

    OpenGlCore *glw = new OpenGlCore(py->data, py->rays[0], py->bins[0], this);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QWidget* sidebarWidget = new QWidget(this);
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebarWidget);

    QComboBox *elevationCombo=new QComboBox;
    QLabel *lbl=new QLabel("Elevation");
    QSpinBox *spn=new QSpinBox(this);
    spn->setRange(0,py->posAngles.size()-1);

    connect(spn,&QSpinBox::valueChanged,[glw,spn,elevationCombo](){
        glw->updateRadar(spn->value());

       elevationCombo->setCurrentIndex(spn->value());

    });


    foreach (auto item, py->posAngles) {
        elevationCombo->addItem(QString::number(item));
    }

    connect(elevationCombo,&QComboBox::currentTextChanged,[=](){

        float pos=elevationCombo->currentText().toFloat();
        int posIndex;

        for (int i = 0; i < py->posAngles.size(); ++i) {
            if(pos==py->posAngles.at(i)){
                posIndex=i;
                break;
            }
        }

        spn->setValue(posIndex);

    });

    sidebarLayout->addWidget(lbl);
    sidebarLayout->addWidget(spn);
    sidebarLayout->addWidget(elevationCombo);
    sidebarLayout->addStretch();

    mainLayout->addWidget(glw, 4);
    mainLayout->addWidget(sidebarWidget, 1);

    // Create the central widget and set the main layout on it
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    // Set the central widget on the main window
    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

