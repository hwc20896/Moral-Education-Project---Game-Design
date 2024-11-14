#include "introwidget.h"

#ifdef DEBUG
#include <QDebug>
#define cout qDebug()
#endif

IntroWidget::IntroWidget(QWidget* parent) : QWidget(parent){
    RuleButton = new QPushButton("規則",this);
    RuleButton->setFont(QFont("Microsoft Jhenghei",18));
    RuleButton->setGeometry(760,20,100,50);

    StartButton = new QPushButton("開始",this);
    StartButton->setFont(QFont("Microsoft Jhenghei",27));
    StartButton->setGeometry(500,380,300,120);

    QPushButton* MuteDisplay = new QPushButton(this);
    MuteDisplay->setGeometry(580,20,50,50);
    MuteDisplay->setStyleSheet("background-image: url(:/mutestate/rsc/unmute.jpg); border-radius: 5px;");
    connect(MuteDisplay,&QPushButton::clicked,this,[=]{
        #ifdef DEBUG
            cout << IsMuted;
        #endif
        MuteDisplay->setStyleSheet(QString("background-image: url(%1); border-radius: 5px;").arg(IsMuted?":/mutestate/rsc/unmute.jpg":":/mutestate/rsc/mute.jpg"));
        IsMuted = !IsMuted;
    });
}
