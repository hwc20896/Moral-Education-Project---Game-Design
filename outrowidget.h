#ifndef OUTROWIDGET_H
#define OUTROWIDGET_H
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QSoundEffect>

class ResultWidget : public QWidget{
    public:
        ResultWidget(int CorrCount, int IncorrCount, int64_t TotalTime, QWidget* parent = 0);
        QPushButton* ToEnd;
        void PageSetup();
    private:
        void Cooldown(int duration);
        QString GetTier(int CorrCount, int TotalCount);
        QString TimeDisplay(double dur);
        int CorrCount, IncorrCount;
        int QuestionCount;
        QLabel* Score,* PrecisionRate,* RankDisplay,* TimeUsed,* AvgTime;
        bool Shown = false;
        QSoundEffect* effect;
};

class EndWidget : public QWidget{
    public:
        EndWidget(QWidget* parent = 0);
        QPushButton* ToInfo;
};

class InfoWidget : public QWidget{
    public:
        InfoWidget(QWidget* parent = 0);
        QPushButton* Return;
};

class OutroWidget : public QStackedWidget{
    public:
        OutroWidget(int CorrCount, int IncorrCount, int64_t TotalTime, QWidget* parent = 0);
        ResultWidget* result;
};

#endif // OUTROWIDGET_H
