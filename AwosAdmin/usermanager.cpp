#include "usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QWidget(parent)
{
    _init_model();
    _init_User_View();
    _set_User_Geometry();
    _init_Size_Value();
    _init_button_b();
    _initSubContrls();
}

void UserManager::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if( _width_Size_ != width()
            || _height_Size_ != height())
    {
        _width_Size_ = width();
        _height_Size_ = height();
        _set_User_Geometry();
        _set_geometry();
    }
    painter.save();
    QRect R1,R2,R3,R4;
    R1.setRect(width() - 290,height() - 50,60,20);
    R2.setRect(width() - 220,height() - 50,60,20);
    R3.setRect(width() - 150,height() - 50,60,20);
    R4.setRect(width() - 80,height() - 50,60,20);
    QLinearGradient vLine(0,height() - 50,0,height() - 30);
    vLine.setColorAt(0,Qt::gray);
    vLine.setColorAt(1,Qt::white);
    painter.setBrush(QColor(Qt::white));
    if(_update_b_){
        painter.setBrush(vLine);
    }
    painter.drawRect(R1);
    painter.drawText(R1,Qt::AlignCenter,"刷新");
    painter.setBrush(QColor(Qt::white));
    if(_create_b_){
        painter.setBrush(vLine);
    }
    painter.drawRect(R2);
    painter.drawText(R2,Qt::AlignCenter,"新建");
    painter.setBrush(QColor(Qt::white));
    if(_add_b_)
    {
        painter.setBrush(vLine);
    }
    painter.drawRect(R3);
    painter.drawText(R3,Qt::AlignCenter,"添加");
    painter.setBrush(QColor(Qt::white));
    if(_delete_b_)
    {
        painter.setBrush(vLine);
    }
    painter.drawRect(R4);
    painter.drawText(R4,Qt::AlignCenter,"删除");
    painter.restore();
}

void UserManager::mousePressEvent(QMouseEvent *e)
{
    bool _update;
    _update = false;
    if(e->button() == Qt::LeftButton){
        int _pos_X,_pos_Y;
        _pos_X = e->pos().x();
        _pos_Y = e->pos().y();
        if(_pos_X >( width() - 290)
                && _pos_X < (width() - 230)
                && _pos_Y > ( height() - 50)
                && _pos_Y < ( height() - 30)){
            qDebug()<<"update button";
            _update = true;
            _relase_b_ = true;
            _update_b_ = true;
            _update_user();
        }
        else if(_pos_X > (width() - 220)
                && _pos_X < (width() - 160)
                && _pos_Y > ( height() - 50)
                && _pos_Y < ( height() - 30)){
            _update = true;
            _relase_b_ = true;
            _create_b_ = true;
            _create_user();
        }
        else if(_pos_X > (width() - 150)
                && _pos_X < (width() - 90)
                && _pos_Y > ( height() - 50)
                && _pos_Y < ( height() - 30)){
            _update = true;
            _relase_b_ = true;
            _add_b_ = true;
            _add_user();
            _update_user();
            // call update user View
        }
        else if(_pos_X > (width() - 80)
                && _pos_X < (width() - 20)
                && _pos_Y > ( height() - 50)
                && _pos_Y < ( height() - 30)){
            _update = true;
            _relase_b_ = true;
            _delete_b_ = true;
            // call update user View
            _delete_user();
            _update_user();
        }
    }
    if( _update){
        update();
    }
}

void UserManager::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    qDebug()<<"relase button";
    if(_update_b_){
        _update_b_ = false;
    }
    else if(_create_b_){
        _create_b_ = false;
    }
    else if(_add_b_){
        _add_b_ = false;
    }
    else if(_delete_b_){
        _delete_b_ = false;
    }

    if(_relase_b_){
        _relase_b_ = false;
        update();
    }
}

void UserManager::_init_User_View()
{
    _User_View_ = new QTableView(this);
    connect(_User_View_,SIGNAL(activated(QModelIndex))
            ,this,SLOT(_select_row(QModelIndex)));
    connect(_User_View_,SIGNAL(pressed(QModelIndex))
            ,this,SLOT(_select_row(QModelIndex)));
}

