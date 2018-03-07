#include "ip36edit.h"

Ip36Edit::Ip36Edit(QWidget *parent) :
    QWidget(parent)
{
    initIpAddressStr();
    initIpEditcontrl();
    setIpValidator();
    setIpEditStyleSheet();
    initUIsize();
    this->setWindowFlags(Qt::FramelessWindowHint);
    initleftClickValue();
    initClickBoolValue();
    initOptionSignal();
}

void Ip36Edit::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    int xleft = - width() / 2;
    int xright = width() / 2;
    int ytop = -height() / 2;
    int yuttom = height() /2;

    if(s_width != width() ||s_height != height()){
        setIpEditGeometry();
        s_width = width();
        s_height = height();
    }

    painter.save();

    //... 绘制几何图形，绘制UI界面图样

    // 一 绘制标题 (占用ui 尺寸 height1/6 width)

    //步骤1：绘制标题背景
    // 1）设置用于背景绘制的画刷 brush
    painter.setBrush(Qt::gray);

    // 3) 去掉背景边框线条
    painter.setPen(Qt::NoPen);

    // 2)绘制背景边框（长方形）
    painter.drawRect(xleft,ytop/* 0 - height()/ 4 / 2*/,width(),height()/6);

    //步骤2：添加标题文字

    //4) 设置字体
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(13);
    painter.setFont(font);

    //3) 设置字体颜色
    painter.setPen(QPen(Qt::white,3));

    //2) 在UI界面中给文字分配一个平面范围（一般都用长方形来）
    QRectF tRect(xleft,ytop,width(),height()/6);

    //1) 绘制标题文字
    painter.drawText(tRect,Qt::AlignCenter,"3616主设备IP地址设置");
    painter.restore();

    painter.save();
    // 二 绘制ip编辑区 (占用ui 尺寸 height/6 width/4)

    //步骤1：绘制现有ip标签
    //4) 设置字体
    //    QFont font = painter.font();
    font.setBold(false/*true*/);
    font.setPixelSize(13);
    painter.setFont(font);

    //3) 设置字体颜色
    painter.setPen(QPen(Qt::black/*white*/,3));

    //2) 在UI界面中给文字分配一个平面范围（一般都用长方形来）
    QRectF tRectip(xleft,ytop + height()* 2 /6,width()/4,height()/6);

    //1) 绘制标题文字
    painter.drawText(tRectip,Qt::AlignRight | Qt::AlignVCenter/*AlignCenter*/,"原始IP地址");

    //步骤2：绘制输入ip标签
    //    //4) 设置字体
    //    //QFont font = painter.font();
    //    font.setBold(false/*true*/);
    //    font.setPixelSize(13);
    //    painter.setFont(font);
    //    //3) 设置字体颜色
    //    painter.setPen(QPen(Qt::black/*white*/,3));

    //2) 在UI界面中给文字分配一个平面范围（一般都用长方形来）
    QRectF tRectip2(xleft,ytop+ height()* 3 /6,width()/4,height()/6);

    //1) 绘制标题文字
    painter.drawText(tRectip2,Qt::AlignRight| Qt::AlignVCenter/*AlignCenter*/,"输入IP地址");

    //步骤3：绘制原有ip地址字符串
    QRectF tRectipStr(xleft + width()/4 ,ytop + height()* 2 /6,width()* 2 /5/*4*/,height()/6);

    //1) 绘制标题文字
    painter.drawText(tRectipStr,Qt::AlignCenter,/*"127.0.0.1"*/ m_IPAddress);
    painter.restore();


    // 三 绘制输入ipstr的输入框(LineEdit) (使用系统提供的QLineEdit控件实现)

    //步骤 1:确定 ip输入控件 在UI上显示的左上角坐标点和尺寸
    /*
     * xleft + width()/4 ,ytop + height()* 3 /6,width()* 2 /5,height()/6
     */

    //步骤 2:用QLineEdit控件定义并初始化 ip输入控件
    /* 在.h文件中实现
     * private：
     *   QLineEdit *IpEdit;
     *   void initIpEditcontrl();
    */

    //步骤 3:设置ip输入控件在UI上显示的几何位置
    /* 在.h文件中实现
     * private：
     * setIpEditGeometry();
    */

    //步骤 4:如果需要缩放UI时:调用步骤2的函数重新设置 ip输入控件 在UI上的几何位置
    /*
     * 设置一队长宽尺寸存下每次UI的长宽，
     * 当每次UI尺寸改变时调用绘图事件（触发条件），
     * 在事件里判断尺寸后重设ip输入控件的几何位置和大小
     * 1.private:
     *    int s_width;
     *    int s_height;
     *    void initUIsize();
     *
     * 2. if(s_width != width() ||s_height != height()){
     *  setIpEditGeometry();
     *  s_width = width();
     *  s_height = height();
     *
     */

    //步骤 5:使用Qss样式表来修饰ip输入控件
    /*
     * setIpEditStyleSheet();
     */

    // 四 去除原有UI的标题栏
    /* 在构造函数中加
     * this->setWindowFlags(Qt::FramelessWindowHint);
     */

    // 五 当按下标题栏是可移动整个自定义UI组件

    //步骤1：捕获鼠标的左键，判断(如在标题区域置按下标志true)并保存按下点的位置pos
    /*void mousePressEvent(QMouseEvent *e);
     *e->button() == Qt::LeftButton
     *leftClick = true;
     *leftPos = e->globalPos() - this->pos();
     */

    //步骤2：移动自定义UI界面
    /*void mouseMoveEvent(QMouseEvent *e);
     *e->buttons() == Qt::LeftButton && leftClick
     *this->move(e->globalPos() - leftPos);
     */

    //步骤3：释放鼠标回复按下标志
    /*void mouseReleaseEvent(QMouseEvent *e);
     *leftClick = false;
     */

    //六 让界面的原始Ipstr 实时更新起来
    /* 在setIpAddres(QString ipAddres)函数中设置m_IPAddress
     *this->m_IPAddress = ipAddres;
     *调用 update() 触发绘图事件
     *painter.drawText(tRectipStr,Qt::AlignCenter,m_IPAddress);
     */

    //七 让界面识别ip地址格式输入
    /* 设置遮罩验证器
     * setIpValidator();
     */

    // 八 绘制按钮控件

    painter.save();
    //步骤 3： 点击和释放按钮改变按钮颜色
    /*    使用 mousePressEvent();
     *     mouseReleaseEvent();
     *     来配合 改变 cancle 变量
     */
    painter.setPen(Qt::NoPen);
    if(cancle){
        painter.setBrush(Qt::green);
    }
    else{
        painter.setBrush(Qt::gray);
    }
    //步骤 1： 确定按钮在自定义UI上占有位置和大小
    //    painter.setBrush(Qt::gray); //换成步骤3来操作
    painter.drawRoundedRect(xright-width() *3/6,yuttom - height()*2/6,width()/6,height()/6,6,6);

    //步骤 3： 点击和释放按钮改变按钮颜色
    /*   使用 mousePressEvent();
     *    mouseReleaseEvent();
     *    来配合 改变 confirm变量
     */
    if(confirm){
        painter.setBrush(Qt::green);
    }
    else{
        painter.setBrush(Qt::gray);
    }
    painter.drawRoundedRect(xright-width() *2/6 + 10,yuttom - height()*2/6,width()/6,height()/6,6,6);
    //步骤 2： 绘制背景并绘制字样
    painter.setPen(QPen(Qt::white,1));
    font.setPixelSize(13);
    painter.setFont(font);
    painter.drawText(xright-width() *3/6,yuttom - height()*2/6,width()/6,height()/6,Qt::AlignCenter,"返回");
    painter.drawText(xright-width() *2/6 + 10,yuttom - height()*2/6,width()/6,height()/6,Qt::AlignCenter,"确定");

    //步骤 4： 发送点击信号
    /*
     *
     *
     *
     */
    painter.restore();
}

