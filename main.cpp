#include "headers/mainwindow.h"
#include <QSurfaceFormat>
#include <QApplication>

int main(int argc, char *argv[])
{

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(2, 1); // Adjust the version to match your desired OpenGL version
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
