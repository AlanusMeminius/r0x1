
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
