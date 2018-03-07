#include "awosworkstationmin.h"
#include <QDebug>
#include <QPolygon>
#include <QFont>
#include <QLinearGradient>

void WorkStation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QString timeStr;
    qDebug()<<"main width:"<<width()<<"main height:"<<height();
    int left = -width() / 2;
    int top = -height() / 2;
    int right = width() / 2;
    int buttom = height() / 2;
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(right,buttom);
    painter.setPen(Qt::NoPen);

    //画边线
    painter.save();
    painter.setPen(QColor("#0000AA"));
    painter.drawLine(left,top + 1, right,top + 1);
    painter.setPen(QColor("#F4A460"));
    painter.drawLine(left,top + 1, left,buttom + 1);
    painter.drawLine(left,buttom, right,buttom);
    painter.drawLine(right,top + 1, right,buttom + 1);
    painter.restore();

    //画标题栏
    painter.save();
    QLinearGradient gradT(0,top,0,height());
    gradT.setColorAt(0,QColor("#4F4F4F"));
    gradT.setColorAt(0.02,QColor("#4F94CD"));
    QRect rectT(left,top,width(),height());
    painter.setBrush(gradT);
    painter.drawRect(rectT);
    painter.restore();

    //画界面控制按钮
    painter.save();

    //4画按钮形状
    QPen drawPen;
    drawPen.setWidth(3);
    drawPen.setColor(Qt::white);
    painter.setPen(drawPen);
    QFont user_font;
    user_font.setPointSize(10);
    painter.setFont(user_font);

    // 用户
    painter.drawText(left,top + 2,100,30,Qt::AlignCenter,_m_user_type+"端");

    // 影藏
    painter.drawLine(right - 84,top + 15,right - 70,top + 15);

    // 关闭
    painter.drawLine(right - 24,top + 9,right - 12,top + 21);
    painter.drawLine(right - 24,top + 21,right - 12,top + 9);

    // 最大小化
    if(!m_fullScreen){
        painter.drawRect(right - 54,top + 9,12,12);
    }
    else{
        painter.drawRect(right - 52,top + 11,8,8);
        painter.drawRect(right - 48,top + 8,8,8);
    }
    painter.restore();

    //画身体背景
    painter.save();
    painter.setBrush(QColor("#D9D9D9"));
    QRect bodyRect(left + 2, top + 30,width() - 4 ,height() - 32);
    painter.drawRect(bodyRect);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor("#F7F7F7"));
    painter.setPen(pen);

    //画区分线
    painter.drawLine(left + 3, top + 30,right - 3 ,top + 30);
    painter.drawLine(left + 3, top + 30,left + 3,buttom - 3);
    painter.restore();

    //画时间栏
    painter.save();
    QLinearGradient gradH(0,top + 31,0,top + 71);
    gradH.setColorAt(0,QColor("#4A708B"));
    gradH.setColorAt(1,QColor("#00688B"));
    QRect rectH(left + 4, top  + 31,width() - 8,42);
    painter.setBrush(gradH);
    painter.drawRect(rectH);
    painter.restore();

    //画时间
    painter.save();
    painter.setPen(QColor("#F0F8FF"));
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(19);
    font.setFamily("微软雅黑");
    painter.setFont(font);
    painter.drawText(left + 10,top  + 30,60,40
                     ,Qt::AlignCenter ,"UTC ");
    painter.drawText(-width() / 4  -158,top  + 30,90,40
                     ,Qt::AlignCenter ,"北京时间 ");
    font.setPixelSize(16);
    font.setBold(false);
    painter.setFont(font);
    painter.drawText(260,top  + 30,420,40
                     ,Qt::AlignCenter
                     ,"北京视程科技有限公司 Vrange");
    painter.setFont(font);
    font.setPixelSize(19);
    painter.setFont(font);
    timeStr = QDateTime::currentDateTimeUtc().toString("HH:mm") + " Z";
    painter.drawText(left + 60,top  + 30,280,32
                     ,Qt::AlignBottom | Qt::AlignLeft,timeStr);
    timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    painter.drawText(left + (right - 4)/ 2 - 66,top  + 30,280,32
                     ,Qt::AlignBottom | Qt::AlignLeft,timeStr);
    painter.restore();

//    // Press partment
//    PressDraw(&painter);

