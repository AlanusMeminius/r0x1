/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/5/9 23:49
* @description: 
*/
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
    add("dir", "true"),
    //    std::make_shared<Core::SettingItem>("dir", "true"),
    add("disk-cache", "32M", Core::SettingItem::Mb),
    add("continue", "true", Core::SettingItem::Bool),
    add("rpc-listen-port", "6800", Core::SettingItem::Number),
    add("timeout", "60", Core::SettingItem::Second),
};
