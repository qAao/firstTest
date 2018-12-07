#include "widget.h"
#include "ui_widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include <QTabWidget>
#include <QToolBar>
#include <QTimer>
#include "draw_curve.h"
#include "osc_chart.h"
extern float mypitch;
extern float myyaw;
extern float myroll;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //pix=ui->DrawCurve;

}

Widget::~Widget()
{
    delete ui;
}
//void Widget::on_textBrowser_windowIconTextChanged(const QString &iconText)
void Widget::on_LED_State_textChanged(const QString &a)
{
    ui->LED_State->clear();
    if(a[0]=='1')
    {
        ui->LED_State->append("LED_1:亮");//能够自动换行
    }
    else
    {
        ui->LED_State->append("LED_1:灭");
    }
    if(a[1]=='1')
    {
        ui->LED_State->append("LED_2:亮");//能够自动换行
    }
    else
    {
        ui->LED_State->append("LED_2:灭");
    }
    if(a[2]=='1')
    {
        ui->LED_State->append("LED_3:亮");//能够自动换行
    }
    else
    {
        ui->LED_State->append("LED_3:灭");
    }
    if(a[3]=='1')
    {
        ui->LED_State->append("LED_4:亮");//能够自动换行
    }
    else
    {
        ui->LED_State->append("LED_4:灭");
    }
    ui->LED_State->document()->setMaximumBlockCount(4);
   // ui->LED_State->setText(a);
}


void Widget::on_KEY_State_textChanged(const QString &a)
{

     ui->KEY_State->clear();

    if(a[0]=='1')
    {
        ui->KEY_State->append("KEY_1:ON");//能够自动换行
    }
    else
    {
        ui->KEY_State->append("KEY_1:OFF");
//        flag++;
    }
    if(a[1]=='1')
    {
        ui->KEY_State->append("KEY_2:ON");//能够自动换行
    }
    else
    {
        ui->KEY_State->append("KEY_2:OFF");
    }
    if(a[2]=='1')
    {
        ui->KEY_State->append("KEY_3:ON");//能够自动换行
    }
    else
    {
        ui->KEY_State->append("KEY_3:OFF");
    }
    if(a[3]=='1')
    {
        ui->KEY_State->append("KEY_4:ON");//能够自动换行
    }
    else
    {
        ui->KEY_State->append("KEY_4:OFF");
    }
//    ui->KEY_State->setText(a);
    ui->KEY_State->document()->setMaximumBlockCount(4);

}

void Widget::system_Change(int ten_system)//进制转换
{
    int temp_ten_system[100] = { 0 };
    int len = 0;
    int j = 0;

    while (ten_system)
    {
        temp_ten_system[len] = ten_system % 16;
        ten_system = ten_system /16;
        len++;
    }
    for (j= 1; j >=0; j--)
    {
        if (temp_ten_system[len - j - 1] < 10)
        {
            sixteen_system[j] = temp_ten_system[len-j-1]+'0';
        }
        else
        {
            sixteen_system[j] = 'A'+ temp_ten_system[len - j - 1]-10;
        }
    }
}
void Widget::on_SendDataBtn_clicked()
{
    int Sum=0;
   if(!(ui->OpenPortComName->isEnabled()))
   {
       QString CheckData="6M";
       QString SendData=ui->ToSendTextData->toPlainText().toLatin1();
       if(SendData.length()!=0)
       {
           serial.open(QIODevice::ReadWrite);
           CheckData+=SendData;
           const char *c_str2 = CheckData.toLatin1().data();
           for(int i=0;i<CheckData.length();i++)
           {
               Sum=Sum+c_str2[i];
           }
           Widget::system_Change(Sum);
           CheckData+=sixteen_system[0];
           CheckData+=sixteen_system[1];
           CheckData+="\n";
           int sendOkFlag=serial.write(CheckData.toLatin1());//以ASCII码的形式通过串口发送出去。
           ui->ReceivedAndSendDataText->insertPlainText(CheckData);
           if(sendOkFlag!=0)
           {
               //serial.close();//发送完就关闭串口
           }
       }
       else
       {
           ui->ReceivedAndSendDataText->insertPlainText("请输入数据!\n");
       }

   }
   else
   {
       ui->ReceivedAndSendDataText->insertPlainText("请打开串口!\n");
   }

}

