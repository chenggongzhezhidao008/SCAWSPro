#include "waveline.h"
#include <QDebug>

void WaveLine::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       //qDebug()<<"the mouse coordinate:"<<event->pos();
       int posY = event->pos().y();
       int posX = event->pos().x();

       //打开跟踪
       if(posX > (this->width() - 65) && posX < (this->width() - 49) &&
               posY > 13 && posY < 29){
           this->selectTrack();
           qDebug()<<"按钮名称："<<"跟踪按钮";
           event->accept();
           return ;
       }

       //显示线条按钮
       int tempX,tempY;
       int buttonNum = this->m_lineNames.count();
       if((posY > 30) && (posY < 55)){//qDebug()<<"按钮位置Y："<<QString("%1").arg(posY);
           for(int i = 0;i < buttonNum;i++){
               tempX = 100 * i + 2;
                if((posX > tempX) && (posX < (tempX + 25))){
                    //qDebug()<<"按钮名称："<<QString("曲线%1").arg(i + 1);
                    selectLines(i+1);
                    event->accept();
                    return ;
                }
           }
       }

      //时间按钮
       if(posX > (this->width() - 65) && posX < (this->width() - 5)){
          for(int b = 0; b < 8;b++){
              tempY = 40 + (this->height() - 50 /*- 40 -10*/) * b / 8; // -10 最后一个按钮与底边的高度
              if(posY > tempY && posY < (tempY + 30)){
                  //qDebug()<<"时间选择按钮："<<QString("%1").arg(b + 1);
                  selectHours(b + 1);
                  event->accept();
                  return ;
              }
          }
       }
       event->accept();
   }
}






















