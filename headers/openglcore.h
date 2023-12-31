#ifndef OPENGLCORE_H
#define OPENGLCORE_H

#include <QWidget>
#include <QOpenGLWidget>

class OpenGlCore : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGlCore(QList<uchar> data,int rays,int bins,QWidget *parent = nullptr);
    void drawXAxis(float length);
    void drawYAxis(float length);

signals:

public slots:
    void updateAnimation();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QList<uchar> mData;
    void drawCircleBorder(int numSegments, float radius,bool fill=false);
    float movingLineAngle = 0.0f;
    void drawMovingLine(float length);
    void setGLColor(uchar number);
    int mRays;
    int mBins;

};

#endif // OPENGLCORE_H
