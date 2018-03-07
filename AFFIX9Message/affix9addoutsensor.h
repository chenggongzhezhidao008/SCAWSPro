#ifndef AFFIX9ADDOUTSENSOR_H
#define AFFIX9ADDOUTSENSOR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QComboBox>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPoint>


class Affix9AddOutSensor : public QWidget
{
    Q_OBJECT
public:
    explicit Affix9AddOutSensor(QWidget *parent = 0);
    void _set_out_sensor_title(QString title);
    void _set_out_sensor_kind(QString kind);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void store_sensor_data(QString sensorData);

public slots:
    void _out_sensor_data_deal();

private:
    int _width_s;
    int _height_s;
    void _init_Size_Sub_UI();

    QLabel *_leabel_name;
    QLabel *_leabel_ID;
    QLabel *_leabel_Loca;
    QLabel *_leabel_Kind;
    QLabel *_leabel_source;
    void _init_label_name();
    void _set_lable_geometry();

    QLineEdit *_edit_name;
    QLineEdit *_edit_Id;
    QLineEdit *_edit_loca;
    QLineEdit *_edit_source;
    void _init_Input_name();
    void _set_input_geometry();
    bool open_kind;
    QComboBox *_combox_Kind;
    QLabel *_leabel_kin_ctx;

    bool _cancle_b;
    bool _confirm_b;
    bool _release_b;
    void _init_button_Value();

    // move wdiget
    bool m_left_b;
    QPoint m_pos;
    void _init_move_bool_Value();

    QString _m_title_;
    void _init_out_Sensor_title();

    QString _m_kind;
    void _init_kind_value();
};

#endif // AFFIX9ADDOUTSENSOR_H
