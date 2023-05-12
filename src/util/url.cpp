/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/22 18:07
* @description: 
*/
#include "url.h"
#include <QRegularExpression>

bool Util::Url::isUrl(const QString &text) {
  // https://blog.csdn.net/qq569699973/article/details/94636893

  QRegularExpression re("([hH][tT]{2}[pP]:"
                        "//|[hH][tT]{2}[pP][sS]://"
                        "|[wW]{3}.|[wW][aA][pP]."
                        "|[fF][tT][pP].|[fF][iI][lL][eE].)"
                        "[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
  QRegularExpressionMatch match = re.match(text);
  return match.hasMatch();
}

bool Util::Url::isBvUrl(const QString &text) {
  return isBvId(getVideoId(text));
}
bool Util::Url::isBvId(const QString &text) {
  return text.startsWith("BV") && text.length() == 12;
}
QString Util::Url::getVideoId(const QString &text) {
  return getId(text, QString::fromLocal8Bit(VideoUrl.data()));
}
QString Util::Url::getId(const QString &url, const QString &baseUrl) {
  if (!isUrl(url)) {
    return {};
  }

  QString tempUrl = enableHttps(url);
  tempUrl = deleteUrlParam(tempUrl);
  tempUrl = tempUrl.replace(QString::fromLocal8Bit(ShareWwwUrl.data()), QString::fromLocal8Bit(WwwUrl.data()));
  tempUrl = tempUrl.replace(QString::fromLocal8Bit(MobileUrl.data()), QString::fromLocal8Bit(WwwUrl.data()));

  if (tempUrl.contains("b23.tv/ss") || tempUrl.contains("b23.tv/ep")) {
    tempUrl = tempUrl.replace(QString::fromLocal8Bit(ShortUrl.data()), QString::fromLocal8Bit(BangumiUrl.data()));
  } else {
    tempUrl = tempUrl.replace(QString::fromLocal8Bit(ShortUrl.data()), QString::fromLocal8Bit(VideoUrl.data()));
  }

  if (!tempUrl.startsWith(baseUrl)) {
    return {};
  }

  return tempUrl.replace(baseUrl, "");
}
QString Util::Url::enableHttps(const QString &url) {
  QString result = url;
  return result.replace(QString("http://"), QString("https://"));
}
QString Util::Url::deleteUrlParam(const QString &url) {
  QStringList strList = url.split("?");
  return strList[0].endsWith("/") ? strList[0].remove(strList[0].size() - 1, 1) : strList[0];
}
