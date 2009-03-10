#include "languagebutton.h"

#include <duigridlayout.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>

const QString cssDir    = "/usr/lib/duicontrolpanel/css/";
const int rowHeight     =    90;
const int rowWidth      =   680;
const float minimalize  =  0.9f;

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
        const int upRowHeight   = rowHeight * 0.55;
        const int downRowHeight = rowHeight * 0.45;

        // mainLayout
        mainLayout = new DuiGridLayout(this);
        mainLayout->setRowMinimumHeight(0, upRowHeight);
        mainLayout->setRowMinimumHeight(1, downRowHeight);
        mainLayout->setRowMaximumHeight(0, upRowHeight);
        mainLayout->setRowMaximumHeight(1, downRowHeight);
                
        // m_bigButton
        m_bigButton = new DuiButton(this);
        m_bigButton->setObjectName("LanguageBigButton");
        m_bigButton->setMinimumHeight(upRowHeight + downRowHeight);
        m_bigButton->setMaximumHeight(upRowHeight + downRowHeight);
        m_bigButton->setMinimumWidth(rowWidth);
        m_bigButton->setMaximumWidth(rowWidth);

        // m_leftLabel
        m_leftLabel = new DuiLabel(m_upText, this);
        m_leftLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_leftLabel->setObjectName("LanguageLeftLabel");
        m_leftLabel->setMinimumHeight(upRowHeight);
        m_leftLabel->setMaximumHeight(upRowHeight);
        m_leftLabel->setMinimumWidth(rowWidth * 0.85f);
        m_leftLabel->setMaximumWidth(rowWidth * 0.85f);
        m_leftLabel->setAcceptedMouseButtons(0);
        
        // m_rightLabel
        m_rightLabel = new DuiLabel(m_downText, this);
        m_rightLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_rightLabel->setObjectName("LanguageRightLabel");
        m_rightLabel->setMinimumHeight(downRowHeight);
        m_rightLabel->setMaximumHeight(downRowHeight);
        m_rightLabel->setMinimumWidth(rowWidth * 0.95f);
        m_rightLabel->setMaximumWidth(rowWidth * 0.95f);
        m_rightLabel->setAcceptedMouseButtons(0);
        
        mainLayout->addItem(m_bigButton, 0, 0, 2, 1, Qt::AlignCenter);
        mainLayout->addItem(m_leftLabel, 0, 0, Qt::AlignCenter);
        mainLayout->addItem(m_rightLabel, 1, 0, Qt::AlignCenter);

        m_bigButton->setZValue(1);
        m_leftLabel->setZValue(2);
        m_rightLabel->setZValue(3);
}