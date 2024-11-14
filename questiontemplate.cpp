#include "questiontemplate.h"
#include <QFont>

#define DEFAULTFONT "Microsoft Jhenghei"
#define SETPUSHBUTTONFONT setFont({DEFAULTFONT,15})
#define SETCOLOR(col) setStyleSheet(QString("background-color: %1;").arg(col))
#define SETCHOSEN SETCOLOR("#6d7dff")
#define SETWRONGANDPLAY SETCOLOR("#ff0011");\
                 IncorrSound->play()
#define SETRIGHTANDPLAY SETCOLOR("#00ee22"); \
                 CorrSound->play()
#define SETWRONG SETCOLOR("#ff0011")
#define SETRIGHT SETCOLOR("#00ee22")
#define COOLDOWN SetCooldown(1000)
#define SOURCE(url) setSource(QUrl(url))
#define __ANSWERTAG setObjectName("AnswerOption")
#define TODOUBLE(val) static_cast<double>(val)

#ifdef DEBUG
#include <QDebug>
#define cout qDebug()
#endif

QuestionTemplate::QuestionBase::QuestionBase(QWidget* parent) : QWidget(parent){
    CorrSound = new QSoundEffect;
    CorrSound->SOURCE("qrc:/sound/rsc/bingo.wav");

    IncorrSound = new QSoundEffect;
    IncorrSound->SOURCE("qrc:/sound/rsc/ohno.wav");

    #ifdef DEBUG
    connect(CorrSound, &QSoundEffect::playingChanged, this, []{cout << "CorrSound playing called";});
    connect(IncorrSound, &QSoundEffect::playingChanged, this, []{cout << "IncorrSound playing called";});
    #endif
}