//    // scale close buttom
//    scaleButtomClose(&painter);

    // scale open buttom
    scaleButtomOpen(&painter);

    //画左边功能按钮
    painter.save();
    painter.setPen(QColor("#96CDCD"));
    QLinearGradient gradLB1(1,top + 80,1,top + 165);
    if(!m_firstFunction){
        gradLB1.setColorAt(1,QColor("#00688B"));
    }
    else{
        gradLB1.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradLB1);
    painter.drawRoundedRect(left + 8, top + 80,70,80,4,4);
     ///==========
    QLinearGradient gradLB2(1,top + 170,1,top + 250);
    if(!m_secondFunction){
        gradLB2.setColorAt(1,QColor("#00688B"));
    }
    else{
        gradLB2.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradLB2);
    painter.drawRoundedRect(left + 8, top + 170,70,80,4,4);
     ///==========
    QLinearGradient gradLB3(1,top + 260,1,top + 340);
    if(!m_thirdFunction){
        gradLB3.setColorAt(1,QColor("#00688B"));
    }
    else{
        gradLB3.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradLB3);
    painter.drawRoundedRect(left + 8, top + 260,70,80,4,4);
     ///==========
    QLinearGradient gradLB4(1,top + 350,1,top + 430);
    if(!m_fourFunction){
        gradLB4.setColorAt(1,QColor("#00688B"));
    }
    else{
        gradLB4.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradLB4);
    painter.drawRoundedRect(left + 8, top + 350,70,80,4,4);
    ///==========
    painter.setPen(Qt::white);
    painter.drawText(left + 8, top + 74,70,80
                     ,Qt::AlignHCenter | Qt::AlignBottom,"数据");
    painter.drawText(left + 8, top + 164,70,80
                     ,Qt::AlignHCenter | Qt::AlignBottom,"电报");
    painter.drawText(left + 8, top + 254,70,80
                     ,Qt::AlignHCenter | Qt::AlignBottom,"系统");
    painter.drawText(left + 8, top + 344,70,80
                     ,Qt::AlignHCenter | Qt::AlignBottom,"ATC");
    painter.restore();

    if(funcMap[1] == true){
        //main user
        showOrCloseMainWaringContrl(true);

        //other contrls
        showOrCloseTelegramCFG(false);
        showOrCloseAFTNContrls(false);
        showOrCloseLocaCFGContrl(false);
        showOrCloseMetarContrls(false);
        showOrCloseSpaciContrls(false);
        showOrCloseMetarReportContrl(false);
        showOrCloseSpacialReportContrl(false);

        // deveice
        showOrCloseDeveiceContrl(false);
        showOrCloseInfomationContrl(false);
        showOrCloseLogContrl(false);
        showOrCloseWaringContrl(false);

        // atc
        showOrCloseAtcMetarReport(false);
        showOrCloseAtcMain(false);

        //画主展示界面框线
        painter.save();
        painter.setPen(QPen(Qt::gray,2));
        painter.drawRect(left + 93,top + 75,width() - 100,height() - 79);
        painter.restore();

        //画跑道线框
        painter.save();
        painter.setPen(QPen(Qt::gray,1));
        painter.drawRoundedRect(left + 97,top + (height() -155) * 5 / 12  + 77
                                ,188,(height() - 155) / 6 - 24,4,4);//调整 - 20 高 -20
        painter.drawRoundedRect(left + 288,top + (height() -155) * 5 / 12  + 77
                                ,(width() - 106) - 383,(height() - 155) / 6 - 24,4,4);
        painter.drawRoundedRect(left + width() - 199,top + (height() - 155) * 5 / 12  + 77
                                ,188,(height() - 155) / 6 - 24,4,4);
        painter.restore();

        //告警字样
        painter.save();
        QFont waringFont;
        waringFont.setBold(true);
        waringFont.setPixelSize(18);
        painter.setFont(waringFont);
        painter.setPen(QColor("#919191"));
        //调整 - 10 // H - 5
        painter.drawText(left + 7,buttom - 74,80,30
                         ,Qt::AlignCenter,"告警!");
        painter.restore();
    }
    else if(funcMap[2] == true){
        //main user
        showOrCloseMainWaringContrl(false);

        // deveice
        showOrCloseDeveiceContrl(false);
        showOrCloseInfomationContrl(false);
        showOrCloseLogContrl(false);
        showOrCloseWaringContrl(false);

        //atc
        showOrCloseAtcMetarReport(false);
        showOrCloseAtcMain(false);

        // AFTN
        showOrCloseAFTNContrls(false);

        // loca CFg
        showOrCloseLocaCFGContrl(false);

        //画子界面框线
        painter.save();
        painter.setPen(QPen(Qt::gray,2));
        painter.drawRect(left + 93,top + 75,width() - 94 - 4 - 4 + 2,height() - 75 - 4);
        painter.setPen(QPen(QColor("#4A708B"),2));
        painter.drawLine(left + 98 /*+ 97*/,top + 113,left + width() - 10,top + 113);
        painter.restore();

        //画按钮
        painter.save();
        painter.setPen(Qt::NoPen);
        QPoint MetStartPoint(0,top + 75);
        QPoint MetEndPoint(0,top + 115);
        QLinearGradient gradMetStart(MetStartPoint ,MetEndPoint);
        QLinearGradient gradMetEnd(MetStartPoint ,MetEndPoint);
        gradMetStart.setColorAt(0,QColor("#4A708B"));
        gradMetStart.setColorAt(1,QColor("#00688B"));
        gradMetEnd.setColorAt(0,QColor("#CAE1FF"));
        gradMetEnd.setColorAt(1,QColor("#B0E0E6"));

        //1
        if(!m_metOne){
            painter.setBrush(gradMetStart);
        }
        else{
            painter.setBrush(gradMetEnd);
        }
        painter.drawRoundedRect(left + 94 + 2,top + 79,100,30,3,3);

        //2
        if(!m_metTwo){
            painter.setBrush(gradMetStart);
        }
        else{
            painter.setBrush(gradMetEnd);
        }
        painter.drawRoundedRect(left + 94 + 2 + 101,top + 79,100 + 60,30,3,3);

        //3
        if(!m_metThree){
            painter.setBrush(gradMetStart);
        }
        else{
            painter.setBrush(gradMetEnd);
        }
        painter.drawRoundedRect(left + 94 + 2 + 262,top + 79,100 + 40,30,3,3);

        //4
        if(!m_metFour){
            painter.setBrush(gradMetStart);

        }
        else{
            painter.setBrush(gradMetEnd);
        }
        painter.drawRoundedRect(left + 94 + 2 + 403,top + 79,100 + 10,30,3,3);

        //5
        if(!m_metFive){
            painter.setBrush(gradMetStart);
        }
        else{
            painter.setBrush(gradMetEnd);
        }
        painter.drawRoundedRect(left + 94 + 2 + 514,top + 79,100,30,3,3);

        //绘制字体
        painter.setPen(Qt::white);
        QFont metarFont = painter.font();
        metarFont.setPixelSize(14);
        painter.setFont(metarFont);
        painter.drawText(left + 94 + 2,top + 79,100,30
                         ,Qt::AlignCenter,"METAR 报告");
        painter.drawText(left + 94 + 2 + 101,top + 79,100 + 60,30
                         ,Qt::AlignCenter,"SPACI 报告\\更正报告");
        painter.drawText(left + 94 + 2 + 262,top + 79,100 + 40,30
                         ,Qt::AlignCenter,"MET REPORT 报告");
        painter.drawText(left + 94 + 2 + 403,top + 79,100 + 10,30
                         ,Qt::AlignCenter,"SPACIAL 报告");
        painter.drawText(left + 94 + 2 + 514,top + 79,100,30
                         ,Qt::AlignCenter,"配置");
        painter.restore();

        int sHeight = height() - 131 - 100; // V drection 4 * 4 - 100
        int sWidth = width() - 112; // H drection 3 * 4

        if(m_metar[1]){      // metar
            showOrCloseMetarContrls(true);
            showOrCloseSpaciContrls(false);
            showOrCloseMetarReportContrl(false);
            showOrCloseSpacialReportContrl(false);
            showOrCloseTelegramCFG(false);

            //qDebug()<<"draw one";
            painter.setPen(Qt::gray);
            painter.drawRect(left + 97,top + 115,sWidth * 4 / 8,sHeight - 120 - 6);

            // metar context show controls
            painter.setPen(QPen(Qt::gray,2));
            painter.setBrush(QColor("#D9D9D9"));
            painter.drawRoundedRect(left + 97,top + 115 + sHeight - 120 - 3
                                    ,sWidth,(sHeight - 120) / 13,4,4);
            painter.drawRoundedRect(left + 97,top + 27 + sHeight,sWidth,98,6,6);
            painter.drawRoundedRect(left + 97,top + 27 + sHeight + 102,sWidth
                                    ,height() - (27 + sHeight + 98) - 12,6,6);

            // metar send buttons controls
            //1 . update 更新
            QLinearGradient gradMetSend1(left + 93,top + 75,left + 93,top + 115);
            if(!m_metUpdate){
                gradMetSend1.setColorAt(0,QColor("#4A708B"));
                gradMetSend1.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend1.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend1.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend1);
            painter.drawRoundRect(left + sWidth * 4 / 5 + 122
                                  ,top + 32 + sHeight
                                  ,sWidth/10 - 12
                                  ,26,6,6);
            // cavok check
            if(!m_cavokCheck){
                gradMetSend1.setColorAt(0,QColor("#4A708B"));
                gradMetSend1.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend1.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend1.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend1);
            painter.drawRoundRect( left + sWidth * 9 / 10 + 109
                                   ,top + 31 + sHeight + 1
                                   ,sWidth/10 - 12
                                   ,26,6,6);

            //2 . modify 修改
            QLinearGradient gradMetSend2(left + 93,top + 75,left + 93,top + 115);
            if(!m_metModify){
                gradMetSend2.setColorAt(0,QColor("#4A708B"));
                gradMetSend2.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend2.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend2.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend2);
            painter.drawRoundRect(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                  ,top + 61 + sHeight + 2
                                  ,(sWidth - 70)/ 5 - 10,26,6,6);

            //3 . send 发送
            QLinearGradient gradMetSend3(left + 93,top + 75,left + 93,top + 115);
            if(!m_metSend){
                gradMetSend3.setColorAt(0,QColor("#4A708B"));
                gradMetSend3.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend3.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend3.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend3);
            painter.drawRoundRect(left + sWidth * 9 / 10 + 112
                                  ,top + sHeight + 94
                                  ,sWidth / 10 - 14
                                  ,26,3,3);
            //2.5 trend requery
            if(!m_metTrend){
                gradMetSend3.setColorAt(0,QColor("#4A708B"));
                gradMetSend3.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend3.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend3.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend3);
            painter.drawRoundRect(left + sWidth * 4 / 5 + 122
                                  ,top + sHeight + 94
                                  ,sWidth / 10 - 13
                                  ,26,3,3);

            //4 metar 报确认
            QLinearGradient gradMetSend4(0,buttom - 102,0,buttom - 8);
            if(!m_metarComfire){
                gradMetSend4.setColorAt(0,QColor("#4A708B"));
                gradMetSend4.setColorAt(1,QColor("#00688B"));
            }
            else{
                gradMetSend4.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend4.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend4);
            painter.drawRoundRect(left + 7 + (width() - 112) / 2
                                  ,buttom - 102,90,94,3,3);

            // spacial 报确认
            QLinearGradient gradMetSend5(0,buttom - 102,0,buttom - 8);
            if(!m_spacilComfire){
                gradMetSend5.setColorAt(0,QColor("#4A708B"));
                gradMetSend5.setColorAt(1,QColor("#00688B"));
            }
            else{
                gradMetSend5.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend5.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend5);
            painter.drawRoundRect(left + 7 + (width() - 112)
                                  ,buttom - 102,90,94,3,3);

            //metar show control titles
            painter.setPen(Qt::black);
            painter.drawText(left + 110,top + 142 + (sHeight - 120) * 12 / 13,60
                             ,(sHeight - 120) / 13,Qt::AlignCenter,"等级");
            painter.drawText(left + sWidth * 1.5 / 8 + 117
                             ,top + 142 + (sHeight - 120) * 12 / 13
                             ,60,(sHeight - 120) / 13,Qt::AlignCenter,"接收地址");
            painter.drawText(left + 100,top + 27 + sHeight,60,98,Qt::AlignCenter,"METAR");
            painter.setPen(Qt::white);
            painter.drawText(left + 7 + (width() - 112) / 2,buttom - 102,90,94
                             ,Qt::AlignCenter,"METAR确认");
            painter.drawText(left + 7 + (width() - 112),buttom - 102,90,94
                             ,Qt::AlignCenter,"SPACIL确认");
            painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                             ,top + 31 + sHeight + 1
                             ,sWidth / 10 - 13
                             ,26
                             ,Qt::AlignCenter,"创建METAR");
            QString cavokString;
            if(!m_cavok){
                cavokString = "应用CAVOK";
            }
            else{
                cavokString = "取消CAVOK";
            }
            painter.drawText(left + sWidth * 9 / 10 + 109
                             ,top + sHeight + 32
                             ,sWidth / 10 - 13
                             ,26
                             ,Qt::AlignCenter,cavokString);

            if(met_modifyFlag){
                painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                 ,top + 61 + sHeight + 2,(sWidth - 70)/ 5 - 10
                                 ,26,Qt::AlignCenter,"确认修改");
            }
            else{
                painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                 ,top + 61 + sHeight + 2,(sWidth - 70)/ 5 - 10,26
                                 ,Qt::AlignCenter,"修改");
            }
            painter.drawText(left + sWidth * 4 / 5 + 122
                             ,top + sHeight + 94
                             ,sWidth / 10 - 13
                             ,26,Qt::AlignCenter,"请求趋势");

            painter.drawText(left + sWidth * 9 / 10 + 112
                             ,top + sHeight + 94
                             ,sWidth / 10 - 14
                             ,26,Qt::AlignCenter,"发送METAR");

        }
        else if(m_metar[2]){ // speci
            showOrCloseSpaciContrls(true);
            showOrCloseMetarContrls(false);
            showOrCloseMetarReportContrl(false);
            showOrCloseSpacialReportContrl(false);
            showOrCloseTelegramCFG(false);

            //qDebug()<<"draw two";

            // copy m_metar[1]
            painter.setPen(Qt::gray);
            painter.drawRect(left + 97,top + 115,sWidth * 4 / 8,sHeight - 120 - 6);

            // SPACI context show controls
            painter.setPen(QPen(Qt::gray,2));
            painter.setBrush(QColor("#D9D9D9"));
            painter.drawRoundedRect(left + 97,top + 115 + sHeight - 120 - 3
                                    ,sWidth,(sHeight - 120) / 13,4,4);
            painter.drawRoundedRect(left + 97,top + 27 + sHeight,sWidth,98,6,6);
            painter.drawRoundedRect(left + 97,top + 27 + sHeight + 102,sWidth
                                    ,height() - (27 + sHeight + 98) - 12,6,6);

            // SPACI send buttons controls
            //1 . update 更新
            QLinearGradient gradMetSend1(left + 93,top + 75,left + 93,top + 115);
            if(!m_spaciUpdate){
                gradMetSend1.setColorAt(0,QColor("#4A708B"));
                gradMetSend1.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend1.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend1.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend1);
            painter.drawRoundRect(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                  ,top + 31 + sHeight + 1
                                  ,(sWidth - 70)/ 5 - 10,26,6,6);

            //2 . modify 修改
            QLinearGradient gradMetSend2(left + 93,top + 75,left + 93,top + 115);
            if(!m_spaciModify){
                gradMetSend2.setColorAt(0,QColor("#4A708B"));
                gradMetSend2.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend2.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend2.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend2);
            painter.drawRoundRect(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                  ,top + 61 + sHeight + 2
                                  ,(sWidth - 70)/ 5 - 10,26,6,6);

            //3 . send 发送
            QLinearGradient gradMetSend3(left + 93,top + 75,left + 93,top + 115);
            if(!m_spaciSend){
                gradMetSend3.setColorAt(0,QColor("#4A708B"));
                gradMetSend3.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend3.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend3.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend3);
            painter.drawRoundRect(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                  ,top + 91 + sHeight + 3
                                  ,(sWidth - 70)/ 5 - 10,26,3,3);

            //4 metar 报确认
            QLinearGradient gradMetSend4(0,buttom - 102,0,buttom - 8);
            if(!m_metarComfire){
                gradMetSend4.setColorAt(0,QColor("#4A708B"));
                gradMetSend4.setColorAt(1,QColor("#00688B"));

            }
            else{
                gradMetSend4.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend4.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend4);
            painter.drawRoundRect(left + 7 + (width() - 112) / 2
                                  ,buttom - 102,90,94,3,3);

            // spacial 报确认
            QLinearGradient gradMetSend5(0,buttom - 102,0,buttom - 8);
            if(!m_spacilComfire){
                gradMetSend5.setColorAt(0,QColor("#4A708B"));
                gradMetSend5.setColorAt(1,QColor("#00688B"));
            }
            else{
                gradMetSend5.setColorAt(0,QColor("#CAE1FF"));
                gradMetSend5.setColorAt(1,QColor("#B0E0E6"));
            }
            painter.setBrush(gradMetSend5);
            painter.drawRoundRect(left + 7 + (width() - 112),buttom - 102,90,94,3,3);

            QLinearGradient gStart(0,top + 142 + (sHeight - 120) * 12.06 / 13,0
                                   ,top + 142 + (sHeight - 120) / 13);
            QLinearGradient gend(0,top + 142 + (sHeight - 120) * 12.06 / 13,0
                                 ,top + 142 + (sHeight - 120) / 13);
            gStart.setColorAt(0,QColor("#4A708B"));
            gStart.setColorAt(1,QColor("#00688B"));
            gend.setColorAt(0,QColor("#CAE1FF"));
            gend.setColorAt(1,QColor("#B0E0E6"));

            //最近的metar 报 和spaci报
            if(!m_clickLastMetar){
                painter.setBrush(gStart);
            }
            else{
                painter.setBrush(gend);
            }
            painter.drawRoundRect(left + sWidth * 4.8 / 8 + 120
                                  ,top + 146 + (sHeight - 120) * 12.06 / 13
                                  ,sWidth * 1.5 / 8,(sHeight - 120) / 13 - 8,3,3);

            if(!m_clickLastSpaci){
                painter.setBrush(gStart);
            }
            else{
                painter.setBrush(gend);
            }
            painter.drawRoundRect(left + sWidth * 6.3 / 8 + 120 + 4
                                  ,top + 142 + (sHeight - 120) * 12.06 / 13 + 4
                                  ,sWidth * 1.5 / 8,(sHeight - 120) / 13 - 8,3,3);

            //SPACI show control titles
            painter.setPen(Qt::black);
            painter.drawText(left + 110,top + 142 + (sHeight - 120) * 12 / 13
                             ,60,(sHeight - 120) / 13,Qt::AlignCenter,"等级");
            painter.drawText(left + sWidth * 1.5 / 8 + 117
                             ,top + 142 + (sHeight - 120) * 12 / 13
                             ,60,(sHeight - 120) / 13,Qt::AlignCenter,"接收地址");
            painter.drawText(left + 100,top + 27 + sHeight,60,98,Qt::AlignCenter,"SPACI");

            painter.setPen(Qt::white);
            painter.drawText(left + sWidth * 4.8 / 8 + 120
                             ,top + 142 + (sHeight - 120) * 12 / 13
                             ,sWidth * 1.5/ 8,(sHeight - 120) / 13
                             ,Qt::AlignCenter,"最近的METAR报告");
            painter.drawText(left + sWidth * 6.3 / 8 + 120,top + 142 + (sHeight - 120) * 12 / 13
                             ,sWidth * 1.5/ 8,(sHeight - 120) / 13
                             ,Qt::AlignCenter,"最近的SPACI报告");
            painter.drawText(left + 7 + (width() - 112) / 2,buttom - 102,90,94
                             ,Qt::AlignCenter,"METAR确认");
            painter.drawText(left + 7 + (width() - 112),buttom - 102,90,94
                             ,Qt::AlignCenter,"SPACIL确认");

            painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                             ,top + 31 + sHeight + 1
                             ,(sWidth - 70)/ 5 - 10,26
                             ,Qt::AlignCenter,"创建SPACI");
            if(spaci_modifyFlag){
                painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                 ,top + 61 + sHeight + 2
                                 ,(sWidth - 70)/ 5 - 10,26
                                 ,Qt::AlignCenter,"确认修改");
            }
            else{
                painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                                 ,top + 61 + sHeight + 2
                                 ,(sWidth - 70)/ 5 - 10,26
                                 ,Qt::AlignCenter,"修改");
            }
            painter.drawText(left + 165 + (sWidth - 70) * 4 / 5 + 13
                             ,top + 91 + sHeight + 3
                             ,(sWidth - 70)/ 5 - 10,26
                             ,Qt::AlignCenter,"发送");

        }
        else if(m_metar[3]){ // meatr report
            showOrCloseMetarReportContrl(true);
            showOrCloseMetarContrls(false);
            showOrCloseSpaciContrls(false);
            showOrCloseSpacialReportContrl(false);
            showOrCloseTelegramCFG(false);
            painter.setPen(Qt::gray);
            painter.drawRect(left + 97,top + 115,sWidth * 4 / 8,sHeight - 120 - 6);
        }
        else if(m_metar[4]){ // special report
            showOrCloseSpacialReportContrl(true);
            showOrCloseMetarContrls(false);
            showOrCloseSpaciContrls(false);
            showOrCloseMetarReportContrl(false);
            showOrCloseTelegramCFG(false);
            painter.setPen(Qt::gray);
            painter.drawRect(left + 97,top + 115,sWidth * 4 / 8,sHeight - 120 - 6);
        }
        else if(m_metar[5]){ // set options
            showOrCloseMetarContrls(false);
            showOrCloseSpaciContrls(false);
            showOrCloseMetarReportContrl(false);
            showOrCloseSpacialReportContrl(false);
            showOrCloseTelegramCFG(true);
            sHeight = sHeight + 100;
            painter.save();
            painter.setPen(Qt::gray);
            painter.restore();
        }
    }
    else if(funcMap[3] == true){
        //main user
        showOrCloseTelegramCFG(false);
        showOrCloseMainWaringContrl(false);
        showOrCloseMetarContrls(false);
        showOrCloseSpaciContrls(false);
        showOrCloseMetarReportContrl(false);
        showOrCloseSpacialReportContrl(false);

        //atc
        showOrCloseAtcMetarReport(false);
        showOrCloseAtcMain(false);

        //draw the main deceives config UI
        int threeWidth = width() - 100;

        painter.save();
        painter.setPen(QPen(Qt::gray,2));
        painter.drawRect(left + 93,top + 75,width() - 94 - 4 - 4 + 2,height() - 75 - 4);
        painter.restore();

        painter.save();
        painter.setPen(Qt::NoPen);

        //draw the config functions buttons
        QPoint configStartPoint(0,top + 75);
        QPoint configEndPoint(0,top + 115);
        QLinearGradient gradMet1(configStartPoint,configEndPoint);
        QLinearGradient gradMet2(configStartPoint,configEndPoint);
        gradMet1.setColorAt(0,QColor("#4A708B"));
        gradMet1.setColorAt(1,QColor("#00688B"));
        gradMet2.setColorAt(0,QColor("#CAE1FF"));
        gradMet2.setColorAt(1,QColor("#B0E0E6"));

        if(!m_mserver){
            painter.setBrush(gradMet1);
        }
        else{
            painter.setBrush(gradMet2);
        }
        painter.drawRoundedRect(left + 94+ 2,top + 75 + 4,threeWidth / 10 - 1,30,3,3);
        if(!m_mCollect){
            painter.setBrush(gradMet1);
        }
        else{
            painter.setBrush(gradMet2);
        }
        painter.drawRoundedRect(left + 94 + threeWidth / 10+ 2
                                ,top + 75 + 4,threeWidth / 10 - 1,30,3,3);
        if(!m_mServerConfig){
            painter.setBrush(gradMet1);
        }
        else{
            painter.setBrush(gradMet2);
        }
        painter.drawRoundedRect(left + 94 + threeWidth * 2 / 10+ 2
                                ,top + 75 + 4,threeWidth / 10 - 1,30,3,3);
        if(!m_mCollectConfig){
            painter.setBrush(gradMet1);
        }
        else{
            painter.setBrush(gradMet2);
        }
        painter.drawRoundedRect(left + 94 + threeWidth * 3 / 10+ 2
                                ,top + 75 + 4,threeWidth / 10 - 1,30,3,3);
        if(!m_mDataConfig){
            painter.setBrush(gradMet1);
        }
        else{
            painter.setBrush(gradMet2);
        }
        painter.drawRoundedRect(left + 94 + threeWidth * 4 / 10+ 2
                                ,top + 75 + 4,threeWidth / 10 - 1,30,3,3);
        if(!m_mLocaConfig){
            painter.setBrush(gradMet1);
        }
        else{
            painter.setBrush(gradMet2);
        }
        painter.drawRoundedRect(left + 94 + threeWidth * 5 / 10+ 2
                                ,top + 75 + 4,threeWidth / 10 - 1,30,3,3);

        //draw the config functions buttons txet
        painter.setPen(Qt::white);
        QFont metarFont = painter.font();
        metarFont.setPixelSize(14);
        painter.setFont(metarFont);
        painter.drawText(left + 94+ 2,top + 75 + 4,threeWidth / 10 - 10 - 1,30
                         ,Qt::AlignCenter,"设备状态");
        painter.drawText(left + 94 + threeWidth/ 10 + 10,top + 75 + 4
                         ,threeWidth / 10 - 10- 1,30,Qt::AlignCenter,"设备管理");
        painter.drawText(left + 94 + threeWidth * 2 / 10+ 2,top + 75 + 4
                         ,threeWidth / 10 - 10- 1,30,Qt::AlignCenter,"告警");
        painter.drawText(left + 94 + threeWidth * 3 / 10+ 2,top + 75 + 4
                         ,threeWidth / 10 - 10- 1,30,Qt::AlignCenter,"日志");
        painter.drawText(left + 94 + threeWidth * 4 / 10+ 2,top + 75 + 4
                         ,threeWidth / 10 - 10- 1,30,Qt::AlignCenter,"AFTN");
        painter.drawText(left + 94 + threeWidth * 5 / 10+ 2,top + 75 + 4
                         ,threeWidth / 10 - 10- 1,30,Qt::AlignCenter,"机场管理");
        painter.setPen(QPen(QColor("#4A708B"),2));
        painter.drawLine(left + 98 ,top + 113,left + 105 + threeWidth - 15,top + 113);
        painter.restore();

        if(m_configPage[1]){
            showOrCloseAFTNContrls(false);
            showOrCloseLocaCFGContrl(false);
            showOrCloseDeveiceContrl(true);
            showOrCloseInfomationContrl(false);
            showOrCloseLogContrl(false);
            showOrCloseWaringContrl(false);

            painter.save();
            painter.setBrush(Qt::green);
            painter.drawRoundedRect(left + 94  + 15,top + 75 + 14,10,10,5,5);
            painter.restore();
        }
        else if(m_configPage[2]){
            showOrCloseAFTNContrls(false);
            showOrCloseLocaCFGContrl(false);
            showOrCloseDeveiceContrl(false);
            showOrCloseInfomationContrl(true);
            showOrCloseLogContrl(false);
            showOrCloseWaringContrl(false);

            painter.save();
            painter.setBrush(Qt::green);
            painter.drawRoundedRect(left + 94 + threeWidth / 10  + 15
                                    ,top + 75 + 14,10,10,5,5);
            painter.restore();
        }
        else if(m_configPage[3]){
            showOrCloseAFTNContrls(false);
            showOrCloseLocaCFGContrl(false);
            showOrCloseDeveiceContrl(false);
            showOrCloseInfomationContrl(false);
            showOrCloseLogContrl(false);
            showOrCloseWaringContrl(true);

            painter.save();
            painter.setBrush(Qt::green);
            painter.drawRoundedRect(left + 94 + threeWidth * 2 / 10  + 15
                                    ,top + 75 + 14,10,10,5,5);
            painter.restore();
        }
        else if(m_configPage[4]){
            showOrCloseAFTNContrls(false);
            showOrCloseLocaCFGContrl(false);
            showOrCloseDeveiceContrl(false);
            showOrCloseInfomationContrl(false);
            showOrCloseWaringContrl(false);
            showOrCloseLogContrl(true);
            painter.save();
            painter.setBrush(Qt::green);
            painter.drawRoundedRect(left + 94 + threeWidth * 3 / 10  + 15
                                    ,top + 75 + 14,10,10,5,5);
            painter.restore();
        }
        else if(m_configPage[5]){  // AFTN CFG
            showOrCloseAFTNContrls(true);
            showOrCloseLocaCFGContrl(false);
            showOrCloseDeveiceContrl(false);
            showOrCloseInfomationContrl(false);
            showOrCloseLogContrl(false);
            showOrCloseWaringContrl(false);

            painter.save();
            painter.setBrush(Qt::green);
            painter.drawRoundedRect(left + 94 + threeWidth * 4 / 10  + 15
                                    ,top + 75 + 14,10,10,5,5);
            painter.restore();
        }
        else if(m_configPage[6]){  // loca CFG
            // 加上此页操作。
             showOrCloseLocaCFGContrl(true);
            showOrCloseAFTNContrls(false);
            showOrCloseDeveiceContrl(false);
            showOrCloseInfomationContrl(false);
            showOrCloseLogContrl(false);
            showOrCloseWaringContrl(false);

            painter.save();
            painter.setBrush(Qt::green);
            painter.drawRoundedRect(left + 94 + threeWidth * 5 / 10  + 15
                                    ,top + 75 + 14,10,10,5,5);
            painter.restore();
        }
    }
    else if(funcMap[4] == true){
        //main user
        showOrCloseMainWaringContrl(false);

        //other contrl
        showOrCloseTelegramCFG(false);
        showOrCloseAFTNContrls(false);
        showOrCloseLocaCFGContrl(false);
        showOrCloseMetarContrls(false);
        showOrCloseSpaciContrls(false);
        showOrCloseMetarReportContrl(false);
        showOrCloseSpacialReportContrl(false);
        showOrCloseInfomationContrl(false);
        showOrCloseLogContrl(false);
        showOrCloseWaringContrl(false);

        // deveice
        showOrCloseDeveiceContrl(false);

        int left4 = left + 93;
        int top4 = top + 75;
        int width4 = width() - 94 - 4 - 4 + 2;
        int height4 = height() - 75 - 4;
        painter.save();
        painter.setPen(QPen(Qt::gray,2));
        painter.drawRect(left4,top4,width4,height4);
        painter.restore();

        painter.setPen(QPen(Qt::gray,2));
        painter.setBrush(QColor("#eeeeee"));
        QFont font = painter.font();
        font.setPixelSize(16);
        font.setBold(true);
        painter.setFont(font);

        painter.save();
        painter.drawRect(left4,top4,65,90);
        painter.translate(left4 + 32,top4 + 45);
        painter.rotate(-90);
        painter.drawText(- 45,- 32,90,65,Qt::AlignCenter,"ATC MAIN");
        painter.restore();

        painter.save();
        painter.drawRect(left4,top4 + 92,65,120);
        painter.translate(left4 + 32,top4 + 92 + 60);
        painter.rotate(-90);
        painter.drawText(- 60,- 32,120,65,Qt::AlignCenter,"ATC REPORT");
        painter.restore();

        painter.save();
        painter.drawRect(left4,top4 + 214,65,70);
        painter.translate(left4 + 32,top4 + 214 + 35);
        painter.rotate(-90);
        painter.drawText(- 35,- 32,70,65,Qt::AlignCenter,"RWYn");
        painter.restore();

        painter.save();
        painter.drawRect(left4,top4 + 286,65,70);
        painter.translate(left4 + 32,top4 + 286 + 35);
        painter.rotate(-90);
        painter.drawText(- 35,- 32,70,65,Qt::AlignCenter,"03-21");
        painter.restore();

        //已被占用尺寸 宽 80
        if(m_atcPage[1]){
            showOrCloseAtcMetarReport(false);
            showOrCloseAtcMain(true);
        }
        else if(m_atcPage[2]){
            showOrCloseAtcMetarReport(true);
            showOrCloseAtcMain(false);
        }
        else if(m_atcPage[3]){
            showOrCloseAtcMetarReport(false);
            showOrCloseAtcMain(false);
        }
        else if(m_atcPage[4]){
            showOrCloseAtcMetarReport(false);
            showOrCloseAtcMain(false);
        }
    }
    else if(funcMap[5] == true){
        //main user
        showOrCloseMainWaringContrl(false);

        //other contrls
        showOrCloseTelegramCFG(false);
        showOrCloseAFTNContrls(false);
        showOrCloseLocaCFGContrl(false);
        showOrCloseMetarContrls(false);
        showOrCloseSpaciContrls(false);
        showOrCloseMetarReportContrl(false);
        showOrCloseSpacialReportContrl(false);
        showOrCloseInfomationContrl(false);
        showOrCloseLogContrl(false);
        showOrCloseWaringContrl(false);

        // deveice
        showOrCloseDeveiceContrl(false);

        //atc
        showOrCloseAtcMetarReport(false);
        showOrCloseAtcMain(false);
        int left5 = left + 93;
        int top5 = top + 75;
        int width5 = width() - 94 - 4 - 4 + 2;
        int height5 = height() - 75 - 4;
        painter.save();
        painter.setPen(QPen(Qt::gray,2));
        painter.drawRect(left5,top5,width5,height5);
        painter.restore();
    }
}

