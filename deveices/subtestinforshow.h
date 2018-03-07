#ifndef SUBTESTINFORSHOW_H
#define SUBTESTINFORSHOW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class subTestInforShow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int subWidth READ getSubWidth WRITE setSubWidth NOTIFY subWidthChanged)
    Q_PROPERTY(int subHeight READ getSubHeight WRITE setSubHeight NOTIFY subHeightChanged)

public:
    explicit subTestInforShow(QWidget *parent = 0);
    int getSubWidth() const { return m_width; }
    int getSubHeight() const { return m_height; }

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void subWidthChanged();
    void subWidthChanged();

public slots:
    void setSubWidth(int vlaue){

    }

    void setSubHeight(int vlaue){

    }

private:
    int m_width;
    int m_height;
};

#endif // SUBTESTINFORSHOW_H
