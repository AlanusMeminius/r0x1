/*
* @author: NonEvent
* @email: nononevent@outlook.com
* @date: 2023/4/28 17:20
* @description:
*/
#include "framelesswindow.h"
#include <AppKit/AppKit.h>
#import <QOperatingSystemVersion>

class BlurEffect : public QObject {
    Q_OBJECT
   public:
    explicit BlurEffect() = default;
    void setBlurEffect(QWidget *parent, QWidget *central) {
        const auto visualEffectViewClass = NSClassFromString(@"NSVisualEffectView");
        if (!visualEffectViewClass) {
            return;
        }
        const auto view = (NSView *) parent->winId();
        view.wantsLayer = YES;
        NSVisualEffectView *const blurView =
            [[visualEffectViewClass alloc] initWithFrame:view.bounds];
        if (!blurView) return;
        blurView.material = NSVisualEffectMaterialPopover;
        blurView.blendingMode = NSVisualEffectBlendingModeBehindWindow;
        blurView.state = NSVisualEffectStateFollowsWindowActiveState;
        BlurView = blurView;

        const auto widgetView = (NSView *) central->winId();
        [view addSubview:blurView positioned:NSWindowBelow relativeTo:widgetView];
        WidgetView = widgetView;
    };

   public:
    NSView *BlurView = nil;
    NSView *WidgetView = nil;
};
// TODO 三个按钮行为重写：1.最小化隐藏到托盘 2.最大化窗口没有缩放 3.按照设定退出行为
FramelessWindow::FramelessWindow(QWidget *parent)
    : QWidget(parent),
      centralWidget(new QWidget),
      layout(new QGridLayout),
      blurEffect(new BlurEffect) {
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(centralWidget, 0, 0, 1, 1);
    layout->setSpacing(0);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyledBackground, true);

    blurEffect->setBlurEffect(this, centralWidget);
}
void FramelessWindow::paintEvent(QPaintEvent *event) {
    blurEffect->BlurView.frame = blurEffect->WidgetView.frame;
    hideSystemTitleBar();
    QWidget::paintEvent(event);
}
void FramelessWindow::resizeEvent(QResizeEvent *event) {
    blurEffect->BlurView.frame = blurEffect->WidgetView.frame;
    QWidget::resizeEvent(event);
}
void FramelessWindow::hideSystemTitleBar() {
    //    const auto view = (NSView *) winId();
    //    NSWindow *nativeWindow = view.window;
    auto nativeView = (NSView *) winId();
    NSWindow *nativeWindow = [nativeView window];
    //设置标题文字和图标为不可见
    [nativeWindow setTitleVisibility:NSWindowTitleHidden];//MAC_10_10及以上版本支持
    //设置标题栏为透明
    [nativeWindow setTitlebarAppearsTransparent:YES];//MAC_10_10及以上版本支持
    //设置不可由标题栏拖动,避免与自定义拖动冲突
    [nativeWindow setMovable:NO];//MAC_10_6及以上版本支持
    [nativeWindow setMovableByWindowBackground:NO];
    //设置view扩展到标题栏
    nativeWindow.styleMask |= NSWindowStyleMaskFullSizeContentView;//MAC_10_10及以上版本支持
    [nativeWindow setShowsToolbarButton:NO];
    [nativeWindow makeKeyWindow];
}
void FramelessWindow::mousePressEvent(QMouseEvent *event) {
    if ((event->button() != Qt::LeftButton) || isMaximized()) {
        return QWidget::mousePressEvent(event);
    }
    QRect rect(0, 0, size().width(), size().height());
    if (rect.contains(this->mapFromGlobal(QCursor::pos()))) {
        windowPos = this->pos();
        // QCursor::pos()
        mousePos = QCursor::pos();
        mousePressed = true;
    }
    return QWidget::mousePressEvent(event);
}
void FramelessWindow::mouseReleaseEvent(QMouseEvent *event) {
    windowMoving = false;
    if (event->button() == Qt::LeftButton) {
        mousePressed = false;
    }
    return QWidget::mouseReleaseEvent(event);
}
void FramelessWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!mousePressed) return QWidget::mouseMoveEvent(event);
    windowMoving = true;
    this->move(windowPos + QCursor::pos() - mousePos);
}
void FramelessWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::WindowStateChange) {
        hideSystemTitleBar();
    }
    QWidget::changeEvent(event);
}

class MacOSThemeObserver {
   public:
    explicit MacOSThemeObserver() {
        if (QOperatingSystemVersion::current() > QOperatingSystemVersion::MacOSSierra) {

        }
    };

   private:
//    std::unique_ptr<MacOSKeyValueObserver> m_appearanceObserver = nil;
};


//MacOsThemeObserver::MacOsThemeObserver() {
//    if (QOperatingSystemVersion::current() > QOperatingSystemVersion::MacOSSierra) {
//
//    }
//}
#include "framelesswindow.moc"
