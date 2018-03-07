#ifndef GLABLECOM_SELECTBUTTON_H
#define GLABLECOM_SELECTBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>

class GlableSelectButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString nameStr READ getNameStr WRITE setNameStr NOTIFY nameStrChanged)

public:
    explicit GlableSelectButton(QWidget *parent = 0);
    QString getNameStr() const { return m_name;}

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void nameStrChanged();
    void buttonClick(QString Name);

public slots:
    void setNameStr(QString name){
        m_name = name;
        update();
    }

private:
    bool m_clicked;
    bool m_release;
    void initValue();


    QString m_name;
    void initButtonNameValue();

};

#endif // GLABLECOM_SELECTBUTTON_H