void Widget::on_OpenPortBtn_clicked()//打开串口
{
    QString tempStringChangeToInt;
    int tempIntFromString=0;
    bool ok=0;
    if(ui->OpenPortComName->isEnabled())//允许使用
    {
        ui->OpenPortBtn->setText("关闭串口");		//按下“OpenPort”后，按键显示为“ClosePort”
        ui->OpenPortComName->setDisabled(true);	//按下“OpenPort”后，禁止再修改COM口
        serial.setPortName(ui->OpenPortComName->currentText());	//设置COM口

        tempStringChangeToInt=ui->OpenBaudRateValue->currentText();
        tempIntFromString=tempStringChangeToInt.toInt(&ok);
        serial.setBaudRate(tempIntFromString,QSerialPort::AllDirections);//设置波特率和读写方向

        tempStringChangeToInt=ui->OpenPortDataBit->currentText();
        tempIntFromString=tempStringChangeToInt.toInt(&ok);
        serial.setDataBits((QSerialPort::DataBits)tempIntFromString);		//数据位为8位

        serial.setFlowControl(QSerialPort::NoFlowControl);//无流控制

        tempStringChangeToInt=ui->OpenPortCheckBit->currentText();
        tempIntFromString=tempStringChangeToInt.toInt(&ok);
        serial.setParity((QSerialPort::Parity)tempIntFromString);	//校验位

        tempStringChangeToInt=ui->OpenPortStopBit->currentText();
        tempIntFromString=tempStringChangeToInt.toInt(&ok);
        serial.setStopBits((QSerialPort::StopBits)tempIntFromString);	//一位停止位 OpenPortDataBit

        serial.close();					//先关串口，再打开，可以保证串口不被其它函数占用。
    }
    else
    {
        ui->ReceivedDataBtn->setText("开始接收");
        ui->OpenPortBtn->setText("打开串口");		//按下“ClosePort”后，按键显示为“OpenPort”
        ui->OpenPortComName->setEnabled(true);		//按下“ClosePort”后，COM口可被修改
        serial.close();					//关串口
        if(My2D_is_created==true)
        {
           drawWidget->Move_X=0;
           drawWidget->Move_Y=0;
        }
    }
}
void Widget::dataDeal()
{
    int Position=-1;

    if(Buf[0]=='6'&&Buf[1]=='M')
    {
        Position=Buf.indexOf('L',0);
        if(Position!=-1)
        {
           for(int i=0;i<4;i++)
           {
              Buf_LED[i]=Buf[Position+i+1];
           }
           on_LED_State_textChanged(Buf_LED);
           Position=-1;
        }
        Position=Buf.indexOf('K',0);
        if(Position!=-1)
        {
           for(int i=0;i<4;i++)
           {
              Buf_KEY[i]=Buf[Position+i+1];
           }
           on_KEY_State_textChanged(Buf_KEY);
           Position=-1;
        }
        Position=Buf.indexOf('C',0);
        if(Position!=-1)
        {
           for(int i=0;i<6;i++)
           {
              Buf_ADC[i]=Buf[Position+i+1];
           }
           on_AD_Value_textChanged(Buf_ADC);
           //d->ADCValue=Buf_ADC;
           Position=-1;
        }
        Position=Buf.indexOf('G',0);
        if(Position!=-1)
        {
           for(int i=0;i<6;i++)
           {
              Buf_Gro[0][i]=Buf[Position+1+i];
              Buf_Gro[1][i]=Buf[Position+7+i];
              Buf_Gro[2][i]=Buf[Position+13+i];
           }
           Position=-1;
        }
        Position=Buf.indexOf('A',0);
        if(Position!=-1)
        {
           for(int i=0;i<6;i++)
           {
              Buf_Acc[0][i]=Buf[Position+1+i];
              Buf_Acc[1][i]=Buf[Position+7+i];
              Buf_Acc[2][i]=Buf[Position+13+i];
           }
           Gro_And_Acc(Buf_Gro,Buf_Acc);
           Position=-1;
        }
        Position=Buf.indexOf('T',0);
        if(Position!=-1)
        {
           for(int i=0;i<6;i++)
           {
              Buf_Angle[0][i]=Buf[Position+1+i];//pitch
              Buf_Angle[1][i]=Buf[Position+7+i];//yaw
              Buf_Angle[2][i]=Buf[Position+13+i];//roll
           }
           Angle_Deal(Buf_Angle);
           Position=-1;
        }
        if(chart_is_created==true)//绘制曲线
        {
            int Pos_Y=Buf_ADC.toInt()/10;
             OSC_Chart1->Add_Line_Data(1,Pos_Y);
             OSC_Chart1->View_Chart();
        }
        if(My2D_is_created==true)
        {
           drawWidget->MBuf_Gro[0]=this->Buf_Gro[0];
           drawWidget->MBuf_Gro[1]=this->Buf_Gro[1];
           drawWidget->MBuf_Gro[2]=this->Buf_Gro[2];
        }

    }
}
void Widget::readComData()
{
    if(receivedDataFlag==1)
    {
        QByteArray temp=serial.readAll();//在缓冲区中读一个byte
        int startTempPosition=0;
        int endTempPosition=0;
        int okFlag=0;
        if(!temp.isEmpty())
        {
              tempReceiveData+=temp;//保留当前数据
              startTempPosition=tempReceiveData.indexOf('M');
              if(startTempPosition!=-1&&startTempPosition!=0&&tempReceiveData[startTempPosition-1]=='6')
              {
                  endTempPosition=tempReceiveData.indexOf('\n');
                  if(endTempPosition!=-1)
                  {
                      for(auto item=tempReceiveData.begin()+startTempPosition-1;item!=tempReceiveData.begin()+endTempPosition+1;item++)
                      {
                         Buf+=*item;
                      }
                      okFlag=1;
                      QString myTempStr;
                      for(auto item=tempReceiveData.begin()+endTempPosition+1;item!=tempReceiveData.end();item++)
                      {
                         myTempStr+=*item;
                      }
                      tempReceiveData.clear();
                      tempReceiveData=myTempStr;
                  }
              }
              if(okFlag==1)
              {
                  ui->ReceivedAndSendDataText->insertPlainText(" ");
                  ui->ReceivedAndSendDataText->insertPlainText(Buf);

                  dataDeal();//数据相应的处理
                  Buf.clear();
              }
        }
    }

}

