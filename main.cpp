#include <QApplication>
#include <QWidget>
#include <QThread>
#include "Nahida.h"
#include "box2d.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Nahida *nahida = new Nahida();

    return QApplication::exec();
}
