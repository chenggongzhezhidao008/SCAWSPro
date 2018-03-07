#include "awosstartsetup.h"
#include <QApplication>
#include <QFont>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily("正楷");
    a.setFont(font);
    AwosStartSetup *setup = new AwosStartSetup();
    int flag = setup->startLogin();
    if(flag < 1){
        return 0;
    }
    return a.exec();
}
