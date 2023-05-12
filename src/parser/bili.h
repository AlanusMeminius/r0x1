/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/25 21:45
* @description: 
*/
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
