#ifndef OSC_CHART_H
#define OSC_CHART_H

//#include <QWidget>
#include "QLabel"
#include "QPainter"
#include "QMouseEvent"
#include "QWheelEvent"
#include "QList"

class OSC_chart : public QLabel
{
    Q_OBJECT

private:
    //是否隐藏指针label
    bool hide_pixmap=false;
    //坐标点显示
    bool viewPos=true;
    //坐标点分度值
    int Pots_multiple=10;
    int Pots_multiple_x=10;
    int Pots_multiple_y=10;
    //示波器放大倍数
    double OSC_multiple=50;
    double OSC_multiple_x=10;
    double OSC_multiple_y=10;
    //x，y轴虚线显示的条数（虚线间隔相等）
    int Step_x=10;
    int Step_y=5;

    QPixmap pixmap;//画布
    QPainter painter;//绘图

    QColor Color_Box[10]={Qt::black,Qt::red,Qt::green,Qt::blue,Qt::cyan,
                          Qt::magenta,Qt::yellow,Qt::gray,Qt::darkRed,Qt::darkBlue};


    void Draw_Wave(QList<int> chart_x,QList<int> chart_y);
    void Draw_Chart();
    void Draw_Cross_pointer(int x,int y);



public:
    //explicit OSC_chart(QWidget *parent = nullptr);
    OSC_chart(const QString & text, QWidget * parent = 0);
    ~OSC_chart(){}
    //外联函数 是否隐藏指针label
    void sethide(bool hide);
    void set_chart(int x, int y, int w, int h);
    void View_Chart();

    void Add_Line_Data(int Line_num,int pos_y);
    //鼠标事件
    QMouseEvent *externevent;

    QList<int> data_x[16];
    QList<int> data_y[16];
    double Set_Chart_Auto(void);



    int start_x=0,start_y=0,offset_x=0,offset_y=0,start_flag=0;
signals:
    void clicked(QMouseEvent *event);
    void moveing(QMouseEvent *event);
    void doubleClicked(QMouseEvent *event);

public slots:
    void slotClicked(QMouseEvent *event);
    void slotmoveing(QMouseEvent *event);
    void slotdoubleClicked(QMouseEvent *event);
protected:
    public:
        void mousePressEvent ( QMouseEvent * event ) ;
        void mouseMoveEvent( QMouseEvent * event ) ;
        void mouseDoubleClickEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent  *event);
        void mouseReleaseEvent(QMouseEvent  *event);
};

#endif // OSC_CHART_H
