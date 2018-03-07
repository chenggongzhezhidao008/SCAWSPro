#ifndef WaringLogShow_H
#define WaringLogShow_H

#include <QWidget>
#include "waringloginforCtx.h"
#include <QScrollArea>
#include <QPainter>
#include <QPaintEvent>
#include <QDateTime>

class WaringLogShow : public QWidget
{
    Q_OBJECT
public:
    explicit WaringLogShow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void store_log_to_database(QString war);

public slots:
    void _m_add_log_Slot(QString logCtx,QString optioner);

private slots:
    void _m_log_information_update_page(int index);

private:
    WaringLogInforCtx *infor;
    QScrollArea *areaBar;
    void _init_infor_show();
    void _m_setGeomerty();

    int _m_width;
    int _m_height;
    void _init_size();

    InforMap _m_warData;
    int _m_log_number;
    void _init_log_number();
    void _m_add_logInformation(QString data);

    bool _m_showConfirm;
    void _init_show_kind();

    int _m_log_index;
    void _init_logIndex();
};

#endif // WaringLogShow_H
