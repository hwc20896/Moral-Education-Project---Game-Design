#include <QApplication>
#include "mainwidget.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWidget window;
    window.setWindowTitle("基本法憲法問問答答");
    window.setFixedSize(1000,700);
    window.show();
    return app.exec();
}
