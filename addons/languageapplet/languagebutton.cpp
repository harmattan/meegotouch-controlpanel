#include "languagebutton.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int rowHeight = 90;

LanguageButton::LanguageButton(QString upText,
                               QString downText,
                               DuiWidget *parent)
               :DuiButton(parent),
                m_UpText(upText),
                m_DownText(downText)
		        // m_Background(NULL)
{
    DuiTheme::loadCSS(cssDir + "languageapplet.css");
    initWidget();
}

LanguageButton::~LanguageButton()
{
    /* if (m_Background)
    {
        DuiTheme::releasePixmap(m_Background);
    }*/
}

void LanguageButton::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    // Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // if available, then draw it:
    /* if (m_Background) 
    {
        painter->drawPixmap(0, 0, *m_Background);
    }*/

    int borderWidth = 2;
    QColor lineColor = QColor(130, 130, 130, 244);
    QPen pen = painter->pen();
    pen.setWidth(1);
    pen.setColor(lineColor);
    painter->setPen(pen);

    qreal y = size().height();
    painter->drawLine(borderWidth, y,
                      geometry().size().width() - 2 * borderWidth, y);
}

void LanguageButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    /* QSize size = this->size().toSize();
    static const int border = 10;
    if (m_Background)
    {
        DuiTheme::releasePixmap(m_Background);
    }
    m_Background = DuiTheme::boxedPixmap("C2-container", size,
                                         border, border, border, border);*/
}

void LanguageButton::setUpText(const QString &text)
{
    m_UpLabel->setText(text);
}

void LanguageButton::setDownText(const QString &text)
{
    m_DownLabel->setText(text);
}

void LanguageButton::initWidget()
{
    this->setObjectName("LanguageButton");
    
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiGridLayoutPolicy *mainLayoutPolicy =
            new DuiGridLayoutPolicy(mainLayout);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(12.0, 12.0, 12.0, 12.0);
    mainLayoutPolicy->setSpacing(2);
    
    // seeMoreLayout
    DuiLayout *seeMoreLayout = new DuiLayout(NULL);
    seeMoreLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *seeMoreLayoutPolicy =
            new DuiLinearLayoutPolicy(seeMoreLayout, Qt::Vertical);
    seeMoreLayout->setPolicy(seeMoreLayoutPolicy);
    
    // seeMoreSmall
    DuiButton *seeMoreSmall = new DuiButton(this);
    seeMoreSmall->setObjectName("LanguageButtonSeeMoreSmall");
    seeMoreSmall->setAcceptedMouseButtons(0);
    seeMoreSmall->setMaximumWidth(15);
    seeMoreSmall->setMaximumHeight(15);

    seeMoreLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
                    0, Qt::AlignCenter);
    seeMoreLayoutPolicy->addItemAtPosition(seeMoreSmall, 1, Qt::AlignLeft | Qt::AlignVCenter);
    seeMoreLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
                    2, Qt::AlignCenter);

    // m_upLabel
    m_UpLabel = new DuiLabel(m_UpText, this);
    m_UpLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_UpLabel->setObjectName("LanguageLeftLabel");
    m_UpLabel->setAcceptedMouseButtons(0);

    // m_downLabel
    m_DownLabel = new DuiLabel(m_DownText, this);
    m_DownLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_DownLabel->setObjectName("LanguageRightLabel");
    m_DownLabel->setAcceptedMouseButtons(0);
 
    DuiWidget* seeMoreWidget = new DuiWidget(this);
    seeMoreWidget->setLayout(seeMoreLayout);
    mainLayoutPolicy->addItemAtPosition(seeMoreWidget, 0, 0);
    mainLayoutPolicy->addItemAtPosition(m_UpLabel, 0, 1);
    mainLayoutPolicy->addItemAtPosition(m_DownLabel, 1, 1);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, 2);
    
    seeMoreSmall->setZValue(1);
    m_UpLabel->setZValue(2);
    m_DownLabel->setZValue(3);
    this->setLayout(mainLayout);
    
    // fixed size
    setMinimumHeight(rowHeight);
    setMaximumHeight(rowHeight);
}
