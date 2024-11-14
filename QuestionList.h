#pragma once
#ifndef QUESTIONLIST_H
#define QUESTIONLIST_H
#include "questiontemplate.h"
#include <QString>

namespace QuestionList{
    QMC* Question1 = new QMC("我國的最高國家權力機關的執行機關是：",
                             {"國務院","全國人民代表大會","國家主席","最高人民法院"},
                             QO::A);

    QMC* Question2 = new QMC("根據《憲法》規定，中華人民共和國的最高\n審判機關是：",
                             {"最高人民法院","最高人民檢察院","國務院","中央軍事委員會"},
                             QO::A);

    QMC* Question3 = new QMC("澳門特別行政區行政長官\n任期_年,可連任___次。",
                             {"3, 1","5, 1","4, 2","10, 2"},
                             QO::B);

    QMC* Question4 = new QMC("澳門特別行政區法定貨幣為：",
                             {"台幣","港幣","人民幣","澳門幣"},
                             QO::D);

    QMC* Question5 = new QMC("澳門特別行政區不實行社會主義\n制度和政策，保持原有的資本主義\n制度和生活方式，___年不變。",
                             {"三十","五十","二十","一百"},
                             QO::B);

    QMC* Question6 = new QMC("《中華人民共和國澳門特別行政區\n基本法》自___起實施。",
                             {"1990年10月1日","1990年12月20日","1999年10月1日","1999年12月20日"},
                             QO::D);

    QMC* Question8 = new QMC("全國人民代表大會每屆任期___年。",
                             {"二","三","四","五"},
                             QO::D);

    QTF* Question9 = new QTF("中央人民政府可在澳門特別行政區徵稅。",false);

    QTF* Question10 = new QTF("中華人民共和國公民有言論、出版、\n集會 、結社、遊行 、示威的自由。",true);

    QTF* Question12 = new QTF("澳門特別行政區的區旗是繪有\n五星、蓮花、大橋、海水圖案的紅色旗幟。",false);

    QTF* Question13 = new QTF("中華人民共和國公民有依照法律納稅的義務。",true);

    QMC* Question14 = new QMC("澳門特別行政區行政長官由年滿四十周歲，\n在澳門通常居住連續滿__年的澳門特別行政區\n永久性居民中的中國公民擔任。",
                              {"十年","二十年","三十年","四十年"},
                              QO::B);

    QMC* Question15 = new QMC("中華人民共和國國歌是：",
                              {"《起來》","《七子之歌》","《義勇軍曲》","《義勇軍進行曲》"},
                              QO::D);

    QTF* Question16 = new QTF("澳門特別行政區終審權屬於\n中華人民共和國最高人民法院。",false);

    QMC* Question17 = new QMC("中華人民共和國首都是：",
                              {"北京","南京","天津","上海"},
                              QO::A);

    QTF* Question18 = new QTF("我國《憲法》明確規定，\n國家推廣全國通用的普通話。",true);

    QTF* Question19 = new QTF("中華人民共和國國徽，\n中間是五星照耀下的天安門，\n周圍是鐮刀和錘子。",false);

    QMC* Question20 = new QMC("以下哪個地方不屬於澳門特別行政區管轄範圍？",
                              {"澳門半島","氹仔島","路環島","橫琴島"},
                              QO::D);

    QTF* Question21 = new QTF("根據「一國兩制」方針，澳門特別行政區不實行\n社會主義的制度和政策。",true);

    QTF* Question22 = new QTF("澳門特別行政區依法保障澳門特別行政區居民\n和其他人的權利和自由。",true);

    QTF* Question23 = new QTF("澳門特別行政區實行高度自治，\n享有獨立的司法權和終審權。",true);

    QTF* Question24 = new QTF("澳門特別行政區永久性居民和非永久性居民\n依法享有選舉權和被選舉權。",false);

    constexpr int TotalQuestion = 8;
}

#endif // QUESTIONLIST_H
