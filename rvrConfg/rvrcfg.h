#ifndef RVRCFG_H
#define RVRCFG_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include <QMap>
#include <QComboBox>
#include <QStringList>
typedef QMap<QString,QString> DataMap;

class RVRCFG : public QWidget
{
    Q_OBJECT
public:
    explicit RVRCFG(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void dataCommandOptions(QString set_infor);

public slots:
    void show_cfg();
    void m_config_message(QString info);
    void m_set_all_values(DataMap data);

private slots:
    void PolluteAD_set();
    void SpotADMax_set();
    void StandardADMax_set();
    void MorCalculate_set();
    void VR800Correct_ask();
    void MakeUpMor_set();

private:
    QLabel *L_PolluteAD_a;
    QLineEdit *E_PolluteAD_a;
    QLineEdit *V_PolluteAD_a;
    QLabel *L_PolluteAD_b;
    QLineEdit *E_PolluteAD_b;
    QLineEdit *V_PolluteAD_b;
    QPushButton *B_PolluteAD_b;
    QPushButton *update_AllData;

    QLabel *L_SpotADMax;
    QLineEdit *E_SpotADMax;
    QLineEdit *V_SpotADMax;
    QPushButton *B_SpotADMax;

    QLabel *L_StdADMax;
    QLineEdit *E_StdADMax;
    QLineEdit *V_StdADMax;
    QPushButton *B_StdADMax;

    QLabel *L_morCaLc_a;
    QLineEdit *E_morCaLc_a;
    QLineEdit *V_morCaLc_a;

    QLabel *L_morCaLc_b;
    QLineEdit *E_morCaLc_b;
    QLineEdit *V_morCaLc_b;
    QPushButton *B_morCaLc_b;

    QLabel *L_morMakeUp_v;
    QLineEdit *E_morMakeUp_v;
    QLineEdit *V_morMakeUp_v;

    QLabel *L_morMakeUp_enable;
    QComboBox *E_morMakeUp_enable;
    QLineEdit *V_morMakeUp_enable;
    QPushButton *B_morMakeUp;

    void m_init_Contrls();
    void m_setGeometry();
    void m_init_Connections();

    int m_width;
    int m_height;
    bool doAction; // 标志这台设备有操作。
    bool askall; // 标志请求所有数据
    void m_initValue();

};

#endif // RVRCFG_H
