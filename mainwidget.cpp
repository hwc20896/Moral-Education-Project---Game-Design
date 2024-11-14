#include "mainwidget.h"
#include "rulewidget.h"
#include "QuestionList.h"
#include "questionmanagement.h"

MainWidget::MainWidget(QWidget* parent) : QStackedWidget(parent){
    initpage = new IntroWidget;
    initpage->setObjectName("InitPage");
    this->addWidget(initpage);

    RuleWidget* rulepage = new RuleWidget;
    this->addWidget(rulepage);

    this->setCurrentIndex(0);
    this->setStyleSheet("QWidget#InitPage {background-image: url(:/image/rsc/firstpagebg.jpg);background-position: center;}");

    connect(initpage->RuleButton, BUTTON_CLICK, this, [=]{setCurrentIndex(1);});
    connect(rulepage->ReturnButton, BUTTON_CLICK, this, [=]{setCurrentIndex(0);});
    connect(initpage->StartButton, BUTTON_CLICK, this, &MainWidget::StartGame);

    Question1 = new QTMC(QuestionList::Question1);
    Question2 = new QTMC(QuestionList::Question2);
    Question3 = new QTMC(QuestionList::Question3);
    Question4 = new QTMC(QuestionList::Question4);
    Question5 = new QTMC(QuestionList::Question5);
    Question6 = new QTMC(QuestionList::Question6);
    Question8 = new QTMC(QuestionList::Question8);
    Question9 = new QTTF(QuestionList::Question9);
    Question10 = new QTTF(QuestionList::Question10);
    Question12 = new QTTF(QuestionList::Question12);
    Question13 = new QTTF(QuestionList::Question13);
    Question14 = new QTMC(QuestionList::Question14);
    Question15 = new QTMC(QuestionList::Question15);
    Question16 = new QTTF(QuestionList::Question16);
    Question17 = new QTMC(QuestionList::Question17);
    Question18 = new QTTF(QuestionList::Question18);
    Question19 = new QTTF(QuestionList::Question19);
    Question20 = new QTMC(QuestionList::Question20);
    Question21 = new QTTF(QuestionList::Question21);
    Question22 = new QTTF(QuestionList::Question22);
    Question23 = new QTTF(QuestionList::Question23);
    Question24 = new QTTF(QuestionList::Question24);
}

void MainWidget::StartGame(){
    QuestionManagement* mng = new QuestionManagement({
        Question1, Question2, Question3, Question4, Question5, Question6,
        Question8, Question9, Question10, Question12,
        Question13, Question14, Question15, Question16, Question17, Question18,
        Question19, Question20, Question21, Question22, Question23, Question24
        }, QuestionList::TotalQuestion
    );
    this->close();
    mng->setFixedSize(1000,700);
    mng->show();
    mng->SetMutedState(initpage->IsMuted);
    mng->bgm->play();
}


