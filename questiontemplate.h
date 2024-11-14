#pragma once
#ifndef QUESTIONTEMPLATE
#define QUESTIONTEMPLATE
#include <QWidget>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QEventLoop>
#include <array>
#include <QMap>
#include <QSoundEffect>
#include <QAudioOutput>
#define BUTTON_CLICK &QPushButton::clicked

namespace Question{
    struct MultipleChoice;
    struct TrueorFalse;
    struct CorrDisplay;
    enum class Option{A,B,C,D};
}

namespace QuestionTemplate{
    class QuestionBase;
    class MultipleChoice;
    class TrueorFalse;
}

struct Question::MultipleChoice{
    MultipleChoice(const QString& Question, const std::array<QString,4>& Options, Option CorrOption) :
        Question(Question), Options(Options), CorrOption(CorrOption){}
    QString Question;
    std::array<QString,4> Options;
    Option CorrOption;
};

struct Question::TrueorFalse{
    TrueorFalse(const QString& Question, bool CorrOption) : Question(Question), CorrOption(CorrOption){}
    QString Question;
    bool CorrOption;
};

struct Question::CorrDisplay{
    int CorrCount, IncorrCount;
};

class QuestionTemplate::QuestionBase : public QWidget{
    Q_OBJECT
    public:
        QuestionBase(QWidget* parent = 0);
        QPushButton *PrevQuestion, *NextQuestion;
        QLabel* CorrCount, *Progress;
        QPushButton* MuteDisplay;
        bool Answered = false;
        virtual void SetIndex(int index){this->QuestionIndex = index;}
        void SetScore(int Corr, int Incorr);
        void SetProgress(int CurrentProgress, int Total);
        void SetCooldown(size_t ms);
    signals:
        void TimerTab();
        void Score(bool Corr);
        void SwitchMuteStatus(bool MuteStatus);
    protected:
        int QuestionIndex = 0;
        QAudioOutput* aout;
        QSoundEffect* CorrSound, *IncorrSound;
};

class QuestionTemplate::MultipleChoice : public QuestionBase{
    Q_OBJECT
    public:
        MultipleChoice(Question::MultipleChoice* Question, QWidget* parent = 0);
        void SetIndex(int index);
    private:
        void AnswerCheck(Question::Option Input);
        Question::MultipleChoice* TargetQuestion;
        Question::Option InputOption;
        QPushButton *OptionA, *OptionB, *OptionC, *OptionD;
        QMap<Question::Option, QPushButton*> OptiontoButton;
        QLabel* Label;
};

class QuestionTemplate::TrueorFalse : public QuestionBase{
    Q_OBJECT
    public:
        TrueorFalse(Question::TrueorFalse* Question, QWidget* parent = 0);
        void SetIndex(int index);
    private:
        void AnswerCheck(bool Input);
        QPushButton* TrueOption, *FalseOption;
        Question::TrueorFalse* TargetQuestion;
        bool InputOption;
        QLabel* Label;
        QPushButton* OptiontoButton(bool input);
};

using QMC = Question::MultipleChoice;
using QTF = Question::TrueorFalse;
using QO = Question::Option;
using QTMC = QuestionTemplate::MultipleChoice;
using QTTF = QuestionTemplate::TrueorFalse;

#endif
