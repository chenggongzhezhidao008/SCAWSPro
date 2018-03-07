#ifndef IP36EDIT_H
#define IP36EDIT_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPoint>


class Ip36Edit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString ipAddres READ getIpAddres WRITE setIpAddres NOTIFY ipAddresChanged)

public:
    explicit Ip36Edit(QWidget *parent = 0);
    QString getIpAddres() const {
        return this->m_IPAddress;
    }

signals:
    void ipAddresChanged();
    void updateIpAddress(QString ipAddress);
    void closeIpEdit(bool closed);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void setIpAddres(QString ipAddres){
        this->m_IPAddress.clear();
        this->m_IPAddress = ipAddres;
        update();
    }
    void _set_Option_Signal(QString _Option_Signal);
private:
    QString m_IPAddress;
    void initIpAddressStr();

    QLineEdit *IpEdit;
    void initIpEditcontrl();
    void setIpValidator();
    void setIpEditGeometry();
    void setIpEditStyleSheet();

    int s_width;
    int s_height;
    void initUIsize();

    bool leftClick;
    QPoint leftPos;
    void initleftClickValue();

    bool cancle;
    bool confirm;
    bool release;
    void initClickBoolValue();

    QString _m_option_signal;
    void initOptionSignal();
};

#endif // IP36EDIT_H
