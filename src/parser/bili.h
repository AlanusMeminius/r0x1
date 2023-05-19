
#pragma once
#include "parser.h"
namespace URLParser {

class BiliURLParser : public Parser {

   public:
    Result getResult(QString url) const override;

   private:
    std::string getVideoId(QString url);
};

}// namespace URLParser
