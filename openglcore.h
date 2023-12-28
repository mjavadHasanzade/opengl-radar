#ifndef OPENGLCORE_H
#define OPENGLCORE_H

#include <QWidget>
#include <QOpenGLWidget>

class OpenGlCore : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGlCore(QWidget *parent = nullptr);
    void drawXAxis(float length);
    void drawYAxis(float length);

signals:

public slots:
    void updateAnimation();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void drawCircleBorder(int numSegments, float radius,bool fill=false);

    float angle = 0.0f;

    void drawMovingLine(float radius);
};

#endif // OPENGLCORE_H
