#ifndef INTROWIDGET_H
#define INTROWIDGET_H
#include <QWidget>
#include <QPushButton>

class IntroWidget : public QWidget{
    public:
        IntroWidget(QWidget* parent = 0);
        QPushButton* RuleButton,* StartButton;
        bool IsMuted = false;
};




#endif // INTROWIDGET_H
