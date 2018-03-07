#include "awosmainfram.h"
#include "ui_awosmainfram.h"

void AwosMainFram::windStatus(SensorMap senMap)
{
    DataMap headmap = senMap["windHead"];
    Q_UNUSED(headmap)
    DataMap bodymap = senMap["windData"];
    //======**** 状态
    //qDebug()<<"wind online status ******:"<<bodymap;
    if(bodymap["OnlineState"].toInt() == 1){
         windState(true);
    }
    else
    {
         windState(false);
    }
    headmap.clear();
    bodymap.clear();
}

void AwosMainFram::humiTempStatus(SensorMap senMap)
{
    DataMap headmap = senMap["humAndTempHead"];
    Q_UNUSED(headmap)
    DataMap bodymap = senMap["humAndTempData"];
    //======**** 状态
    //qDebug()<<"hum and temp online status ******:"<<bodymap;
    if(bodymap["OnlineState"].toInt() == 1){
         humiTempState(true);
    }
    else
    {
         humiTempState(false);
    }
    headmap.clear();
    bodymap.clear();
}

void AwosMainFram::rvrStatus(SensorMap senMap)
{
    DataMap headmap = senMap["VISHead"];
    Q_UNUSED(headmap)
    DataMap bodymap = senMap["VISData"];
    //qDebug()<<"SC Vis Status body data ******:"<<bodymap;
    //======**** 状态
    //qDebug()<<"RVR online status******:"<<bodymap["online"];
    if(bodymap["OnlineState"].toInt() == 1){
         rvrState(true);
    }
    else
    {
         rvrState(false);
    }
    headmap.clear();
    bodymap.clear();
}

void AwosMainFram::cloudStatus(SensorMap /*senMap*/)
{

}

void AwosMainFram::atmospherePressStatus(SensorMap /*senMap*/)
{

}

void AwosMainFram::rainStatus(SensorMap /*senMap*/)
{

}

void AwosMainFram::phenomenaWeatherStatus(SensorMap /*senMap*/)
{

}

void AwosMainFram::prevailingVisibilityStatus(SensorMap /*senMap*/)
{

}

void AwosMainFram::manualInputDataStatus(SensorMap /*senMap*/)
{

}

void AwosMainFram::humiTempData(SensorMap senMap)
{
    DataMap headmap = senMap["humAndTempHead"];
    Q_UNUSED(headmap)
    DataMap bodymap = senMap["humAndTempData"];
    //qDebug()<<"hum:"<<bodymap["RHINS"].split(":").at(0)<<"temp:"<<bodymap["TAINS"].split(":").at(0);
    ui->widget_TempValue->setText(bodymap["TAINS"].split(":").at(0).mid(0,4));
    ui->widget_HumValue->setText(bodymap["RHINS"].split(":").at(0).mid(0,4));
    ui->widget_dewPointValue->setText(bodymap["TDINS"].split(":").at(0).mid(0,4));
    headmap.clear();
    bodymap.clear();
}

void AwosMainFram::windState(bool connect)
{
    if(connect){
        ui->widget_wind_state->setState("OnLine");
    }
    else{
        ui->widget_wind_state->setState("disconnected");
    }
}

void AwosMainFram::humiTempState(bool connect)
{
    if(connect){
        ui->widget_temp_state->setState("OnLine");
        ui->widget_Hum_state->setState("OnLine");
    }
    else{
        ui->widget_temp_state->setState("disconnected");
        ui->widget_Hum_state->setState("disconnected");
    }
}


void AwosMainFram::rvrState(bool connect)
{
    if(connect){
        ui->widget_RVR_state->setState("OnLine");
    }
    else{
        ui->widget_RVR_state->setState("disconnected");
    }
}

void AwosMainFram::cloudState(bool /*connect*/)
{

}

void AwosMainFram::atmospherePressState(bool /*connect*/)
{

}

void AwosMainFram::rainState(bool /*connect*/)
{

}

void AwosMainFram::phenomenaWeatherState(bool /*connect*/)
{

}

void AwosMainFram::prevailingVisibilityState(bool /*connect*/)
{

}


