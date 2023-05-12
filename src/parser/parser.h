/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/25 22:53
* @description: 
*/
#pragma once
#include <string>
namespace URLParser {

struct Result {
    std::string urls;
    int type;
};

class Parser {
   public:
    virtual Result getResult(std::string& url) const = 0;
};

}// namespace URLParser
