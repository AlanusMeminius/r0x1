/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/25 22:50
* @description: 
*/
#include "url.h"
#include <regex>

namespace URLParser {

URL::URL(const std::string &url) : url(const_cast<std::string &>(url)) {
}
bool URL::checkUrl() {
    std::regex regex("([hH][tT]{2}[pP]://|[hH][tT]{2}[pP][sS]://|[wW]{3}.|[wW][aA][pP].|[fF][tT][pP].|[fF][iI][lL][eE].)[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
    return std::regex_match(url, regex);
}
URL::TYPE URL::checkType() {

    return URL::BILIBILI;
}
Result URL::get() {
    if (!checkUrl()) {
        return {};
    }
    switch (checkType()) {
        case DEFAULT:
            return callDefault();
        case BILIBILI:
            return callBili();
        case YOUTUBE:
            return {"youtube url"};
    }
}
Result URL::callBili() {
    parser = std::make_shared<BiliURLParser>();
    return parser->getResult(url);
}
Result URL::callDefault() {
    return {url, DEFAULT};
}

}// namespace URLParser