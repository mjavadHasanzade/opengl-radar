#include "jetcore.h"

JetCore::JetCore(QObject *parent)
    : QObject{parent}
{

}

QVector<QColor> jetColors = {
    QColor(51, 128, 255),// Dark Blue
    QColor(0, 0, 255),// Blue
    QColor(0, 128, 255),// Light Blue
    QColor(0, 255, 255),// Cyan
    QColor(128, 255, 20),// Light Cyan
    QColor(128, 180, 20),// Green
    QColor(128, 255, 0),// Yellow-Green
    QColor(255, 255, 0),// Yellow
    QColor(255, 255, 128),// Light Yellow
    QColor(255, 128, 0),// Orange
    QColor(255, 192, 0),// Light Orange
    QColor(255, 64, 0),// Red-Orange
    QColor(255, 0, 0),// Red
    QColor(255, 0, 128),// Bright Red
};

QColor JetCore::getJetColor(int value, int minValue, int maxValue)
{
    // Normalize the value between 0 and 1
    double normalizedValue = static_cast<double>(value - minValue) / (maxValue - minValue);

    // Calculate the index in the Jet color map
    int numColors = jetColors.size();
    int index = qRound(normalizedValue * (numColors - 1));

    // Retrieve the corresponding color from the lookup table
    QColor color = jetColors[index];

    return color;
}
