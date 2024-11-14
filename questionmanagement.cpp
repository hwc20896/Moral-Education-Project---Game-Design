#include "questionmanagement.h"
#include <stdexcept>
#include "outrowidget.h"
#include <algorithm>
using namespace std::chrono;
using QTQB = QuestionTemplate::QuestionBase;

#ifdef DEBUG
#include <QDebug>
#define cout qDebug()
#endif

QuestionManagement::QuestionManagement(const std::deque<QuestionTemplate::QuestionBase*>& Questions, int Quantity, QWidget* parent) :
  QStackedWidget(parent), Quantity(Quantity){
    aout = new QAudioOutput;
    aout->setVolume(PlayVolume);

    bgm = new QMediaPlayer;
    bgm->setAudioOutput(aout);
    bgm->setLoops(-1);
    bgm->setSource(QUrl("qrc:/sound/rsc/OMFG_Pizza.mp3"));

    auto order = GetRandomOrder(Questions, this->Quantity);
    for (int i=0;i<this->Quantity;i++){
        auto* Target = Questions[order[i]];
        Target->setObjectName("AnsWidget");
        this->addWidget(Target);
        this->Questions.push_back(Target);
        connect(Target->PrevQuestion,&QPushButton::clicked,this,[=]{
            if (currentIndex() != 0) setCurrentIndex(currentIndex()-1);
        });
        connect(Target->NextQuestion,&QPushButton::clicked,this,[=]{
            if (currentIndex() != count()-1) {
                setCurrentIndex(currentIndex()+1);
                Start = timer.now();
            }
            else EndGame();
        });
        connect(Target,&QTQB::TimerTab,this,[=]{
            End = timer.now();
            int64_t time = duration_cast<milliseconds>(End-Start).count();
            cout << QString("Took %1 ms to answer this question.").arg(time);
            TimeStamps.push_back(time);
        });
        connect(Target,&QTQB::Score,this,[=](bool Corr){
            if (Corr) CorrCount++;
            else IncorrCount++;
            IndexAccessed++;
            UpdatePages();
        });
        connect(Target->MuteDisplay,&QPushButton::clicked,this,[=]{
            SetMutedState(!IsMuted);
            IsMuted = !IsMuted;
        });
        Target->SetIndex(i+1);
        Target->SetScore(CorrCount,IncorrCount);
        if (i==this->Quantity-1) Target->NextQuestion->setText("完成");
    }
    UpdatePages();
    this->setCurrentIndex(0);
    SetMutedState(false);

    Start = timer.now();

    this->setStyleSheet("QStackedWidget{background-image: url(:/image/rsc/qnabg.jpg);}"
                        "QPushButton#AnswerOption{background-color: #e3e3e3; color: black; border-radius: 5px; border-color: #2f2f2f;}"
                        "QPushButton#AnswerOption:hover{background-color: #6d7dff; color: black;}"
                        "QLabel{background-color: rgba(211,211,211,0.3);}");
}

void QuestionManagement::UpdatePages(){
    for (auto* page : Questions) {
        page->SetScore(CorrCount,IncorrCount);
        page->SetProgress(IndexAccessed,Quantity);
    }
}

void QuestionManagement::SetMutedState(bool IsMuted){
    for (auto* p : this->Questions){
        p->MuteDisplay->setStyleSheet(QString("#MuteDisplay{background-image: url(%1);"
                                              "border-radius: 5px;}").arg(IsMuted?":/mutestate/rsc/mute.jpg":":/mutestate/rsc/unmute.jpg"));
    }
    aout->setMuted(IsMuted);
}

std::vector<int> QuestionManagement::GetRandomOrder(const std::deque<QuestionTemplate::QuestionBase*>& Questions, size_t Quantity){
    if (Questions.size() < Quantity) throw std::out_of_range("Unable to get Question Order: Question List empty");
    std::vector<int> Output, Copy = range(Questions.size());
    for (size_t i=0; i<Quantity;i++){
        srand(time(0));
        size_t Target = (size_t)GetRandomNumber(Copy.size());
        Output.push_back(Copy[Target]);
        Copy.erase(Copy.begin()+Target);
    }
    return Output;
}

int QuestionManagement::GetRandomNumber(int High, int Low){return rand()%(High - Low) + Low;}

std::vector<int> QuestionManagement::range(int Lim){
    std::vector<int> Out;
    for (int i=0;i<Lim;i++) Out.push_back(i);
    return Out;
}

void QuestionManagement::EndGame(){
    bgm->disconnect();
    bgm->stop();

    int64_t totaltime = 0;
    std::for_each(TimeStamps.begin(), TimeStamps.end(), [&](int time){totaltime += time;});

    #ifdef DEBUG
        cout << QString("Time used: %1ms.").arg(totaltime);
    #endif

    this->close();
    OutroWidget* outro = new OutroWidget(CorrCount, IncorrCount, totaltime);
    outro->setFixedSize(1000,700);
    outro->show();
    outro->result->PageSetup();
}
