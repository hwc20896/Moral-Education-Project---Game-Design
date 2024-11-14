#ifndef MAINWIDGET
#define MAINWIDGET
#include <QStackedWidget>
#include "questiontemplate.h"
#include "introwidget.h"

class MainWidget : public QStackedWidget{
    public:
        MainWidget(QWidget* parent = 0);
    private:
        QTMC *Question1, *Question2, *Question3, *Question4, *Question5, *Question6,
             *Question8, *Question14, *Question15, *Question17, *Question20;
        QTTF *Question9, *Question10, *Question12, *Question13, *Question16, *Question18, *Question19,
             *Question21, *Question22, *Question23, *Question24;
        void StartGame();
        IntroWidget* initpage;

};


#endif
