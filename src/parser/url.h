
#pragma once
#include "bili.h"
#include <QString>
#include <QRegularExpression>
namespace URLParser {

class URL {
   private:
    enum TYPE {
        DEFAULT,
        BILIBILI,
        YOUTUBE
    };
    std::shared_ptr<Parser> parser = nullptr;
    QString url;

    bool isURI();
    static TYPE checkType();

   public:
    explicit URL(QString url);

    Result get();

   private:
    Result callBili();
    Result callDefault();
};

}// namespace URLParser
