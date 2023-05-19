
#pragma once
#include <QString>
namespace URLParser {

struct Result {
    QString urls;
    int type;
};

class Parser {
   public:
    virtual Result getResult(QString url) const = 0;
};

}// namespace URLParser
