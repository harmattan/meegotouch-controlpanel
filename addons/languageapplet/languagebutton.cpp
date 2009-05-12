#include "languagebutton.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>
#include <duiseparator.h>
#include <duiscenemanager.h>

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int rowHeight = 90;

LanguageButton::LanguageButton(QString upText,
                               QString downText,
                               DuiWidget *parent)
               :DuiButton(parent),
                m_UpText(upText),
                m_DownText(downText)
{
    DuiTheme::loadCSS(cssDir + "languageapplet.css");
    initWidget();
}

LanguageButton::~LanguageButton()
{
}

void LanguageButton::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
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
    // mainMainLayout
    DuiLayout *mainMainLayout = new DuiLayout(this);
    mainMainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainMainLayoutPolicy =
        new DuiLinearLayoutPolicy(mainMainLayout, Qt::Vertical);
    mainMainLayout->setPolicy(mainMainLayoutPolicy);
    mainMainLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainMainLayoutPolicy->setSpacing(1);
    this->setLayout(mainMainLayout);
    
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(NULL);
    mainLayout->setAnimator(NULL);
    DuiGridLayoutPolicy *mainLayoutPolicy =
            new DuiGridLayoutPolicy(mainLayout);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(15.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(2);
    
    // seeMoreLayout
    DuiLayout *seeMoreLayout = new DuiLayout(NULL);
    seeMoreLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *seeMoreLayoutPolicy =
            new DuiLinearLayoutPolicy(seeMoreLayout, Qt::Vertical);
    seeMoreLayout->setPolicy(seeMoreLayoutPolicy);
    seeMoreLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    
    // seeMoreSmall
    DuiButton *seeMoreSmall = new DuiButton(this);
    seeMoreSmall->setObjectName("LanguageButtonSeeMoreSmall");
    seeMoreSmall->setAcceptedMouseButtons(0);
    seeMoreSmall->setMaximumWidth(20);
    seeMoreSmall->setMaximumHeight(20);

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

    // greySeparator
    m_GreySeparator = new DuiSeparator(this);
    m_GreySeparator->setObjectName("GreySeparator");
    m_GreySeparator->setAcceptedMouseButtons(0);

    // Add items to mainMainLayoutPolicy
    mainMainLayoutPolicy->addItemAtPosition(mainLayout, 0, Qt::AlignCenter);
    mainMainLayoutPolicy->addItemAtPosition(m_GreySeparator, 1, Qt::AlignCenter);
    
    // fixed size
    this->setMinimumHeight(rowHeight);

    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(onOrientationAngleChange()));
    onOrientationAngleChange();
}

void LanguageButton::onOrientationAngleChange()
{
    int devide = 35;
    this->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - devide);
    this->setMaximumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - devide);
    m_DownLabel->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - devide - 60);
    m_DownLabel->setMaximumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - devide - 60);
}
