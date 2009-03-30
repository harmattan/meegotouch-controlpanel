#include "languagebutton.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>

const QString cssDir    = "/usr/share/themes/dui/duicontrolpanel/";
const int rowHeight     =    80;

LanguageButton::LanguageButton(QString upText,
                               QString downText,
                               QGraphicsWidget *parent)
               :DuiWidget(parent),
                m_upText(upText),
                m_downText(downText)
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

void LanguageButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    setMinimumHeight(rowHeight);
    setMaximumHeight(rowHeight);
}

void LanguageButton::initWidget()
{
    const QString   spaceUp("   ");
    const QString spaceDown("   ");
    const int upRowHeight   = rowHeight * 0.55;
    const int downRowHeight = rowHeight * 0.45;

    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);

    DuiGridLayoutPolicy *mainLayoutPolicy = 
            new DuiGridLayoutPolicy(mainLayout);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    // m_bigButton
    m_bigButton = new DuiButton(this);
    m_bigButton->setObjectName("LanguageBigButton");
    m_bigButton->setMinimumHeight(upRowHeight + downRowHeight);
    m_bigButton->setMaximumHeight(upRowHeight + downRowHeight);

    // m_leftLabel
    m_leftLabel = new DuiLabel(spaceUp + m_upText, this);
    m_leftLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_leftLabel->setObjectName("LanguageLeftLabel");
    m_leftLabel->setMinimumHeight(upRowHeight);
    m_leftLabel->setMaximumHeight(upRowHeight);
    m_leftLabel->setAcceptedMouseButtons(0);
        
    // m_rightLabel
    m_rightLabel = new DuiLabel(spaceDown + m_downText, this);
    m_rightLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_rightLabel->setObjectName("LanguageRightLabel");
    m_rightLabel->setMinimumHeight(downRowHeight);
    m_rightLabel->setMaximumHeight(downRowHeight);
    m_rightLabel->setAcceptedMouseButtons(0);
        
    mainLayoutPolicy->addItemAtPosition(m_bigButton, 0, 0, 1, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_leftLabel, 0, 0, 1, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_rightLabel, 1, 0, 2, 0, Qt::AlignCenter);

    m_bigButton->setZValue(1);
    m_leftLabel->setZValue(2);
    m_rightLabel->setZValue(3);
}
