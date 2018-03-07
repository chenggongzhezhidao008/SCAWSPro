#ifndef WarShow_H
#define WarShow_H

#include <QWidget>
#include "inforCtx.h"
#include <QScrollArea>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <QAction>
#include <QMenu>
#include <QDateTime>

typedef QVector<QAction *> menuButton;
class WarShow : public QWidget
{
    Q_OBJECT
public:
    explicit WarShow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void store_waring_to_database(QString war);

public slots:
    void _m_select_waring(bool comfirm);
    void _m_add_waring_Slot(QString warCtx);

private slots:
    void _m_warinfor_confirm(int index);
    void menuOptionSlot();
    void _m_menu_option_Slot(QString option);

private:
    InforCtx *infor;
    QScrollArea *areaBar;
    void _init_infor_show();
    void _m_setGeomerty();

    int _m_width;
    int _m_height;
    void _init_size();

    InforMap _m_warData;
    int _m_war_number;
    void _init_war_number();

    InforMap _m_war_confirmData;
    int _m_war_confirm_number;
    void _init_war_confirm();
    void _m_add_NoConfirm_waring(QString data);
    void _add_confirm_waring(QString war);

    bool _m_showConfirm;
    void _init_show_kind();

    QMenu *_m_menu;
    QStringList _m_namelist;
    menuButton _m_action_List;
    void _m_init_Custom_Menus();
    void _m_create_Action_Contrls();

    int _m_war_index;
    void _init_warIndex();
};

#endif // WarShow_H
