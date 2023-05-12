#pragma once

#include "platform/platform.h"
#include "ui/about/aboutpage.h"
#include "ui/add/addpage.h"
#include "ui/components/toast.h"
#include "ui/help/helppage.h"
#include "ui/setting/settingpage.h"
#include "ui/sidebar/sidebar.h"
#include "ui/task/taskpage.h"
#include <QStackedWidget>

namespace Ui {
class BaseWindow final : public Platform::FramelessWindow {
    Q_OBJECT

   public:
    explicit BaseWindow(QWidget *parent = nullptr);
    //  ~MainWindow() override;
   public:
    QHBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;
    //    Toast *toast;

    Ui::SideBar *sideBar;
    Ui::AddPage *addPage;
    Ui::TaskPage *taskPage;
    Ui::SettingPage *settingPage;
    Ui::HelpPage *helpPage;
    Ui::AboutPage *aboutPage;

   public:
    [[nodiscard]] QString getInputUrl() const;
    void loadSettingUi(const QList<Core::AppSetting::SettingItemPtr> &setting);
};

}// namespace Ui
