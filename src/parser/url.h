
#pragma once
#include "bili.h"

#include <memory>
#include <string>

namespace URLParser {

class URL {
   private:
    enum TYPE {
        DEFAULT,
        BILIBILI,
        YOUTUBE
    };
    std::shared_ptr<Parser> parser = nullptr;
    std::string &url;

    bool checkUrl();
    static TYPE checkType();

   public:
    explicit URL(const std::string &url);

    Result get();

   private:
    Result callBili();
    Result callDefault();
};

}// namespace URLParser
