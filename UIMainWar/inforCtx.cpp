#include "inforCtx.h"

InforCtx::InforCtx(QWidget *parent) :
    QWidget(parent)
{
    initValues();
    initNumValue();
    initIndexValue();
    initsetcontextMenupolicy();
    initCustomMenus();
    _init_cell_width();
}

void InforCtx::_set_data_cell_width(int w)
{
    m_cell_w = w;
}

void InforCtx::paintEvent(QPaintEvent *e)
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
    QStringList list;
    int len;
    int m_y;
    QString subStr,valueStr;
    for(int i = 0;i < m_num;i++)
    {
        list.clear();
        list = m_DataMap[i + 1].split("|",QString::SkipEmptyParts);
        len = list.length();
        m_y = - height() / 2 + 18 * i;
        for(int n = 0;n < len;n++){
            subStr.clear();
            valueStr.clear();
            subStr = list.value(n).split(":").value(0);
            valueStr = list.value(n).split(":",QString::SkipEmptyParts).value(1);
            if(subStr == "sequence"){
                painter.drawText(left,m_y,width() * 1 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignHCenter,valueStr);
            }
            else if(subStr == "time"){
                painter.drawText(left + width() * 1 / 20,m_y,width() * 3 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignHCenter,valueStr);
            }
            else if(subStr == "context"){
                painter.drawText(left + width() * 4 / 20,m_y,width() * 14 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignLeft,valueStr);

            }
            else if(subStr == "deal"){
                if(valueStr == "true"){
                    painter.drawText(left + width() * 18 / 20,m_y,width() * 2 / 20,16
                                     ,Qt::AlignBottom | Qt::AlignHCenter,"Confirmed");
                }
                else{
                    painter.drawText(left + width() * 18 / 20,m_y,width() * 2 / 20,16
                                     ,Qt::AlignBottom | Qt::AlignHCenter,"NoConfirm");
                }
            }
        }
    }
    painter.restore();
}

void InforCtx::mousePressEvent(QMouseEvent *e)
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

void InforCtx::mouseDoubleClickEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){
        int PosY = e->pos().y();
        for(int n = 0;n < m_num;n++){
            if(PosY > (18 * n) && PosY < (18 * (n + 1))){
                flag = true;
                m_index = n + 1;
                emit doubleClickSignal(m_index);
            }
        }
    }
    qDebug()<<"double click index is:"<<m_index;
    if(flag){
        update();
    }
    if(e->button() == Qt::RightButton){
        //qDebug()<<"多少次！";
        menu->exec(QCursor::pos());
    }
}

void InforCtx::setSubWidth(int value)
{
    if( m_width != value){
        m_width = value;
        this->setGeometry(0,0,m_width,m_height);
        update();
    }
}

void InforCtx::setSubHeight(int value)
{
    if(m_height != value){
        m_height = value;
        this->setGeometry(0,0,m_width,m_height);
        update();
    }
}
void InforCtx::setDataMap(InforMap data)
{
    m_DataMap.clear();
    m_DataMap = data;
    m_num = m_DataMap.count();
    update();
}

void InforCtx::setActionName(QStringList actionName)
{
    m_namelist.clear();
    m_namelist = actionName;
    createActionContrls();
}

void InforCtx::menuOptionSlot()
{
    QAction *act=qobject_cast<QAction*>(sender());
    QString DataStr = act->objectName();
    //DataStr = DataStr + QString(">index|%1").arg(m_index);
    emit menuOption(DataStr);
}

void InforCtx::initsetcontextMenupolicy()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

void InforCtx::initCustomMenus()
{
    menu = new QMenu(this);
}

void InforCtx::initValues()
{
    m_width = 20;
    m_height = 20;
}

void InforCtx::initNumValue()
{
    m_num = 0;
}

void InforCtx::initIndexValue()
{
    m_index = -1;
}

void InforCtx::createActionContrls()
{
    QString nameStr;
    for(int i = 0;i < m_namelist.length();i++){
        nameStr = m_namelist.value(i).trimmed();
        QAction *action = menu->addAction(nameStr);
        connect(action,SIGNAL(triggered()),this,SLOT(menuOptionSlot()));
        action->setObjectName(nameStr);
        actionList.push_back(action);
    }
}

void InforCtx::_init_cell_width()
{
    m_cell_w = 180;
}
