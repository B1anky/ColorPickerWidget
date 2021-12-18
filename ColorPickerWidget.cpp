#include "ColorPickerWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QPair>

ColorPickerWidget::ColorPicker(QWidget* parent, bool closeOnPick)
    : QWidget          (parent),
      m_closeOnPick    (closeOnPick),
      m_rows           (10),
      m_columns        (0),
      m_colorGridLayout(new QGridLayout)
{
    QPushButton* defaultColorButton = new QPushButton("Default Color");
    QPushButton* moreColorsButton   = new QPushButton("More Colors...");
    QVBoxLayout* vBoxLayout         = new QVBoxLayout;
    setLayout(vBoxLayout);

    vBoxLayout->addWidget(defaultColorButton);
    vBoxLayout->addLayout(m_colorGridLayout);
    vBoxLayout->addWidget(moreColorsButton);

    defaultColorButton->setShortcut(tr("Alt+D"));
    defaultColorButton->setShortcut(tr("Alt+M"));

    GradientList colorGradients = InitialialzeColorGradients();
    m_columns = colorGradients.size();
    CreateColorsButtons();
    SetButtonColors(colorGradients);
}

QColor ColorPickerWidget::InterpolateColor(QColor colorStart, QColor colorEnd, float percent)
{
    double resultRedF   = colorStart.redF()   + percent * (colorEnd.redF()   - colorStart.redF());
    double resultGreenF = colorStart.greenF() + percent * (colorEnd.greenF() - colorStart.greenF());
    double resultBlueF  = colorStart.blueF()  + percent * (colorEnd.blueF()  - colorStart.blueF());
    QColor interpolatedColor;
    interpolatedColor.setRedF(resultRedF);
    interpolatedColor.setGreenF(resultGreenF);
    interpolatedColor.setBlueF(resultBlueF);
    return interpolatedColor;
}

GradientList ColorPickerWidget::InitialialzeColorGradients()
{
    GradientList gradientList;
    gradientList.push_back(qMakePair(Qt::white,             Qt::black));             // white         -> black
    gradientList.push_back(qMakePair(QColor( 93, 218, 255), QColor( 20, 113, 145))); // cyan          -> blue green
    gradientList.push_back(qMakePair(QColor(129, 182, 255), QColor( 28,  51, 135))); // light blue    -> dark blue
    gradientList.push_back(qMakePair(QColor(186,   0, 255), QColor( 65,   0, 125))); // magenta       -> violet
    gradientList.push_back(qMakePair(QColor(229,   0, 255), QColor(106,   0, 129))); // pink          -> wine
    gradientList.push_back(qMakePair(QColor(241,  79, 154), QColor(123,   0,  61))); // bright orange -> brown
    gradientList.push_back(qMakePair(QColor(255, 122, 116), QColor(173,   0,   0))); // orange        -> dark red
    gradientList.push_back(qMakePair(QColor(251, 205,  95), QColor(167,  69,   0))); // light orange  -> dark orange
    gradientList.push_back(qMakePair(QColor(245, 255, 125), QColor(147, 150,   0))); // light yellow  -> gray
    gradientList.push_back(qMakePair(QColor(150, 238, 125), QColor( 50, 135,  18))); // lime green    -> dark green
    return gradientList;
}

void ColorPickerWidget::CreateColorsButtons()
{
    for(int row = 0; row < m_rows; ++row){
        for(int column = 0; column < m_columns; ++column){
            QPushButton* colorButton = new QPushButton("");
            m_colorGridLayout->addWidget(colorButton, row, column);
            connect(colorButton, &QPushButton::clicked, this, [this, colorButton](){
                emit ColorSelected(colorButton->palette().button().color());
                if(m_closeOnPick){
                    close();
                }
            }, Qt::DirectConnection);
        }
    }
}

void ColorPickerWidget::SetButtonColors(GradientList gradientList)
{
    QColor colorStart;
    QColor colorEnd;
    for(int column = 0; column < gradientList.size(); ++column){
        float percent = 0.0f;
        colorStart = gradientList.at(column).first;
        colorEnd   = gradientList.at(column).second;
        for(int row = 0; row < m_rows; ++row){
            QPushButton* colorButton = qobject_cast<QPushButton*>(m_colorGridLayout->itemAtPosition(row, column)->widget());
            colorButton->setFixedSize(QSize(15, 15));
            QColor interpolatedColor = InterpolateColor(colorStart, colorEnd, percent);
            colorButton->setStyleSheet(QString("QPushButton{"
                                       "background-color: rgb(%0,%1,%2);"
                                       "border : none;"
                                       "}").arg(interpolatedColor.red()).arg(interpolatedColor.green()).arg(interpolatedColor.blue()));
            percent += 1.0f / (m_rows - 1);
        }
    }
}

