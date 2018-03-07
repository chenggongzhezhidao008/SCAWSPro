#include "dealcenter3616.h"

DealCenter3616::DealCenter3616(QWidget *parent) :
    QWidget(parent)
{
    init_subui_obj();
    m_init_size();
}

void DealCenter3616::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    if(m_heigh != height() || m_width != width()){
        m_heigh = height();
        m_width = width();
        init_subui_geomerty();
    }
    painter.save();
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(0,0,width(),340+10,5,5);
    painter.restore();
}

void DealCenter3616::init_subui_obj()
{
    for(int card = 1;card < 21;card++){
        if(card < 3){
            Ui_NetworkCard *networkCard = new Ui_NetworkCard(this);
            networkCard->setObjectName(QString("networkCard:%1").arg(card));
            networkList[QString("networkCard:%1").arg(card)] = networkCard;
            continue ;
        }
        if(card > 18){
            Ui_powerCard *powerCard = new Ui_powerCard(this);
            powerCard->setObjectName(QString("powerCard:%1").arg(card));
            powerList[QString("powerCard:%1").arg(card)] = powerCard;
            continue ;
        }
        Ui_sensorCard *sensorCard = new Ui_sensorCard(this);
        sensorCard->setObjectName(QString("sensorCard:%1").arg(card));
        sensorList[QString("sensorCard:%1").arg(card)] = sensorCard;
    }
}

void DealCenter3616::init_subui_geomerty()
{
    int w_size,w_size2,w_size3;
    w_size = width()*7/124;
    w_size2 = width()*6/124;
    w_size3 = width()/124;
    for(int card = 1;card < 21;card++){
        if(card < 3){
            networkList[QString("networkCard:%1").arg(card)]
                    ->setGeometry(w_size3/2 + w_size *(card-1),5,w_size-2,340);
            continue ;
        }
        if(card > 18){
            powerList[QString("powerCard:%1").arg(card)]
                    ->setGeometry(w_size3/2 +w_size *2 + w_size2 *16 + w_size*(card -19),5,w_size-2,340);
            continue ;
        }
        sensorList[QString("sensorCard:%1").arg(card)]
                ->setGeometry(w_size3/2 + w_size *2 + w_size2 *(card-3),5,w_size2-2,340);
    }
}

void DealCenter3616::m_init_size()
{
    m_width = 0;
    m_heigh = 0;
}
