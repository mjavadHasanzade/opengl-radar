#ifndef PYTHONCORE_H
#define PYTHONCORE_H

#include <QObject>
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

#include <QElapsedTimer>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>


class PythonCore : public QObject
{
    Q_OBJECT
public:
    explicit PythonCore(QString fileName,QString execPath,QObject *parent = nullptr);
    ~PythonCore();
    QString mFileName;QString mExecPath;
    QList<int> rays; QList<int> bins; int sliceCount; QList<QList<ushort>> startAngle; QList<QList<ushort>> stopAngle; QList<QList<uchar>> data;float angleStep;int stopRange;

private:
    PyObject* pModule;
    void loadVolData(QString fileName,QString execPath, QList<int> *rayS, QList<int> *binS,
                     int *slicecount, QList<QList<ushort>> *startangle, QList<QList<ushort>> *stopangle,
                     QList<QList<uchar>> *data,float *anglestep,int *stoprange);


};

#endif // PYTHONCORE_H
