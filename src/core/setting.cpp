#include "setting.h"

bool Core::AppSetting::loadAria2Setting() {
    CSimpleIniA iniA;
    iniA.SetUnicode();
    SI_Error error = iniA.LoadFile("/Users/Nonevent/CLionProjects/R0x1/config.conf");
    if (error < 0) {
        // TODO catch error
        return false;
    }
    CSimpleIniA::TNamesDepend keys;
    iniA.GetAllKeys("", keys);
    for (const auto &entry : keys) {
        auto value = iniA.GetValue("", entry.pItem, "none");
        for (const auto &setting : DefaultSettings) {
            auto pred = [value, entry](const auto &setting) -> bool {
                return (setting->key() == entry.pItem) && (setting->value() == value);
            };
            if (entry.pItem == setting->key() && !std::any_of(settingList.begin(), settingList.end(), pred)) {
                settingList.push_back(
                    std::make_shared<SettingItem>(QString(entry.pItem), QString(value),setting->unit()));
            }
        }
    }
    return true;
}
namespace Core {
#define add std::make_shared<Core::SettingItem>
}// namespace Core
const QList<Core::AppSetting::SettingItemPtr> Core::AppSetting::DefaultSettings{
    add("dir", "/download"),
    //    std::make_shared<Core::SettingItem>("dir", "true"),
    add("disk-cache", "32M", Core::SettingItem::Number),
    add("continue", "true", Core::SettingItem::Bool),
    add("rpc-listen-port", "6800"),
    add("file-allocation", "60", Core::SettingItem::None),
    add("timeout", "none"),
    add("always-resume", "true", Core::SettingItem::Bool),
    add("timeout", "false", Core::SettingItem::Bool),
    add("max-resume-failure-tries", "0", Core::SettingItem::Number),
    add("remote-time", "true", Core::SettingItem::Bool),
    add("input-file", "/root/.aria2/aria2.session", Core::SettingItem::None),
    add("save-session", "/root/.aria2/aria2.session", Core::SettingItem::None),
    add("save-session-interval", "1", Core::SettingItem::Number),
    add("force-save", "false", Core::SettingItem::Bool),
    add("max-file-not-found", "10", Core::SettingItem::Number),
    add("max-tries", "0", Core::SettingItem::None),
    add("retry-wait", "10", Core::SettingItem::None),
    add("connect-timeout", "10", Core::SettingItem::Number),
    add("max-concurrent-downloads", "5", Core::SettingItem::None),
};
