#include "headers/pythoncore.h"

PythonCore::PythonCore(QString fileName,QString execPath,QObject *parent)
    : QObject{parent}, mFileName(fileName), mExecPath(execPath)
{
    Py_Initialize();

    loadVolData(mFileName,mExecPath,
                &rays,&bins,&sliceCount,&startAngle,&stopAngle,&data,&angleStep,&stopRange);
}

void PythonCore::loadVolData(QString fileName, QString execPath, QList<int> *rayS, QList<int> *binS,
                             int *slicecount, QList<QList<ushort> > *startangle, QList<QList<ushort> > *stopangle,
                             QList<QList<uchar> > *data, float *anglestep, int *stoprange)
{
    QElapsedTimer timer;
    timer.start();

    //clear old data
    rayS->clear();
    binS->clear();
    *slicecount=0;
    *anglestep=0;
    *stoprange=0;
    startangle->clear();
    stopangle->clear();
    data->clear();


    PyObject* pSysPath = PySys_GetObject("path");
    PyList_Append(pSysPath, PyUnicode_FromString(execPath.toUtf8().constData()));

    pModule = PyImport_Import( PyUnicode_FromString("extract-vol"));

    if (!pModule) {
        PyErr_Print();
        PyErr_Clear();  // Clear the Python error indicator

        // Retrieve the error message from the Python error stack
        PyObject* pType;
        PyObject* pValue;
        PyObject* pTraceback;
        PyErr_Fetch(&pType, &pValue, &pTraceback);

        // Convert the exception to a string
        PyObject* pStrValue = PyObject_Str(pValue);
        const char* valueStr = PyUnicode_AsUTF8(pStrValue);

        // Log or handle the error
        qDebug() << "Python error:" << (QString(valueStr));

        // Cleanup
        Py_XDECREF(pType);
        Py_XDECREF(pValue);
        Py_XDECREF(pTraceback);
        Py_DECREF(pStrValue);

        return;
    }



    PyObject* jsonFunc = PyObject_GetAttrString(pModule, "get_json_file");
    if (!jsonFunc || !PyCallable_Check(jsonFunc)) {
        qDebug() << "Failed to get function or function is not callable";
        return ;
    }

    PyObject* pArgs=PyUnicode_FromString(fileName.toUtf8().constData());
    PyObject* jsonResult = PyObject_CallFunctionObjArgs(jsonFunc, pArgs, nullptr);

    if (jsonResult != nullptr) {
        QByteArray jsonData = PyUnicode_AsUTF8(jsonResult);
        QString jsonString(jsonData);

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());


        foreach (QJsonValue slice, jsonDocument["scan"]["slice"].toArray()) {

            binS->append(slice["slicedata"]["rawdata"]["@bins"].toString().toInt());
            rayS->append(slice["slicedata"]["rawdata"]["@rays"].toString().toInt());
            *slicecount+=1;

            QList<ushort> startangleArr;
            QList<ushort> stopangleArr;

            if(slice["slicedata"]["rayinfo"].isArray()){


                foreach (QJsonValue item, slice["slicedata"]["rayinfo"][0]["data"].toArray()) {
                    startangleArr.append(item.toInt());
                }

                foreach (QJsonValue item, slice["slicedata"]["rayinfo"][1]["data"].toArray()) {
                    stopangleArr.append(item.toInt());
                }

            }else{

                if(slice["slicedata"]["rayinfo"]["@refid"].toString()=="startangle")
                    foreach (QJsonValue item, slice["slicedata"]["rayinfo"]["data"].toArray()) {
                        startangleArr.append(item.toInt());
                    }
                else
                    foreach (QJsonValue item, slice["slicedata"]["rayinfo"]["data"].toArray()) {
                        stopangleArr.append(item.toInt());
                    }


            }

            startangle->append(startangleArr);
            stopangle->append(stopangleArr);

            QList <uchar> elevation;

            foreach (auto ray, slice["slicedata"]["rawdata"]["data"].toArray()) {
                foreach (auto bin, ray.toArray()) {
                    elevation.append(bin.toInt());
                }
            }
            data->append(elevation);
        }

        *anglestep=(jsonDocument["scan"]["pargroup"]["anglestep"].toString()).toFloat();
        *stoprange=(jsonDocument["scan"]["pargroup"]["stoprange"].toString()).toInt();

        Py_DECREF(jsonResult);
    } else {
        // Error occurred, retrieve error information
        PyErr_Print();
    }

    Py_DECREF(jsonFunc);

    qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
    Py_Finalize();

}