void Widget::on_AD_Value_textChanged(const QString &a)
{
    ui->AD_Value->setText(a);
}
void Widget::Gro_And_Acc( QString a[], QString b[])
{
    for(int i=0;i<3;i++)
    {
        if(a[i][0]=='1')
        {
          a[i][0]='-';
        }
        else
        {
          a[i][0]=' ';
        }
        if(b[i][0]=='1')
        {
          b[i][0]='-';
        }
        else
        {
          b[i][0]=' ';
        }
    }

    ui->Gro_X_Edit->setText(a[0]);
    ui->Gro_Y_Edit->setText(a[1]);
    ui->Gro_Z_Edit->setText(a[2]);
    ui->Acc_X_Edit->setText(b[0]);
    ui->Acc_Y_Edit->setText(b[1]);
    ui->Acc_Z_Edit->setText(b[2]);
    if(chart_is_created==true)//绘制曲线
    {
        int Pos_Y=a[0].toInt()/10;
        OSC_Chart1->Add_Line_Data(2,Pos_Y);
        OSC_Chart1->View_Chart();

        Pos_Y=a[1].toInt()/10;
        OSC_Chart1->Add_Line_Data(3,Pos_Y);
        OSC_Chart1->View_Chart();

        Pos_Y=a[2].toInt()/10;
        OSC_Chart1->Add_Line_Data(4,Pos_Y);
        OSC_Chart1->View_Chart();

        Pos_Y=b[0].toInt()/10;
        OSC_Chart1->Add_Line_Data(5,Pos_Y);
        OSC_Chart1->View_Chart();

        Pos_Y=b[1].toInt()/10;
        OSC_Chart1->Add_Line_Data(6,Pos_Y);
        OSC_Chart1->View_Chart();
        Pos_Y=b[2].toInt()/10;
        OSC_Chart1->Add_Line_Data(7,Pos_Y);
        OSC_Chart1->View_Chart();
    }
}

