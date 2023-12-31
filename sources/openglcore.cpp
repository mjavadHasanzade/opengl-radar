#include "headers/openglcore.h"
#include <qmath.h>
#include <QTimer>
#include <QDebug>

OpenGlCore::OpenGlCore(QList<uchar> data,int rays,int bins, QWidget *parent) :
    QOpenGLWidget(parent), mData(data),mRays(rays),mBins(bins)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->start(10);
}

void OpenGlCore::initializeGL()
{
    makeCurrent();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGlCore::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    qreal aspectRatio = qreal(w) / qreal(h);
    glOrtho(-1 * aspectRatio, 1 * aspectRatio, -1, 1, 1, -1);
}

void OpenGlCore::setGLColor(uchar number)
{
    if (number != 0)
    {
        float red = number / 255.0f;
        float green = number / 255.0f;
        float blue = number / 255.0f;
        glColor3f(red, green, blue);
    }
    else
    {
        glColor3f(0.0, 0.0, 0.0);

    }
}

void OpenGlCore::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1.0f);
    // Calculate the angle between each sector
    float angleIncrement = 360.0f / mRays;

    // Calculate the radius of each arc segment
    float radiusIncrement = 1.0f / mBins;

    for (int sector = 0; sector < mData.length() / mBins; ++sector) // to get the count of sectors
    {
        // Calculate the start and end angles for the arc
        float startAngle = sector * angleIncrement;
        float endAngle = (sector + 1) * angleIncrement;

        // Draw Bins
        for (int line = 0; line < mData.length() / mRays; ++line)
        {
            // Get the index in the vector for the current line
            int index = sector * mBins + line;


            uchar dataValue = mData.at(index);

            setGLColor(dataValue);


            // Calculate the center and radius of the arc
            float centerX = 0.0f; // Set the X coordinate of the center of the arc
            float centerY = 0.0f; // Set the Y coordinate of the center of the arc
            float radius = radiusIncrement * (line + 0.25f); // Calculate the radius of the current arc

            // Draw the arc
            glBegin(GL_LINE_STRIP);
            for (float angle = startAngle; angle < endAngle; angle += 0.2f)
            {
                // Calculate the point on the arc
                float x = centerX + radius * cos(angle * M_PI / 180.0f);
                float y = centerY + radius * sin(angle * M_PI / 180.0f);

                // Specify the vertex coordinate
                glVertex2f(x, y);
            }
            glEnd();
        }
    }


    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleBorder(360, 1);
    drawCircleBorder(360, 0.5);
    drawCircleBorder(360, 0.25);

    drawXAxis(1); // Adjust the length as needed
    drawYAxis(1); // Adjust the length as needed
    drawMovingLine(1);
}

void OpenGlCore::drawCircleBorder(int numSegments, float radius, bool fill)
{
    const float theta = 2.0f * M_PI / numSegments;

    if (fill)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    for (int i = 0; i < numSegments; ++i)
    {
        float x = radius * cos(i * theta);
        float y = radius * sin(i * theta);
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
    const float radian = movingLineAngle * (M_PI / 180.0f);

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);  // Starting point at the center of the radar
    glVertex2f(length * cosf(radian), length * sinf(radian));  // Endpoint on the circle
    glEnd();
}

void OpenGlCore::updateAnimation()
{
    float angleIncrement = 0.5;
    movingLineAngle += angleIncrement;  // Increment the angle

    if (movingLineAngle > 360.0f)
        movingLineAngle -= 360.0f;

    update();
}
