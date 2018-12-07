#include "draw_curve.h"
#include <QTabWidget>
#include <QPainter>
#include "widget.h"
#include "qtimer.h"
#include "ui_widget.h"
Draw_Curve::Draw_Curve(QWidget *parent) :QWidget(parent)
{
  setAutoFillBackground(true);
  setPalette(QPalette(Qt::white));
  pix=new QPixmap(size());
  pix->fill(Qt::white);
  setMaximumSize(200,200);
  QTimer *timer = new QTimer(this); // 声明一个定时器
  connect(timer, SIGNAL(timeout()), this,SLOT(mytimer()));// 定时器超时信号连接到槽函数mytimer
  timer->start(10); // 启动定时器， 定时周期10ms
}
Draw_Curve::~Draw_Curve()
{

}
void Draw_Curve:: paintEvent(QPaintEvent* )
{
        int centerX=90;
        int centerY=90;

         paint=new QPainter;
         paint->begin(this);
         paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
         Move_Position();
         //factMove_X=Move_X;
         //factMove_Y=Move_Y;
         centerX=90-Move_X/50;
         centerY=90-Move_Y/50;
         if(centerX<10)
            { centerX=10;}
         if(centerX>190)
            {centerX=190;}
         if(centerY<10)
            {centerY=10;}
         if(centerY>190)
            {centerY=190;}
         paint->drawRect(centerX,centerY,20,20);
         paint->end();
}

void Draw_Curve:: mytimer()
{
    update();
}
void Draw_Curve:: Move_Position()
{
    int Now_Value_X=0;
    int Now_Value_Y=0;
    int Now_Value_Z=5;
    const int MySet=5000;
    if(MBuf_Gro[0]!='-')
    {
        if(MBuf_Gro[0]=='1')
        {
            MBuf_Gro[0]='0';
            Now_Value_X=-MBuf_Gro[0].toInt();
        }
        else
        {
            Now_Value_X=MBuf_Gro[0].toInt();
        }
        Move_X=Move_X+Now_Value_X+21;
    }
    MBuf_Gro[0]='-';
    if(MBuf_Gro[1]!='-')
    {
        if(MBuf_Gro[1]=='1')
        {
            MBuf_Gro[1]='0';
            Now_Value_Y=-MBuf_Gro[1].toInt();
        }
        else
        {
            Now_Value_Y=MBuf_Gro[1].toInt();
        }
        Move_Y=Move_Y+Now_Value_Y-15;
    }
    MBuf_Gro[1]='-';

    if(Move_X>MySet)
    {Move_X=MySet;}
    if(Move_X<-MySet)
    {Move_X=-MySet;}
    if(Move_Y>MySet)
    {Move_Y=MySet;}
    if(Move_Y<-MySet)
    {Move_Y=-MySet;}
}

