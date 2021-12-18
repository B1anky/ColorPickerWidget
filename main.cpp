#include "ColorPicker.h"

#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ColorPicker colorPicker(nullptr, false);
    colorPicker.show();
    QObject::connect(&colorPicker, &ColorPickerWidget::ColorSelected, &app, [&app](QColor selectedColor){
        qDebug() << selectedColor;
    });
    return app.exec();
}
