#include "rulewidget.h"
#include <QString>
#define FONT "Microsoft JhengHei"
#define BUTTON_CLICK &QPushButton::clicked
#define SOUNDINRULE true

#if SOUNDINRULE
#include <QSoundEffect>
#endif

RuleWidget::RuleWidget(QWidget* parent) : QWidget(parent){
    QLabel* RuleTitle = new QLabel("遊戲規則",this);
    RuleTitle->setGeometry(420,35,160,40);
    RuleTitle->setAlignment(Qt::AlignCenter);
    RuleTitle->setFont(QFont(FONT,28));

    QLabel* RuleText = new QLabel(this);
    RuleText->setFont(QFont(FONT,15));
    RuleText->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    ReturnButton = new QPushButton("返回",this);
    ReturnButton->setGeometry(410,600,180,60);
    ReturnButton->setFont(QFont(FONT,16));

    #if SOUNDINRULE  // Debugger Version
        RuleText->setText("（遊戲以程序檔(.exe)呈現）\n\n玩法：\n在按開始遊戲後，玩家共需回答八條問題。\n答對了（選擇正確答案）可直接進入下一題，並獲得「甜美」的恭喜音效。\n答錯（選擇錯誤答案）則自動出現正確答案，並獲得「甜美」的「鼓勵」音效。\n答題庫共有22條，每輪遊戲會隨機抽出8題進行遊戲。"
                          "\n\n等級劃分：（正確率）\n80% ~ 100% -> S\n55% ~ 80% -> A\n30% ~ 55% -> B\n0% ~ 30% -> C");
        RuleText->setGeometry(35,110,700,475);

        QSoundEffect* CorrSoundPreview = new QSoundEffect;
        CorrSoundPreview->setSource(QUrl("qrc:/sound/rsc/bingo.wav"));
        CorrSoundPreview->setVolume(.5);

        QSoundEffect* IncorrSoundPreview = new QSoundEffect;
        IncorrSoundPreview->setSource(QUrl("qrc:/sound/rsc/ohno.wav"));
        IncorrSoundPreview->setVolume(.5);

        QLabel* SoundPreview = new QLabel("音效預覽",this);
        SoundPreview->setAlignment(Qt::AlignCenter);
        SoundPreview->setGeometry(760,149,200,62);
        SoundPreview->setFont(QFont(FONT,28));

        QPushButton* BingoSound = new QPushButton("「甜美」的恭喜音效",this);
        BingoSound->setGeometry(760,266,200,50);
        BingoSound->setFont(QFont(FONT,12));
        connect(BingoSound,BUTTON_CLICK,this,[=]{CorrSoundPreview->play();});

        QPushButton* BooSound = new QPushButton("「甜美」的「鼓勵」音效",this);
        BooSound->setGeometry(760,369,200,50);
        BooSound->setFont(QFont(FONT,12));
        connect(BooSound,BUTTON_CLICK,this,[=]{IncorrSoundPreview->play();});
    #else   // Public Version
        RuleText->setText("在按開始遊戲後，玩家共需回答八條問題。\n選擇正確答案可直接進入下一題，並獲得甜美的恭喜音效。\n選擇錯誤答案則自動出現正確答案，並獲得甜美的鼓勵音效。\n答題庫共有22條，每輪遊戲會隨機抽出8題進行遊戲。");
        RuleText->setGeometry(75,110,850,475);
    #endif
}
