#include "bodyrecog_demo.h"
#include <QtGui/QApplication>

// ����У׼������ʾת�������û�����ѡ��ɨ�����ģ���ʾ�ƴ����룻�����ֶ������ƴ����룻ȷ��������ƴ�����ű���


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BodyRecog_Demo w;
    w.show();
    return a.exec();
}
