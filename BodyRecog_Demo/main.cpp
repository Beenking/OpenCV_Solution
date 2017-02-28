#include "bodyrecog_demo.h"
#include <QtGui/QApplication>

// 可以校准，并显示转换矩阵；用户交互选择扫描中心；显示移床距离；可以手动设置移床距离；确定后调用移床命令脚本；


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BodyRecog_Demo w;
    w.show();
    return a.exec();
}