void UserManager::_set_User_Geometry()
{
    _User_View_->setGeometry(10,10,width() - 20,height() - 80);
    _User_View_->show();
}

void UserManager::_initSubContrls()
{
    m_name_lab = new QLabel(this);
    m_name_lab->setText("用户");
    m_password_lab = new QLabel(this);
    m_password_lab->setText("密码");
    m_grade_lab = new QLabel(this);
    m_grade_lab->setText("权限");
    m_nameEdit = new QLineEdit(this);
    m_passwordEdit = new QLineEdit(this);
    m_gradeCombox = new QComboBox (this);
    QStringList list;
    list<<"预报"<<"观测"<<"机务"<<"塔台"<<"管理";
    m_gradeCombox->addItems(list);
    m_name_lab->hide();
    m_password_lab->hide();
    m_grade_lab->hide();
    m_nameEdit->hide();
    m_passwordEdit->hide();
    m_gradeCombox->hide();
}

void UserManager::_set_geometry()
{
    m_name_lab->setGeometry(40,height()-50,40,20);
    m_nameEdit->setGeometry(90,height()-50,60,20);
    m_password_lab ->setGeometry(160,height()-50,40,20);
    m_passwordEdit->setGeometry(210,height()-50,60,20);
    m_grade_lab->setGeometry(280,height()-50,40,20);
    m_gradeCombox->setGeometry(330,height()-50,60,20);
}

void UserManager::_update_user()
{
    emit user_options_signal("update:tableName=admin");
}

void UserManager::_create_user()
{
    m_userName = "";
    m_password = "";
    m_grade = "";
    m_name_lab->show();
    m_password_lab->show();
    m_grade_lab->show();
    m_nameEdit->show();
    m_passwordEdit->show();
    m_gradeCombox->show();
}

void UserManager::_add_user()
{
    QString userStr;
    m_userName =  m_nameEdit->text();
    m_password =  m_passwordEdit->text();
    m_grade =     m_gradeCombox->currentText();
    if(m_userName == ""||m_password == ""){
        qDebug()<<"waring:parameter lost ,add user faild!";
        return;
    }
    userStr = QString("add:name=%1/password=%2/grade=%3")
            .arg(m_userName).arg(m_password).arg(m_grade);
    emit user_options_signal(userStr);
    m_nameEdit->clear();
    m_passwordEdit->clear();
}

void UserManager::_delete_user()
{
    if(_selected_indexRow == -1){
        qDebug()<<"waring!!!!!";
        return ;
    }
    QSqlRecord record;
    record = m_model->record(_selected_indexRow);
    QString dataStr;
    dataStr = QString("delete:v1=%1/v2=%2/v3=%3")
            .arg(record.value("SC_username").toString())
            .arg(record.value("SC_password").toString())
            .arg(record.value("SC_loginClass").toString());
    qDebug()<<"===================delete user:"<<dataStr;
    emit user_options_signal(dataStr);
}

void UserManager::_set_user_table_Model(/*QSqlQueryModel *model*/)
{
    //qDebug()<<"VVVVVV3:"<<model;
    //m_model = model;
    _User_View_->setModel(m_model/*model*/);
    _User_View_->show();
}

QSqlQueryModel *UserManager::_get_Model_object()
{
    return m_model;
}

void UserManager::_select_row(QModelIndex index)
{
    qDebug()<<"FFFFFFFFFFFFFFFFFFFFFFFFFFF"<<index.row();
    _selected_indexRow = index.row();
    _User_View_->selectRow(_selected_indexRow);
}

void UserManager::_get_user_infor()
{
    _update_user();
}

void UserManager::_init_model()
{
    m_model = new QSqlQueryModel();
    _selected_indexRow = -1;
}

void UserManager::_init_Size_Value()
{
    _width_Size_ = 0;
    _height_Size_ = 0;
}

void UserManager::_init_button_b()
{
    _update_b_ = false;
    _create_b_ = false;
    _add_b_ = false;
    _delete_b_ = false;
    _relase_b_ = false;
}
