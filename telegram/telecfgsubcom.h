#ifndef TELECFGSUBCOM_H
#define TELECFGSUBCOM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QStringList>

class TeleCFGSubCom : public QWidget
{
    Q_OBJECT
public:
    explicit TeleCFGSubCom(QWidget *parent = 0);

    QStringList getTempHumItemList() const;
    void setTempHumItemList(const QStringList &value);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void m_update_items(QString set);

private:
    int m_width;
    int m_height;
    void _m_init_size_value();

    QLabel *m_modelOption;
    QComboBox *m_modelSelect;
    void _m_init_moedl();
    void _m_set_model_gemotry();

    QLabel    *m_wind_Option;
    QComboBox *m_wind_Select;
    QLabel    *m_rvr_Option;
    QComboBox *m_rvr_Select;
    QLabel    *m_cloud_Option;
    QComboBox *m_cloud_Select;
    QLabel    *m_weather_Option;
    QComboBox *m_weather_Select;
    QLabel    *m_reWeather_Option;
    QComboBox *m_reWeather_Select;
    QLabel    *m_tempdew_Option;
    QComboBox *m_tempdew_Select;
    QLabel    *m_press_Option;
    QComboBox *m_press_Select;
    void _m_init_sub_sensor_objcets();
    void _m_set_sub_sensor_geomerty();

    QLabel  *m_wind_option;
    QLabel  *m_wind_defult;
    QLabel  *m_rvr_option;
    QLabel  *m_rvr_defult;
    QLabel  *m_cloud_option;
    QLabel  *m_cloud_defult;
    QLabel  *m_weather_option;
    QLabel  *m_weather_defult;
    QLabel  *m_reWeather_option;
    QLabel  *m_reWeather_defult;
    QLabel  *m_tempdew_option;
    QLabel  *m_tempdew_defult;
    QLabel  *m_press_option;
    QLabel  *m_press_defult;
    void _init_defult_coms();
    void _m_set_defult_geomerty_values();

    QStringList m_wind_Item_List;
    //QStringList m_vis_Item_List;
    QStringList m_RVR_Item_List;
    QStringList m_weather_Item_List;
    QStringList m_cloud_Hight_Item_List;
    QStringList m_temp_Hum_Item_List;
    QStringList m_press_Item_List;
    QStringList m_close_Weather_Item_List;
};

#endif // TELECFGSUBCOM_H
