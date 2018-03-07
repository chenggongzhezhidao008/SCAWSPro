#include "telecfgsubcom.h"

TeleCFGSubCom::TeleCFGSubCom(QWidget *parent) :
    QWidget(parent)
{
    _m_init_size_value();
    _m_init_moedl();
    _m_init_sub_sensor_objcets();
    _init_defult_coms();
}

void TeleCFGSubCom::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);
    if(width() != m_width || height() != m_height){
        m_width = width();
        m_height = height();
        _m_set_model_gemotry();
        _m_set_sub_sensor_geomerty();
        _m_set_defult_geomerty_values();
    }
    int left = -width()/2;
    int top = -height()/2;
    painter.save();
    painter.setPen(QPen(Qt::white,2));
    painter.drawLine(left+4,top + 80 ,left + width() - 8,top + 80);
    painter.drawLine(left+4,top + 300 ,left + width() - 8,top + 300);
    painter.restore();
}

void TeleCFGSubCom::m_update_items(QString set)
{
    QStringList affixList;
    affixList = set.split(":",QString::SkipEmptyParts);
    QString boxkind ,itemName;
    boxkind = affixList.value(0);
    itemName = affixList.value(1);
    if(boxkind == "updateWindSelect")
    {
        int num = m_wind_Item_List.length();
        for(int i = 0;i < num;i++){
            if(m_wind_Item_List.value(i) == itemName)
                return;
        }
        m_wind_Item_List.push_back(itemName);
        m_wind_Select->clear();
        m_wind_Select->addItems(m_wind_Item_List);
    }
    else if(boxkind == "updateHumiTempselect")
    {
        int num2 = m_temp_Hum_Item_List.length();
        for(int i = 0;i < num2;i++)
        {
            if(m_temp_Hum_Item_List.value(i) == itemName)
                return;
        }
        m_temp_Hum_Item_List << itemName;
        m_tempdew_Select->clear();
        m_tempdew_Select->addItems(m_temp_Hum_Item_List);
    }
    else if(boxkind == "updateRVRSelect")
    {
        // vis contrl
        //int num3 = m_vis_Item_List.length();
        //for(int i = 0;i < num3;i++){
        //    if(m_vis_Item_List.value(i) == itemName)
        //        return;
        //}
        //m_vis_Item_List << itemName;
        //visBox->addItems(m_vis_Item_List);

        // rvr contrl
        int num3 = m_RVR_Item_List.length();
        for(int i = 0;i < num3;i++)
        {
            if(m_RVR_Item_List.value(i) == itemName)
                return;
        }
        m_RVR_Item_List << itemName;
        m_rvr_Select->clear();
        m_rvr_Select->addItems(m_RVR_Item_List);
    }
    else if(boxkind == "updateCloudSelect")
    {
        int num4 = m_cloud_Hight_Item_List.length();
        for(int i = 0;i < num4;i++)
        {
            if(m_cloud_Hight_Item_List.value(i) == itemName)
                return;
        }
        m_cloud_Hight_Item_List.push_back(itemName);
        m_cloud_Select->clear();
        m_cloud_Select->addItems(m_cloud_Hight_Item_List);
    }
    else if(boxkind == "updatePressSelect")
    {
        int num5 = m_press_Item_List.length();
        for(int i = 0;i < num5;i++)
        {
            if(m_press_Item_List.value(i) == itemName)
                return;
        }
        m_press_Item_List << itemName;
        m_press_Select->clear();
        m_press_Select->addItems(m_press_Item_List);
    }
    else if(boxkind == "updateWeatherSelect") //"updateWeatherSelect:%1"
    {
        int num6 = m_weather_Item_List.length();
        for(int i = 0;i < num6;i++)
        {
            if(m_weather_Item_List.value(i) == itemName)
                return;
        }
        m_weather_Item_List << itemName;
        m_weather_Select->clear();
        m_weather_Select->addItems(m_weather_Item_List);
        num6 = m_close_Weather_Item_List.length();
        for(int i = 0;i < num6;i++)
        {
            if(m_close_Weather_Item_List.value(i) == itemName)
                return;
        }
        m_close_Weather_Item_List << itemName;
        m_reWeather_Select->clear();//近时天气
        m_reWeather_Select->addItems(m_close_Weather_Item_List);
    }
}

void TeleCFGSubCom::_m_init_size_value()
{
    m_width = 0;
    m_height = 0;
}

void TeleCFGSubCom::_m_init_moedl()
{
    m_modelOption = new QLabel(this);
    m_modelOption->setText("模式");
    m_modelSelect = new QComboBox(this);
    m_modelSelect->addItem("Auto");
    m_modelSelect->addItem("Manual");
}

