#ifndef DRAW_CURVE_H
#define DRAW_CURVE_H

#include <QWidget>
#include <QPainter>

class Draw_Curve: public QWidget
{
  Q_OBJECT
public:
    explicit Draw_Curve(QWidget *parent = 0);
    ~Draw_Curve();
     QString ADCValue;
     QString MBuf_Gro[3];
     int Move_X=0;
     int Move_Y=0;
protected:
    void paintEvent(QPaintEvent*);
private slots:
    void mytimer();
    void Move_Position();

private:
    QPainter * paint;
    QPixmap *pix;


    int factMove_X=0;
    int factMove_Y=0;
};

#endif // DRAW_CURVE_H
