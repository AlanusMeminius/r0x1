
#include "url.h"
#include <regex>
#include <utility>

namespace URLParser {

URL::URL(QString url) : url(std::move(url)) {
}
bool URL::isURI() {
    QRegularExpression re(
        "([hH][tT]{2}[pP]://|[hH][tT]{2}[pP][sS]://|[wW]{3}.|[wW][aA][pP].|[fF][tT][pP].|[fF][iI][lL][eE].)"
        "[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
    return re.match(url).hasMatch();
}
URL::TYPE URL::checkType() {

    return URL::DEFAULT;
}
Result URL::get() {
    if (!isURI()) {
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