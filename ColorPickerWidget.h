#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>

class QGridLayout;
typedef QList<QPair<QColor,QColor>> GradientList;

class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    ColorPicker(QWidget* parent = nullptr, bool closeOnPick = true);
    QColor InterpolateColor(QColor colorStart, QColor colorEnd, float percent);
    GradientList InitialialzeColorGradients();
    void CreateColorsButtons();
    void SetButtonColors(GradientList gradientList);

signals:
    void ColorSelected(QColor color);

protected:
    bool         m_closeOnPick;
    int          m_rows;
    int          m_columns;
    QGridLayout* m_colorGridLayout;
};

#endif // COLORPICKERWIDGET_H
