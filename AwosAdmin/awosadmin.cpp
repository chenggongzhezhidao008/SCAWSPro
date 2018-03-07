#include "awosadmin.h"
#include <QDebug>

AwosAdmin::AwosAdmin(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    initUserInputCtl();
    initmoveValue();
    initTxtValue();
    initLoginFalg();
    _init_buttons_value();
}
void AwosAdmin::logining() //调用此函数处理信息
{
    m_queue.clear();
    QString userNmaeStr,passwordStr;
    userNmaeStr = userNameUi->text().trimmed();
    passwordStr = passwordUi->text().trimmed();
    if(userNmaeStr == "" || passwordStr == ""){
        txtStr = "please input you all information.";
        return ;
    }
    m_queue.enqueue(userNmaeStr);
    m_queue.enqueue(passwordStr);
    m_queue.enqueue(m_loginclass);//登录信息队列
    if(!m_login)
    {
        emit searchUser("user_putIn",m_queue);//发送信息
    }
}

void AwosAdmin::setUserNanme(QString userName)
{
    this->m_userName = userName;
    emit  userNanmeChanged();
    update();
}

void AwosAdmin::setPassword(QString password)
{
    this->m_password = password;
    emit passwordChanged();
    update();
}

void AwosAdmin::setLoginClass(QString loginClass)
{
    this->m_loginclass = loginClass;
    emit loginClassChanged();
    update();
}

void AwosAdmin::drawInputLine()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    if(userNameUi){
        userNameUi->setGeometry(width() * 2 / 5,height() / 5,width() / 2,height() * 1 / 10);
        userNameUi->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:gray;border-width:0;border-style:outset}");;
        userNameUi->setFont(font);
        userNameUi->show();
    }
    if(passwordUi){
        passwordUi->setEchoMode(QLineEdit::Password);
        passwordUi->setGeometry(width() * 2 / 5,height() * 2 / 5 ,width() / 2,height() * 1 / 10);
        passwordUi->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:gray;border-width:0;border-style:outset}");
        passwordUi->setFont(font);
        passwordUi->show();
    }
}

void AwosAdmin::loginResult(QString falg)
{
    QString falgStr = falg.split(":").value(0);
    if(falgStr == "pass"){
        m_login = true;//启动
        txtStr = "login pass,the system Will setup.";
        emit setupSystem(true);
    }
    else if(falgStr == "error"){
        m_login = false;//报错
        txtStr = "user information is error！";
    }
    else if(falgStr == "initInfor"){
        txtStr = falg.split(":").value(1);//初始化
    }
    else if(falgStr == "end"){
        txtStr = "system init ok.";//结束
        this->close();
    }
    update();
}

void AwosAdmin::initUserInputCtl()
{
    userNameUi = new QLineEdit(this);
    passwordUi = new QLineEdit(this);
}

void AwosAdmin::initLoginFalg()
{
    m_login = false;
}

LoginQueue AwosAdmin::getLoginIfoQueue()
{
    return this->m_queue;
}

void AwosAdmin::initmoveValue()
{
    moveWidget = false;
    StartPoint = QPoint();
}

void AwosAdmin::initTxtValue()
{
    txtStr ="awos";
}

void AwosAdmin::_init_buttons_value()
{
    _m_obsever = false;
    _m_forcaster = false;
    _m_machine = false;
    _m_tower = false;
    _m_manager = false;
    _m_release = false;
    _m_closed = false;
}



