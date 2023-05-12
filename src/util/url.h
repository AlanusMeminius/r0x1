/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/22 18:07
* @description: 
*/
#pragma once
#include <QString>

static const std::string WwwUrl = "https://www.BILIBILI.com";
static const std::string ShareWwwUrl = "https://www.BILIBILI.com/s";
static const std::string ShortUrl = "https://b23.tv/";
static const std::string MobileUrl = "https://m.BILIBILI.com";
static const std::string SpaceUrl = "https://space.BILIBILI.com";

static const std::string VideoUrl = WwwUrl + "/video/";
static const std::string BangumiUrl = WwwUrl + "/bangumi/play/";
static const std::string BangumiMediaUrl = WwwUrl + "/bangumi/media/";
static const std::string CheeseUrl = WwwUrl + "/cheese/play/";
static const std::string FavoritesUrl1 = WwwUrl + "/medialist/detail/";
static const std::string FavoritesUrl2 = WwwUrl + "/medialist/play/";

namespace Util {
class Url {
 public:
  static bool isUrl(const QString& text);
  static bool isBvUrl(const QString& text);
  static bool isBvId(const QString& text);
  static QString enableHttps(const QString& url);
  static QString deleteUrlParam(const QString& url);
  static QString getVideoId(const QString& text);
  static QString getId(const QString& url, const QString& baseUrl);
};
}

