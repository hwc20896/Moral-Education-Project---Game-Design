#pragma once
#ifndef QUESTIONMANAGEMENT
#define QUESTIONMANAGEMENT
#include <QStackedWidget>
#include <deque>
#include <vector>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <chrono>
#include "questiontemplate.h"
using namespace std::chrono;

class QuestionManagement : public QStackedWidget{
    public:
        QuestionManagement(const std::deque<QuestionTemplate::QuestionBase*>& Questions, int Quantity, QWidget* parent = 0);
        void SetMutedState(bool IsMuted);
        QMediaPlayer* bgm;
    private:
        std::vector<int> GetRandomOrder(const std::deque<QuestionTemplate::QuestionBase*>& Questions, size_t Quantity);
        int Quantity;
        void UpdatePages();
        void EndGame();
        int GetRandomNumber(int High,int Low=0);
        std::vector<int> range(int Lim);  // [0, Lim)
        std::deque<QuestionTemplate::QuestionBase*> Questions;
        int PageIndex = 0, IndexAccessed = 0;
        int CorrCount=0, IncorrCount=0;
        QAudioOutput* aout;
        high_resolution_clock timer;
        time_point<high_resolution_clock> Start, End;
        std::vector<int64_t> TimeStamps;
        bool IsMuted;
        static constexpr float PlayVolume = 0.5;
};

#endif
