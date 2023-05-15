#pragma once
#include <QLabel>
#include <QPaintEvent>

namespace Ui {

class CheckableSvgLabel : public QLabel {
    Q_OBJECT
   public:
    explicit CheckableSvgLabel(QLabel *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setSvg(const QString &name, QSize size = {18, 18});
   signals:
    void clicked();

   protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

   public:
    bool checked = false;
};

}// namespace Ui