void Ip36Edit::mousePressEvent(QMouseEvent *e)
{
    bool updateFlag = false;
    if(e->button() == Qt::LeftButton){
        int posX = e->pos().x();
        int posY = e->pos().y();
        // 原点在中间 ：xleft,ytop/* 0 - height()/ 4 / 2*/,width(),height()/6
        // 原点在左上角 ：0,0,width(),height()/6
        if(posX > 0 && posX < width() &&
                posY > 0 && posY <(height()/6)){
            leftClick = true;
            leftPos = e->globalPos() - this->pos();
        }
        // xright-width() *3/6,yuttom - height()*2/6,width()/6,height()/6,
        // 转化换坐标：width() -width() *3/6， height() - height()*2/6 ，width()/6,height()/6
        else if(posX > (width()/2) && posX < (width() *4/6) &&
                posY > (height()*4/6) && posY <(height()*5/6)){
            cancle = true;
            release = true;
            updateFlag = true;
            emit closeIpEdit(true);
        }
        //xright-width() *2/6 + 10,yuttom - height()*2/6,width()/6,height()/6,
        // 转化换坐标：width() -width() *2/6， height() - height()*2/6 ，width()/6,height()/6
        else if(posX > (width()*4/6) && posX < (width()*5/6) &&
                posY > (height()*4/6) && posY <(height()*5/6)){
            confirm = true;
            release = true;
            updateFlag = true;
            emit updateIpAddress(_m_option_signal + IpEdit->text());
        }
    }
    if(updateFlag){
        update();
    }
    e->accept();
}

