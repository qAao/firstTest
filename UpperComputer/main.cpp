#include "widget.h"
#include <QApplication>
#include "draw_curve.h"
#include <QPainter>

#include "qtimer.h"
float mypitch=0;
float myyaw=0;
float myroll=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    //mytimer(d.ADCValue,w.Buf_ADC);
    return a.exec();
}
