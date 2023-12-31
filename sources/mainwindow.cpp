#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/openglcore.h"
#include "headers/pythoncore.h"
#include <QLabel>
#include<QHBoxLayout>
#include<QCheckBox>
#include<QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PythonCore *py = new PythonCore("D:/tut_cpp/opengl-radar/2022080617001200dBZ.vol", "D:/tut_cpp/opengl-radar", this);
//    qDebug() << py->data[activeElevation].length();

    OpenGlCore *glw = new OpenGlCore(py->data, py->rays[0], py->bins[0], this);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Create the sidebar widget
    QWidget* sidebarWidget = new QWidget(this);
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebarWidget);

    // Create a button group for the checkboxes
    QButtonGroup* buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true); // Make checkboxes mutually exclusive

    // Add the checkboxes and labels to the sidebar layout and button group
    for (int i = 0; i < py->sliceCount; i++) {
        QHBoxLayout* checkboxLayout = new QHBoxLayout;
        QCheckBox* checkbox = new QCheckBox;
        checkbox->setText(QString("Checkbox %1").arg(i + 1));

        checkboxLayout->addWidget(checkbox);
        sidebarLayout->addLayout(checkboxLayout);

        // Add the checkbox to the button group
        buttonGroup->addButton(checkbox);

        connect(checkbox, &QCheckBox::clicked, [i, glw]() {
            glw->updateRadar(i);
        });
    }

    // Add the sidebar widget and OpenGL widget to the main layout
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