void Widget::on_tabWidget_tabBarClicked()
{


    if(chart_is_created==false)
    {
       // ui->tabWidget->setCurrentWidget(ui->DrawCurve);
        OSC_Chart1 = new OSC_chart("painter",ui->label_OSC);
        OSC_Chart1->sethide(true);
        OSC_Chart1->set_chart(0,0,600,300);
        OSC_Chart1->show();
        chart_is_created=true;
    }
    if(My3D_is_created==false)
    {
       mywidget =new MainWidget(ui->openGLWidget_3D);
       mywidget->setGeometry(40,-15,220,220);
       My3D_is_created=true;
    }
    if(My2D_is_created==false)
    {
       drawWidget =new Draw_Curve(ui->show_2D);
       drawWidget->setGeometry(0,0,200,200);
       My2D_is_created=true;
    }

}
//void Widget:: paintEvent(QPaintEvent* )
// {
//     paint=new QPainter;
//     paint->begin(this);
//     paint->setPen(QPen(Qt::blue,4,Qt::DashLine));//设置画笔形式
//     paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
//     paint->drawRect(20,20,20,20);
//     paint->end();
//    // update();
//    // paint->draw(QPoint(0,0),*pix);
// }



void Widget::on_pushButton_clicked()
{
    if(My3D_is_created==true)
    {
        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        QSurfaceFormat::setDefaultFormat(format);

    #ifndef QT_NO_OPENGL

        mywidget->show();
    #else
        QLabel note("OpenGL Support required");
        note.show();
    #endif
    }
}
void Widget:: Angle_Deal(QString a[])
{
    if(a[0][0]=='0')
    {
      mypitch= (a[0].toInt())/10.0;
      a[0][0]=' ';
    }
    else
    {
      a[0][0]='0';
      mypitch=-a[0].toInt()/10.0;
      a[0][0]='-';
    }
    if(a[1][0]=='0')
    {
      myyaw= (a[1].toInt())/10.0;
       a[1][0]=' ';
    }
    else
    {
      a[1][0]='0';
      myyaw= -a[1].toInt()/10.0;
      a[1][0]='-';
    }
    if(a[2][0]=='0')
    {
      myroll= (a[2].toInt())/10.0;
      a[2][0]=' ';
    }
    else
    {
      a[2][0]='0';
      myroll=- (a[2].toInt()/10.0);
      a[2][0]='-';
    }
    ui->Angle_Pitch->setText(a[0]);
    ui->Angle_Roll->setText(a[1]);
    ui->Angle_Yaw->setText(a[2]);
}


void Widget::on_ReceivedDataBtn_clicked()
{
    if(receivedDataFlag==0&&(!ui->OpenPortComName->isEnabled())&&serial.open(QIODevice::ReadWrite))		//以可读写的方式打开串口
    {
        receivedDataFlag=1;
        ui->ReceivedDataBtn->setText("停止接收");
        connect(&serial,SIGNAL(readyRead()),this,SLOT(readComData()));	//把串口的readyRead()信号绑定到read_Com()这个槽函数上
    }
    else
    {
        serial.close();
        receivedDataFlag=0;
        ui->ReceivedDataBtn->setText("开始接收");
    }
}


void Widget::on_ClearTextBtn_clicked()
{
    ui->ReceivedAndSendDataText->clear();
}

void Widget::on_pushButton_2_clicked()
{
    if(My2D_is_created)
    {
        drawWidget->show();
    }

}
