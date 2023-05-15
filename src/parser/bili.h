
#pragma once
#include "parser.h"
namespace URLParser {

class BiliURLParser : public Parser {

   public:
    Result getResult(std::string& url) const override;

   private:
    std::string getVideoId(std::string &url);
};

}// namespace URLParser