void QuestionTemplate::QuestionBase::SetCooldown(size_t ms){
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

void QuestionTemplate::QuestionBase::SetProgress(int CurrentProgress, int Total){
    Progress->setText(QString("進度：%1 / %2 - %3%").arg(CurrentProgress).arg(Total).arg(TODOUBLE(CurrentProgress) / TODOUBLE(Total) * 100));
}

void QuestionTemplate::QuestionBase::SetScore(int Corr, int Incorr){
    CorrCount->setText(QString("<font color=\"#ff0000\">錯誤數 %1</font> | <font color=\"#00dd12\">%2 正確數</font>").arg(Incorr).arg(Corr));
}

QuestionTemplate::MultipleChoice::MultipleChoice(Question::MultipleChoice* Question, QWidget* parent) : QuestionTemplate::QuestionBase(parent), TargetQuestion(Question){
    Label = new QLabel(QString("(%1) %2").arg(this->QuestionIndex).arg(TargetQuestion->Question), this);
    Label->setGeometry(100,120,800,135);
    Label->setAlignment(Qt::AlignCenter);
    Label->setFont({DEFAULTFONT,24});

    OptionA = new QPushButton(QString("A %1").arg(TargetQuestion->Options[0]), this);
    OptionA->setGeometry(200,266,270,140);
    OptionA->SETPUSHBUTTONFONT;
    connect(OptionA, BUTTON_CLICK, this, [this]{AnswerCheck(Question::Option::A);});
    OptionA->__ANSWERTAG;

    OptionB = new QPushButton(QString("B %1").arg(TargetQuestion->Options[1]), this);
    OptionB->setGeometry(530,266,270,140);
    OptionB->SETPUSHBUTTONFONT;
    connect(OptionB, BUTTON_CLICK, this, [this]{AnswerCheck(Question::Option::B);});
    OptionB->__ANSWERTAG;


    OptionC = new QPushButton(QString("C %1").arg(TargetQuestion->Options[2]), this);
    OptionC->setGeometry(200,435,270,140);
    OptionC->SETPUSHBUTTONFONT;
    connect(OptionC, BUTTON_CLICK, this, [this]{AnswerCheck(Question::Option::C);});
    OptionC->__ANSWERTAG;

    OptionD = new QPushButton(QString("D %1").arg(TargetQuestion->Options[3]),this);
    OptionD->setGeometry(530,435,270,140);
    OptionD->SETPUSHBUTTONFONT;
    connect(OptionD, BUTTON_CLICK, this, [this]{AnswerCheck(Question::Option::D);});
    OptionD->__ANSWERTAG;

    OptiontoButton = {{Question::Option::A,OptionA},{Question::Option::B,OptionB},{Question::Option::C,OptionC},{Question::Option::D,OptionD}};

    PrevQuestion = new QPushButton("<- 上一題",this);
    PrevQuestion->setGeometry(50,590,160,60);
    PrevQuestion->SETPUSHBUTTONFONT;
    PrevQuestion->setVisible(this->QuestionIndex != 1);

    NextQuestion = new QPushButton("下一題 ->",this);
    NextQuestion->setGeometry(790,590,160,60);
    NextQuestion->SETPUSHBUTTONFONT;
    NextQuestion->setEnabled(false);

    CorrCount = new QLabel(this);
    CorrCount->setGeometry(200,10,250,50);
    CorrCount->setAlignment(Qt::AlignCenter);
    CorrCount->setFont({"Microsoft Jhenghei",21});

    Progress = new QLabel(this);
    Progress->setGeometry(730,10,250,50);
    Progress->setAlignment(Qt::AlignCenter);
    Progress->setFont({"Microsoft Jhenghei",21});

    MuteDisplay = new QPushButton(this);
    MuteDisplay->setGeometry(570,10,50,50);
    MuteDisplay->setObjectName("MuteDisplay");
}

void QuestionTemplate::MultipleChoice::AnswerCheck(Question::Option Input){
    if (!Answered){
        emit TimerTab();
        Answered = true;
        this->setStyleSheet("QPushButton#AnswerOption{background-color: #e3e3e3; color: black; border-radius: 5px; border-color: #2f2f2f;}");
        OptiontoButton[Input]->SETCHOSEN;
        bool Corr = Input == TargetQuestion->CorrOption;
        if (!Corr){
            COOLDOWN;
            OptiontoButton[Input]->SETWRONGANDPLAY;
            COOLDOWN;
            OptiontoButton[TargetQuestion->CorrOption]->SETRIGHT;
        }
        else{
            COOLDOWN;
            OptiontoButton[Input]->SETRIGHTANDPLAY;
        }
        COOLDOWN;
        NextQuestion->setEnabled(true);
        emit Score(Corr);
    }
}

void QuestionTemplate::MultipleChoice::SetIndex(int index){
    this->QuestionIndex = index;
    Label->setText(QString("(%1) %2").arg(this->QuestionIndex).arg(TargetQuestion->Question));
    PrevQuestion->setVisible(this->QuestionIndex != 1);
}

QuestionTemplate::TrueorFalse::TrueorFalse(Question::TrueorFalse* Question, QWidget* parent) : QuestionTemplate::QuestionBase(parent), TargetQuestion(Question){
    Label = new QLabel(QString("(%1) %2").arg(QuestionIndex).arg(TargetQuestion->Question), this);
    Label->setGeometry(100,120,800,125);
    Label->setAlignment(Qt::AlignCenter);
    Label->setFont({"Microsoft Jhenghei",24});

    TrueOption = new QPushButton("對", this);
    TrueOption->setGeometry(210,350,250,125);
    TrueOption->SETPUSHBUTTONFONT;
    connect(TrueOption, BUTTON_CLICK, this, [this]{AnswerCheck(true);});
    TrueOption->__ANSWERTAG;

    FalseOption = new QPushButton("錯", this);
    FalseOption->setGeometry(560,350,250,125);
    FalseOption->SETPUSHBUTTONFONT;
    connect(FalseOption, BUTTON_CLICK, this, [this]{AnswerCheck(false);});
    FalseOption->__ANSWERTAG;

    PrevQuestion = new QPushButton("<- 上一題",this);
    PrevQuestion->setGeometry(50,610,160,60);
    PrevQuestion->SETPUSHBUTTONFONT;

    NextQuestion = new QPushButton("下一題 ->",this);
    NextQuestion->setGeometry(790,610,160,60);
    NextQuestion->SETPUSHBUTTONFONT;
    NextQuestion->setEnabled(false);

    CorrCount = new QLabel(this);
    CorrCount->setGeometry(200,10,250,50);
    CorrCount->setAlignment(Qt::AlignCenter);
    CorrCount->setFont({"Microsoft Jhenghei",21});

    Progress = new QLabel(this);
    Progress->setGeometry(730,10,250,50);
    Progress->setAlignment(Qt::AlignCenter);
    Progress->setFont({"Microsoft Jhenghei",21});

    MuteDisplay = new QPushButton(this);
    MuteDisplay->setGeometry(570,10,50,50);
    MuteDisplay->setObjectName("MuteDisplay");
}

void QuestionTemplate::TrueorFalse::AnswerCheck(bool Input){
    if (!Answered){
        emit TimerTab();
        Answered = true;
        this->setStyleSheet("QPushButton#AnswerOption{background-color: #e3e3e3; color: black; border-radius: 5px; border-color: #2f2f2f;}");
        OptiontoButton(Input)->SETCHOSEN;
        bool Corr = Input == TargetQuestion->CorrOption;
        if (!Corr){
            COOLDOWN;
            OptiontoButton(Input)->SETWRONGANDPLAY;
            COOLDOWN;
            OptiontoButton(TargetQuestion->CorrOption)->SETRIGHT;
        }
        else{
            COOLDOWN;
            OptiontoButton(Input)->SETRIGHTANDPLAY;
        }
        COOLDOWN;
        NextQuestion->setEnabled(true);
        emit Score(Corr);
    }
}

void QuestionTemplate::TrueorFalse::SetIndex(int index){
    this->QuestionIndex = index;
    Label->setText(QString("(%1) %2").arg(this->QuestionIndex).arg(TargetQuestion->Question));
    PrevQuestion->setVisible(this->QuestionIndex != 1);
}

QPushButton* QuestionTemplate::TrueorFalse::OptiontoButton(bool input){return input? TrueOption : FalseOption;}
