#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>  //QSerialPort：提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>   //QSerialPortInfo：提供系统中存在的串口的信息
#include <QPainter>
#include <QTabWidget>
#include "draw_curve.h"
#include "osc_chart.h"
#include "QPixmap"
#include "QMouseEvent"
#include <QByteArray>
#include "mainwidget.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString Buf_ADC;
    QString Buf_Gro[3];
    QString Buf_Acc[3];
    QString Buf_Angle[3];
    Draw_Curve * drawWidget;
private slots:
    void on_LED_State_textChanged(const QString &a);
    void on_KEY_State_textChanged(const QString &a);

    void on_SendDataBtn_clicked();//发送数据

    void on_OpenPortBtn_clicked();//打开串口自动寻找port
    void readComData();//读取串口数据并且缓存下来
    void dataDeal();
    void on_AD_Value_textChanged(const QString &a);
    void Gro_And_Acc(QString a[], QString b[]);
    void Angle_Deal(QString a[]);
    void on_tabWidget_tabBarClicked();
    void system_Change(int ten_system);
    //void paintEvent(QPaintEvent* );
    void on_pushButton_clicked();
    void on_ReceivedDataBtn_clicked();

    void on_ClearTextBtn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QSerialPort serial;//声明串口类的指针
    QString Buf;
    QString Buf_LED;
    QString Buf_KEY;

    QPainter *paint;
    QWidget *pix;
    char sixteen_system[3] = {0};

    Draw_Curve *d;
    OSC_chart *OSC_Chart1;
    bool chart_is_created=false;
    bool My3D_is_created=false;

    MainWidget *mywidget;

    QString tempReceiveData;
    bool receivedDataFlag=0;
    bool My2D_is_created=false;
};

#endif // WIDGET_H
