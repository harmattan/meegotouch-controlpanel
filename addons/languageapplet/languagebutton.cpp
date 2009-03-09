#include "languagebutton.h"

#include <duigridlayout.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>

const QString cssDir    = "/usr/lib/duicontrolpanel/css/";
const int upRowHeight   =  90;
const int downRowHeight =  80;

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

void LanguageButton::initWidget()
{
        DuiGridLayout *mainLayout = new DuiGridLayout(this);
        mainLayout->setRowMinimumHeight(0, upRowHeight);
        mainLayout->setRowMinimumHeight(1, downRowHeight);

        mainLayout->setRowMaximumHeight(0, upRowHeight);
        mainLayout->setRowMaximumHeight(1, downRowHeight);
        
        m_bigButton = new DuiButton(this);
        m_bigButton->setObjectName("LanguageBigButton");
        m_bigButton->setMinimumHeight(upRowHeight + downRowHeight);
        m_bigButton->setMaximumHeight(upRowHeight + downRowHeight);

        m_leftLabel = new DuiLabel(m_upText, this);
        m_leftLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
        m_leftLabel->setMinimumHeight(upRowHeight);
        m_leftLabel->setMaximumHeight(upRowHeight);
        m_leftLabel->setObjectName("LanguageLeftLabel");
        m_leftLabel->setAcceptedMouseButtons(0);
        
        m_rightLabel = new DuiLabel(m_downText, this);
        m_rightLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
        m_rightLabel->setMinimumHeight(downRowHeight);
        m_rightLabel->setMaximumHeight(downRowHeight);
        m_rightLabel->setObjectName("LanguageRightLabel");
        m_rightLabel->setAcceptedMouseButtons(0);
        
        mainLayout->addItem(m_bigButton, 0, 0, 2, 1, Qt::AlignCenter);
        mainLayout->addItem(m_leftLabel, 0, 0, Qt::AlignCenter);
        mainLayout->addItem(m_rightLabel, 1, 0, Qt::AlignCenter);

        m_bigButton->setZValue(1);
        m_leftLabel->setZValue(2);
        m_rightLabel->setZValue(3);
}
