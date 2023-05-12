#include "horizonnavigation.h"
#include <QMouseEvent>
#include <QPainterPath>
#include <utility>

namespace Ui {
//HorizonNavigation::HorizonNavigation(QWidget *parent)
//    : QWidget(parent),
//      animation(new QPropertyAnimation(this, "")) {
//    setUi();
//}
HorizonNavigation::HorizonNavigation(QWidget *parent, QStringList items)
    : QWidget(parent),
      itemList(std::move(items)),
      animation(new QPropertyAnimation(this, "")) {
    setUi();
}

void HorizonNavigation::setUi() {
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(30);
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutBack);
    connect(animation, &QPropertyAnimation::valueChanged, this, &HorizonNavigation::onValeChanged);
}
void HorizonNavigation::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    // 画背景
    painter.setPen(Qt::NoPen);
    QPainterPath background;
    background.addRoundedRect(QRect(0, 0, columnWidth * int(itemList.length()) + 4, rowHeight), radius, radius);
    painter.fillPath(background, Ui::backgroundColor);
    if (itemList.length() > 1) {
    }
    // 画按钮
    QPainterPath itemPath;
    itemPath.addRoundedRect(QRect(2 + offset, 2, columnWidth, rowHeight - 4), radius, radius);
    painter.fillPath(itemPath, Ui::btnColor);

    for (int count = 0; count < itemList.length(); ++count) {
        // 画按钮分割线
        if (itemList.length() > 1 && count > 0) {
            painter.setPen(QPen(Ui::fontColor, 1, Qt::SolidLine, Qt::SquareCap));
            if (offset < columnWidth * (count - 1) || offset > columnWidth * (count)) {
                painter.drawLine(2 + columnWidth * count, 8, 2 + columnWidth * count, 20);
            }
        }
        // 画按钮名称
        painter.setPen(Ui::fontColor);
        painter.drawText(
            QRect(count * columnWidth, 0, columnWidth, rowHeight),
            Qt::AlignVCenter | Qt::AlignHCenter,
            itemList.at(count));
    }
    painter.restore();
}
void HorizonNavigation::mousePressEvent(QMouseEvent *event) {
    if (event->position().x() / columnWidth < int(itemList.length())) {
        currentIndex = qIntCast(event->position().x()) / columnWidth;
        emit currentItemChanged(currentIndex);
        animation->setStartValue(preIndex * columnWidth);
        animation->setEndValue(currentIndex * columnWidth);
        animation->start();
        preIndex = currentIndex;
        update();
    }
}
void HorizonNavigation::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e)
}
void HorizonNavigation::onValeChanged(const QVariant &v) {
    offset = v.toInt();
    update();
}
void HorizonNavigation::addItems(const QStringList &items) {
    itemList = items;
    update();
}

}// namespace Ui

// 以下是通过 QListWidget 实现
#if 0
#include "horizonnavigation.h"
#include <QScroller>

Ui::ListItemSelectionDelegate::ListItemSelectionDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void Ui::ListItemSelectionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //    QStyleOptionViewItem op =
    QStyleOptionViewItem option_ = option;
    option_.state &= ~QStyle::State_Selected;
    QStyledItemDelegate::paint(painter, option_, index);
}

Ui::HorizonNavigation::HorizonNavigation(QWidget *parent)
    : QListWidget(parent),
      selectedFrame(new QFrame(this)),
      animation(new QPropertyAnimation(selectedFrame, "geometry")),
      itemDelegate(new ListItemSelectionDelegate(this))
{
    this->setObjectName("HorizonNavigation");
    setAttribute(Qt::WA_StyledBackground, true);
    selectedFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    selectedFrame->setFocusPolicy(Qt::NoFocus);
//    selectedFrame->hide();
    selectedFrame->setObjectName("SelectedFrame");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutBack);
    connect(this, &QListWidget::currentItemChanged, this, &HorizonNavigation::updateSelection);
    setItemDelegate(itemDelegate);

    setFlow(QListView::LeftToRight);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(3);

}

void Ui::HorizonNavigation::resizeEvent(QResizeEvent *event) {
    QListView::resizeEvent(event);
    updateSelection(currentItem());
}

void Ui::HorizonNavigation::updateSelection(QListWidgetItem *current) {
    animation->stop();
    if (!current) {
        selectedFrame->hide();
        return;
    }
    if (!selectedFrame->isVisible()) {
        selectedFrame->setGeometry(visualItemRect(current));
        selectedFrame->show();
        return;
    }
    animation->setStartValue(selectedFrame->geometry());
    animation->setEndValue(visualItemRect(current));
    animation->start();
}
void Ui::HorizonNavigation::setTextAlignCenter() {
    for (auto item : this->findItems("*", Qt::MatchWildcard)) {
        //do something with each item
        item->setTextAlignment(Qt::AlignCenter);
    }
}
void Ui::HorizonNavigation::addItems(const QStringList &labels) {
    QListWidget::addItems(labels);
    setTextAlignCenter();
    setCurrentRow(0);
}

#endif