void WorkStation::PressDraw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    QFont font = painter->font();
    font.setBold(true);
    font.setPixelSize(19);
    painter->setFont(font);
    painter->setBrush(QColor("#F0F8FF"));
    painter->drawRoundedRect(-150 ,-height() / 2 + 33+4,300,30,15,15);
    painter->setPen(QPen((Qt::gray),1));
    painter->drawRoundedRect(-60 ,-height() / 2 + 34 +3,140,30,15,15);
    painter->setPen(QPen((Qt::black),4));
    painter->drawText(-140 ,-height() / 2 + 33,50,38,Qt::AlignCenter,"QNH");
    painter->drawText(90 ,-height() / 2 + 33,50,38,Qt::AlignCenter,"hPa");
    font.setPixelSize(22);
    painter->setFont(font);
    painter->drawText(-80 ,-height() / 2 + 34,160,36,Qt::AlignCenter,m_qnf);
    painter->restore();
}

void WorkStation::scaleButtomClose(QPainter *painter)
{
    int polygon[3][2];
    polygon[0][0] = -width()/2+ 88;
    polygon[0][1] = -height()/2+73+(height()-76)/2 - 6;
    polygon[1][0] = -width()/2+ 82;
    polygon[1][1] = -height()/2+73+(height()-76)/2;
    polygon[2][0] = -width()/2+ 88;
    polygon[2][1] = -height()/2+73+(height()-76)/2 + 6;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawPolygon(QPolygon(3,&polygon[0][0]));
    painter->restore();
}

void WorkStation::scaleButtomOpen(QPainter *painter)
{
    int polygon[3][2];
    polygon[0][0] = -width()/2+ 6;
    polygon[0][1] = -height()/2+73+(height()-76)/2 - 6;
    polygon[1][0] = -width()/2+ 12;
    polygon[1][1] = -height()/2+73+(height()-76)/2;
    polygon[2][0] = -width()/2+ 6;
    polygon[2][1] = -height()/2+73+(height()-76)/2 + 6;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawPolygon(QPolygon(3,&polygon[0][0]));
    painter->restore();
}





