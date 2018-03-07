#ifndef AWOSADMIN_H
#define AWOSADMIN_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLineEdit>
#include <QPoint>
#include <QQueue>
typedef QQueue<QString> LoginQueue;

class AwosAdmin : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString userNanme READ userNanme WRITE setUserNanme NOTIFY userNanmeChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString loginClass READ loginClass WRITE setLoginClass NOTIFY loginClassChanged)

public:
    explicit AwosAdmin(QWidget *parent = 0);
    QString userNanme() const { return this->m_userName; }
    QString password() const { return this->m_password; }
    QString loginClass() const { return this->m_loginclass; }

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void searchUser(QString option,LoginQueue loginQueue);//查询用户数据
    void userNanmeChanged();
    void passwordChanged();
    void loginClassChanged();
    void setupSystem(bool falg);

public slots:
    void logining();//收集登录信息
    void setUserNanme(QString userName);
    void setPassword(QString password);
    void setLoginClass(QString loginClass);
    void drawInputLine();//设置输入行编辑框
    LoginQueue getLoginIfoQueue();//保存用户信息
    void loginResult(QString falg);

private:
    LoginQueue m_queue;
    QLineEdit *userNameUi;
    QLineEdit *passwordUi;
    void initUserInputCtl();
    int m_wdith;
    int m_heigh;
    QString m_userName;
    QString m_password;
    QString m_loginclass;
    bool m_login;
    void  initLoginFalg();

    bool moveWidget;
    QPoint StartPoint;
    void initmoveValue();

    QString txtStr;
    void  initTxtValue();

    bool _m_obsever;
    bool _m_forcaster;
    bool _m_machine;
    bool _m_tower;
    bool _m_manager;
    bool _m_release;
    bool _m_closed;
    void _init_buttons_value();
};

#endif // AWOSADMIN_H
