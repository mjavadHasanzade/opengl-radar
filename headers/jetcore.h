#ifndef JETCORE_H
#define JETCORE_H

#include <QObject>
#include <QVector>
#include <QColor>


class JetCore : public QObject
{
    Q_OBJECT
public:
    explicit JetCore(QObject *parent = nullptr);
    static QColor getJetColor(int value, int minValue, int maxValue);
signals:

private:


};

#endif // JETCORE_H
