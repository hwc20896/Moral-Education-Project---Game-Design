#ifndef RULEWIDGET_H
#define RULEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class RuleWidget : public QWidget{
    public:
        RuleWidget(QWidget* parent = 0);
        QPushButton* ReturnButton;
};

#endif // RULEWIDGET_H
