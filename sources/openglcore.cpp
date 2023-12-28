#include "headers/openglcore.h"
#include <qmath.h>
#include <QTimer>
#include <QDebug>

OpenGlCore::OpenGlCore(QWidget *parent) : QOpenGLWidget(parent)
{

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->start(10);
}


void OpenGlCore::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



}

void OpenGlCore::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);

    qreal aspectRatio=qreal(w)/qreal(h);

    glOrtho(-1*aspectRatio,1*aspectRatio,-1,1,1,-1);
}

void OpenGlCore::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 0.0f);


    for (float i = 0; i < 361; ++i) {

        float radian=i * (M_PI / 180.0);
        glColor3f(i>255?(i-255)/255:i/255, i>255?(i-255)/255:i/255, i>255?(i-255)/255:i/255);

        glLineWidth(1.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f); // starting point
        glVertex2f(0.85 * cosf(radian), 0.85 * sinf(radian)); // end point
        glEnd();
    }



    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleBorder(360, 0.85);
    drawCircleBorder(360, 0.5);
    drawCircleBorder(360, 0.25);
    drawCircleBorder(360, 0.01, true);

    drawXAxis(0.95f); // Adjust the length as needed
    drawYAxis(0.95f); // Adjust the length as needed
    drawMovingLine(0.85);

}

void OpenGlCore::drawCircleBorder(int numSegments, float radius, bool fill)
{
    const float theta = 2.0f * M_PI / float(numSegments);

    if (fill)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    for (int i = 0; i < numSegments; ++i)
    {
        float x = radius * cosf(i * theta);
        float y = radius * sinf(i * theta);
        glVertex2f(x, y);
    }

    glEnd();
}

void OpenGlCore::drawXAxis(float length)
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-length, 0.0f);
    glVertex2f(length, 0.0f);
    glEnd();
}

void OpenGlCore::drawYAxis(float length)
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -length);
    glVertex2f(0.0f, length);
    glEnd();
}

void OpenGlCore::drawMovingLine(float length)
{
    const float radian = angle * (M_PI / 180.0f);

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);  // Starting point at the center of the radar
    glVertex2f(length * cosf(radian), length * sinf(radian));  // Endpoint on the circle
    glEnd();
}


void OpenGlCore::updateAnimation()
{

    float angleIncrement = 0.5;

    angle += angleIncrement;  // Increment the angle

    if (angle > 360.0f)
        angle -= 360.0f;

    update();
}
