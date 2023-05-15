
#include "aboutpage.h"
#include <QDesktopServices>

namespace Ui {
AboutPage::AboutPage(QWidget *parent)
    : QWidget((parent)),
      mainLayout(new QVBoxLayout),
      aboutLabel(new QLabel),
      about(new QLabel) {
    this->setLayout(mainLayout);
    aboutLabel->setObjectName("AboutLabel");
    mainLayout->addWidget(aboutLabel);
    aboutLabel->setText("About");
    about->setObjectName("About");
    mainLayout->addWidget(about);
    about->setText(QString(R"(
<body>
<p>R0x1© &#20;&#20; Version 0.1</p>
<p>a full-featured download manager. </p>
<p>fast and light-weight. clean and nice interface.</p>
<p>built with qt and aria2.</p>
<p style=color:#6699CC>──────────────</p>
<p style=color:#31493C>致谢</p>
<p><a style=color:#32bc84; href = https://www.qt.io>qt</a></p>
<p><a style=color:#32bc84; href = https://aria2.github.io>aria2</a></p>
<p><a style=color:#32bc84; href = https://json.nlohmann.me>nlohmann-json</a></p>
<p><a style=color:#32bc84; href = https://xxx>xxx</a></p>
<p><a style=color:#32bc84; href = https://xxx>xxx</a></p>
<p>
<p style=color:#6699CC>──────────────</p>
<a style=color:#000; href = https://xxx>about</a>&#20;&#20;
<a style=color:#000; href = https://xxx>support</a>&#20;&#20;
<a style=color:#000; href = https://xxx>release</a>&#20;&#20;
</p>
</body>

)"));
    connect(about,&QLabel::linkActivated,this,[=](const QString &link) {
            QDesktopServices::openUrl(QUrl(link));
    });
}
}// namespace Ui