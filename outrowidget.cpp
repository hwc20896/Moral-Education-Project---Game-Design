#include "outrowidget.h"
#include <QApplication>
#include <QTimer>
#include <QEventLoop>
#include <cmath>
#include <stdexcept>
#define ALIGNCENTER setAlignment(Qt::AlignCenter)
#define SHOW setVisible(true);
#define TODOUBLE(var) static_cast<double>(var)
#define DEFAULTFONT "Microsoft JhengHei"

ResultWidget::ResultWidget(int CorrCount, int IncorrCount, int64_t TotalTime, QWidget* parent) : QWidget(parent),
  CorrCount(CorrCount), IncorrCount(IncorrCount), QuestionCount(CorrCount+IncorrCount){
    QLabel* Title = new QLabel("結果",this);
    Title->setGeometry(415,50,170,55);
    Title->ALIGNCENTER;
    Title->setFont(QFont(DEFAULTFONT,40));

    Score = new QLabel(QString("分數：%1 / %2").arg(this->CorrCount).arg(QuestionCount),this);
    Score->setGeometry(175,150,200,50);
    Score->ALIGNCENTER;
    Score->hide();
    Score->setFont(QFont(DEFAULTFONT,23));

    PrecisionRate = new QLabel(QString("正確率：%1%").arg(TODOUBLE(this->CorrCount) / TODOUBLE(QuestionCount) * 100),this);
    PrecisionRate->setGeometry(575,150,250,50);
    PrecisionRate->ALIGNCENTER;
    PrecisionRate->hide();
    PrecisionRate->setFont(QFont(DEFAULTFONT,23));

    RankDisplay = new QLabel(this);
    RankDisplay->setGeometry(410,260,182,144);
    RankDisplay->hide();
    RankDisplay->setPixmap(QPixmap(GetTier(CorrCount, QuestionCount)));

    TimeUsed = new QLabel(QString("完成時間：%1").arg(TimeDisplay(TotalTime)),this);
    TimeUsed->ALIGNCENTER;
    TimeUsed->setGeometry(120,450,300,40);
    TimeUsed->hide();
    TimeUsed->setFont(QFont(DEFAULTFONT,25));

    AvgTime = new QLabel(QString("平均回答時間：%1").arg(TimeDisplay(TotalTime/QuestionCount)),this);
    AvgTime->ALIGNCENTER;
    AvgTime->setGeometry(570,450,400,40);
    AvgTime->hide();
    AvgTime->setFont(QFont(DEFAULTFONT,25));

    ToEnd = new QPushButton("繼續...",this);
    ToEnd->setGeometry(400,540,200,90);
    ToEnd->hide();
    ToEnd->setFont(QFont(DEFAULTFONT,21));

    effect = new QSoundEffect;
    effect->setSource(QUrl("qrc:/sound/rsc/pop.wav"));
    effect->setVolume(.5);
}

void ResultWidget::PageSetup(){
    Cooldown(850);
    Score->setVisible(true);
    effect->play();
    Cooldown(850);
    PrecisionRate->setVisible(true);
    effect->play();
    Cooldown(850);
    RankDisplay->setVisible(true);
    effect->play();
    Cooldown(850);
    TimeUsed->setVisible(true);
    AvgTime->setVisible(true);
    effect->play();
    Cooldown(500);
    ToEnd->setVisible(true);
}

QString ResultWidget::TimeDisplay(double dur){
    if (dur > 6e4){
        double remain = remainder(dur,60.0);
        return QString("%1分%2秒").arg(floor(dur/6e4)).arg(QString::number(remain<0?remain+60:remain,'g',3));
    }
    else if (dur == 6e4) return "1分鐘";
    else if (dur >= 0) return QString("%1秒").arg(QString::number(dur/1000.0,'g',3));
    else throw std::range_error("Invalid duration");
}

QString ResultWidget::GetTier(int CorrCount, int TotalCount){
    /*  80% ~ 100% -> S
     *  55% ~ 80% -> A
     *  30% ~ 55% -> B
     *  0% ~ 30% -> C
     */
    double Rate = TODOUBLE(CorrCount) / TODOUBLE(TotalCount);
    if (Rate > 1) throw std::out_of_range("Rate bigger than 1");
    else if (Rate >= 0.8) return ":/rank/rsc/SRank.png";
    else if (Rate >= 0.55) return ":/rank/rsc/ARank.png";
    else if (Rate >= 0.3) return ":/rank/rsc/BRank.png";
    else if (Rate >= 0) return ":/rank/rsc/CRank.png";
    else throw std::out_of_range("Rate smaller than 0");
}

void ResultWidget::Cooldown(int duration){
    QEventLoop* lp = new QEventLoop;
    QTimer::singleShot(duration,lp,&QEventLoop::quit);
    lp->exec();
}

EndWidget::EndWidget(QWidget* parent) : QWidget(parent){
    this->setObjectName("EndWidget");
    this->setStyleSheet("QWidget#EndWidget{background-image: url(:/image/rsc/outrobg.jpg);}");

    QPushButton* QuitButton = new QPushButton("結束游戲",this);
    QuitButton->setGeometry(440,430,200,80);
    QuitButton->setFont(QFont(DEFAULTFONT,27));
    connect(QuitButton,&QPushButton::clicked,this,&QApplication::quit);

    ToInfo = new QPushButton("資訊頁",this);
    ToInfo->setGeometry(639,21,100,40);
    ToInfo->setFont(QFont(DEFAULTFONT,17));
}

InfoWidget::InfoWidget(QWidget* parent) : QWidget(parent){
    QLabel* title = new QLabel("資訊頁",this);
    title->setGeometry(384,46,233,50);
    title->setFont(QFont(DEFAULTFONT,37));

    QLabel* info = new QLabel(this);
    info->setGeometry(270,130,510,430);
    info->setText("分工：\n    洪偉晴：程序製作，背景音樂\n    古藝軒：繪圖\n    譚瑤琦：問題收集\n    葉鈺文：配音\n\n\n背景音樂：OMFG - Pizza\n\n使用程式語言：C++");
    info->setFont(QFont(DEFAULTFONT,23));

    Return = new QPushButton("返回",this);
    Return->setGeometry(410,580,180,63);
    Return->setFont(QFont(DEFAULTFONT,21));
}

OutroWidget::OutroWidget(int CorrCount, int IncorrCount, int64_t TotalTime, QWidget* parent) : QStackedWidget(parent){
    result = new ResultWidget(CorrCount, IncorrCount, TotalTime, this);
    this->addWidget(result);
    EndWidget* end = new EndWidget;
    this->addWidget(end);
    InfoWidget* infowidget = new InfoWidget;
    this->addWidget(infowidget);
    this->setCurrentIndex(0);
    connect(result->ToEnd,&QPushButton::clicked,this,[=]{setCurrentIndex(1);});
    connect(infowidget->Return,&QPushButton::clicked,this,[=]{setCurrentIndex(1);});
    connect(end->ToInfo,&QPushButton::clicked,this,[=]{setCurrentIndex(2);});
}
