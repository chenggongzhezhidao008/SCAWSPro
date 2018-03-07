#include "warInforShow.h"

WarInforShow::WarInforShow(QWidget *parent) :
    QWidget(parent)
{
    initValues();
    initNumValue();
    initIndexValue();
    initsetcontextMenupolicy();
    initCustomMenus();
}

void WarInforShow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    int left = - width() / 2;
    int top = - height() / 2;
    painter.save();
    painter.setBrush(Qt::gray);
    painter.drawRect(left,top,width(),height());
    painter.restore();

    //     显示数据内容
    painter.save();
    painter.setBrush(QColor("#FFFAF0"));
    painter.setPen(Qt::NoPen);
    for(int i = 0;i < m_num;i++){
        if(i == (m_index - 1)){
            painter.setBrush(QColor("#CDAF95"));
            painter.drawRect(left,top + 18 * i,width(),16);
            painter.setBrush(QColor("#FFFAF0"));
        }
        else{
            painter.drawRect(left,top + 18 * i,width(),16);
        }
    }
    painter.setPen(QPen(Qt::black,3));
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(13);
    painter.setFont(font);
    for(int i = 0;i < m_num;i++){
        painter.drawText(left + 10,top + 18 * i,width(),16,
                         Qt::AlignVCenter | Qt::AlignLeft,m_DataMap[i + 1]);
    }
    painter.restore();
}

void WarInforShow::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){
        int PosY = e->pos().y();
        for(int n = 0;n < m_num;n++){
            if(PosY > (18 * n) && PosY < (18 * (n + 1))){
                flag = true;
                m_index = n + 1;
            }
        }
    }
    qDebug()<<"index is:"<<m_index;
    if(flag){
        update();
    }
    if(e->button() == Qt::RightButton){
        //qDebug()<<"多少次！";
        menu->exec(QCursor::pos());
    }
}

void WarInforShow::setSubWidth(int value)
{
    if( m_width != value){
        m_width = value;
        this->setGeometry(0,0,m_width,m_height);
        update();
    }
}

void WarInforShow::setSubHeight(int value)
{
    if(m_height != value){
        m_height = value;
        this->setGeometry(0,0,m_width,m_height);
        update();
    }
}
void WarInforShow::setDataMap(InforMap data)
{
    m_DataMap.clear();
    m_DataMap = data;
    m_num = m_DataMap.count();
    update();
    //qDebug()<<"XXXXXXXXX";
}

void WarInforShow::setActionName(QStringList actionName)
{
    m_namelist.clear();
    m_namelist = actionName;
    createActionContrls();
}

void WarInforShow::menuOptionSlot()
{
    QAction *act=qobject_cast<QAction*>(sender());
    //qDebug()<<"obj"<<act->objectName();
    QString DataStr = act->objectName();
    DataStr = DataStr + QString(">index|%1").arg(m_index);
    emit menuOption(DataStr);
}

void WarInforShow::initsetcontextMenupolicy()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

void WarInforShow::initCustomMenus()
{
    menu = new QMenu(this);
}

void WarInforShow::initValues()
{
    m_width = 20;
    m_height = 20;
}

void WarInforShow::initNumValue()
{
    m_num = 0;
}

void WarInforShow::initIndexValue()
{
    m_index = -1;
}

void WarInforShow::createActionContrls()
{
    QString nameStr;
    for(int i = 0;i < m_namelist.length();i++){
        nameStr = m_namelist.value(i).trimmed();
        QAction *action = menu->addAction(nameStr.split(":").value(1));
        connect(action,SIGNAL(triggered()),this,SLOT(menuOptionSlot()));
        action->setObjectName(nameStr);
        actionList.push_back(action);
    }
}
