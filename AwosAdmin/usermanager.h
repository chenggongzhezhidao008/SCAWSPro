#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDebug>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QLinearGradient>
#include <QTableView>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlRecord>

class UserManager : public QWidget
{
    Q_OBJECT
public:
    explicit UserManager(QWidget *parent = 0);

signals:
    void user_options_signal(QString optionStr);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void _set_user_table_Model(/*QSqlQueryModel *model*/);
    QSqlQueryModel *_get_Model_object();
    void _select_row(QModelIndex index);
    void _get_user_infor();

private:

private:
    QSqlQueryModel *m_model;
    int _selected_indexRow;
    void _init_model();
    QTableView *_User_View_;
    void _init_User_View();
    void _set_User_Geometry();


    QLabel *m_name_lab,*m_password_lab,*m_grade_lab;
    QLineEdit *m_nameEdit,*m_passwordEdit;
    QComboBox *m_gradeCombox;
    void _initSubContrls();
    void _set_geometry();

    QString m_userName,m_password,m_grade;
    void _update_user();
    void _create_user();
    void _add_user();
    void _delete_user();

    int _width_Size_;
    int _height_Size_;
    void _init_Size_Value();

    // button set line gradient
    bool _update_b_;
    bool _create_b_;
    bool _add_b_;
    bool _delete_b_;
    bool _relase_b_;
    void _init_button_b();
};

#endif // USERMANAGER_H