void Ip36Edit::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && leftClick){
        this->move(e->globalPos() - leftPos);
    }
    e->accept();
}

void Ip36Edit::mouseReleaseEvent(QMouseEvent *e)
{
    leftClick = false;
    if(cancle){
        this->close();
        cancle = !cancle;
    }
    if(confirm){
        confirm = !confirm;
    }
    if(release){
        update();
    }

    e->accept();
}

void Ip36Edit::_set_Option_Signal(QString _Option_Signal)
{
    this->_m_option_signal.clear();
    this->_m_option_signal = _Option_Signal;
}

void Ip36Edit::initIpAddressStr()
{
    m_IPAddress = "127.0.0.1";
}

void Ip36Edit::initIpEditcontrl()
{
    IpEdit = new QLineEdit(this); //一定指定父对象（否则变成非模式对话框）
    IpEdit->show();
}

void Ip36Edit::setIpValidator()
{
    IpEdit->setInputMask("999.999.999.999");
    IpEdit->setAlignment(Qt::AlignCenter);
}

void Ip36Edit::setIpEditGeometry()
{
    if(IpEdit){
        //xleft + width()/4 ,ytop + height()* 3 /6,width()* 2 /5,height()/6
        //在paintEvent 函数外部的坐标不能平移还是初始坐标
        // 转换：width()/4 ,height()* 3 /6,width()* 2 /5,height()/6
        IpEdit->setGeometry(width()/4 + 20 ,height()* 13/24/*3 /6*/
                            ,width()* 2 /5 - 30,height()/12/*6*/);
    }
}

void Ip36Edit::setIpEditStyleSheet()
{
    if(IpEdit){
        QString styleStr = "QLineEdit{border:0px solid #636363;border-radius:5px;}";
        IpEdit->setStyleSheet(styleStr);
    }
}

void Ip36Edit::initUIsize()
{
    s_width = 0;
    s_height = 0;
}

void Ip36Edit::initleftClickValue()
{
    leftClick = false;
}

void Ip36Edit::initClickBoolValue()
{
    cancle = false;
    confirm = false;
    release = false;
}

void Ip36Edit::initOptionSignal()
{
    _m_option_signal= " ";
}