void TeleCFGSubCom::_m_set_model_gemotry()
{
    m_modelOption->setGeometry(10,10,40,20);
    m_modelSelect->setGeometry(10,50,100,20);
}

void TeleCFGSubCom::_m_init_sub_sensor_objcets()
{
    m_wind_Option = new QLabel(this);
    m_wind_Option->setText("风");
    m_wind_Select = new QComboBox(this);
    m_rvr_Option = new QLabel(this);
    m_rvr_Option->setText("能见度");
    m_rvr_Select = new QComboBox(this);
    m_weather_Option = new QLabel(this);
    m_weather_Option->setText("现在天气");
    m_weather_Select = new QComboBox(this);
    m_cloud_Option = new QLabel(this);
    m_cloud_Option->setText("云量");
    m_cloud_Select = new QComboBox(this);
    m_reWeather_Option = new QLabel(this);
    m_reWeather_Option->setText("近时天气");
    m_reWeather_Select = new QComboBox(this);
    m_tempdew_Option = new QLabel(this);
    m_tempdew_Option->setText("温度/露点");
    m_tempdew_Select = new QComboBox(this);
    m_press_Option = new QLabel(this);
    m_press_Option->setText("气压");
    m_press_Select = new QComboBox(this);
}

void TeleCFGSubCom::_m_set_sub_sensor_geomerty()
{
    m_wind_Option->setGeometry(10,90,60,20);//90
    m_wind_Select->setGeometry(80,90,100,20);
    m_rvr_Option->setGeometry(10,120,60,20);//120
    m_rvr_Select->setGeometry(80,120,100,20);
    m_cloud_Option->setGeometry(10,150,60,20);//150
    m_cloud_Select->setGeometry(80,150,100,20);
    m_weather_Option->setGeometry(10,180,60,20);//180
    m_weather_Select->setGeometry(80,180,100,20);
    m_reWeather_Option->setGeometry(10,210,60,20);//210
    m_reWeather_Select->setGeometry(80,210,100,20);
    m_tempdew_Option->setGeometry(10,240,60,20);//240
    m_tempdew_Select->setGeometry(80,240,100,20);
    m_press_Option->setGeometry(10,270,60,20);//270
    m_press_Select->setGeometry(80,270,100,20);
}

void TeleCFGSubCom::_init_defult_coms()
{
    m_wind_option = new QLabel(this);
    m_wind_option->setText("风运行");
    m_wind_defult = new QLabel(this);
    m_rvr_option = new QLabel(this);
    m_rvr_option->setText("能见度运行");
    m_rvr_defult = new QLabel(this);
    m_cloud_option = new QLabel(this);
    m_cloud_option->setText("现在天气运行");
    m_cloud_defult = new QLabel(this);
    m_weather_option = new QLabel(this);
    m_weather_option->setText("云量运行");
    m_weather_defult = new QLabel(this);
    m_reWeather_option = new QLabel(this);
    m_reWeather_option->setText("近时天气运行");
    m_reWeather_defult = new QLabel(this);
    m_tempdew_option = new QLabel(this);
    m_tempdew_option->setText("温度/露点运行");
    m_tempdew_defult = new QLabel(this);
    m_press_option = new QLabel(this);
    m_press_option->setText("气压运行");
    m_press_defult = new QLabel(this);
}

void TeleCFGSubCom::_m_set_defult_geomerty_values()
{
    m_wind_option->setGeometry(10,310,80,20);//310
    m_wind_defult->setGeometry(100,310,80,20);
    m_rvr_option->setGeometry(10,340,80,20);//340
    m_rvr_defult->setGeometry(100,340,80,20);
    m_cloud_option->setGeometry(10,370,80,20);//370
    m_cloud_defult->setGeometry(100,370,80,20);
    m_weather_option->setGeometry(10,400,80,20);//400
    m_weather_defult->setGeometry(100,400,80,20);
    m_reWeather_option->setGeometry(10,430,80,20);//430
    m_reWeather_defult->setGeometry(100,430,80,20);
    m_tempdew_option->setGeometry(10,460,80,20);//460
    m_tempdew_defult->setGeometry(100,460,80,20);
    m_press_option->setGeometry(10,490,80,20);//490
    m_press_defult->setGeometry(100,490,80,20);
}
QStringList TeleCFGSubCom::getTempHumItemList() const
{
    return m_temp_Hum_Item_List;
}

void TeleCFGSubCom::setTempHumItemList(const QStringList &value)
{
    m_temp_Hum_Item_List = value;
}

