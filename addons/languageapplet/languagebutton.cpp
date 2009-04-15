#include "languagebutton.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>

const QString cssDir    = "/usr/share/themes/dui/duicontrolpanel/";
const int rowHeight     =    90;

LanguageButton::LanguageButton(QString upText,
                               QString downText,
                               DuiWidget *parent)
               :DuiButton(parent),
                m_upText(upText),
                m_downText(downText),
		m_Background(NULL)
{
        DuiTheme::loadCSS(cssDir + "languageapplet.css");
        initWidget();
}

LanguageButton::~LanguageButton()
{
    if (m_Background)
    {
        DuiTheme::releasePixmap(m_Background);
    }
}

void LanguageButton::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    // Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // if available, then draw it:
    if (m_Background) 
    {
        painter->drawPixmap(0, 0, *m_Background);
    }                
}

void LanguageButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    QSize size = this->size().toSize();
    static const int border = 10;
    if (m_Background)
    {
        DuiTheme::releasePixmap(m_Background);
    }
    m_Background = DuiTheme::boxedPixmap("C2-container", size,
                                         border, border, border, border);
}

void LanguageButton::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    // mainLayout->setAnimator(0),
    this->setObjectName("LanguageButton");
    
    // upLabelLayout
    DuiLayout *upLabelLayout = new DuiLayout(0);
    DuiLinearLayoutPolicy *upLabelLayoutPolicy = 
            new DuiLinearLayoutPolicy(upLabelLayout, Qt::Horizontal);
    upLabelLayout->setPolicy(upLabelLayoutPolicy); 
    
    // m_upLabel
    m_upLabel = new DuiLabel(m_upText, this);
    m_upLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_upLabel->setObjectName("LanguageLeftLabel");
    m_upLabel->setAcceptedMouseButtons(0);

    // seeMoreSmall
    DuiButton *seeMoreSmall = new DuiButton(this);
    seeMoreSmall->setObjectName("LanguageButtonSeeMoreSmall");
    seeMoreSmall->setAcceptedMouseButtons(0);
    seeMoreSmall->setMaximumWidth(15);
    seeMoreSmall->setMaximumHeight(15);

    DuiWidget *spacerItem = new DuiWidget(this);
    spacerItem->setMaximumHeight(5);
    spacerItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    upLabelLayoutPolicy->addItemAtPosition(seeMoreSmall, 0, Qt::AlignLeft | Qt::AlignVCenter);
    upLabelLayoutPolicy->addItemAtPosition(m_upLabel, 1, Qt::AlignLeft | Qt::AlignVCenter);
    upLabelLayoutPolicy->addItemAtPosition(spacerItem, 2, Qt::AlignLeft | Qt::AlignVCenter);
        
    // m_downLabel
    m_downLabel = new DuiLabel(m_downText, this);
    m_downLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_downLabel->setObjectName("LanguageRightLabel");
    m_downLabel->setAcceptedMouseButtons(0);
 
    // mainLayoutPolicy
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);

    DuiWidget *spacer = new DuiWidget(this);
    spacer->setMinimumWidth(12);
    spacer->setMaximumWidth(12);
    spacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainLayoutPolicy->addItemAtPosition(spacer, 0, Qt::AlignLeft | Qt::AlignVCenter);

    // labelLayout
    DuiLayout *labelLayout = new DuiLayout(0);
    // labelLayout->setAnimator(0);
    DuiLinearLayoutPolicy *labelLayoutPolicy = 
            new DuiLinearLayoutPolicy(labelLayout, Qt::Vertical);
    labelLayout->setPolicy(labelLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(labelLayout, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // spacer
    DuiWidget *spacer2 = new DuiWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    DuiWidget *spacer3 = new DuiWidget(this);
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
    labelLayoutPolicy->addItemAtPosition(spacer2, 0, Qt::AlignLeft | Qt::AlignBottom);
    labelLayoutPolicy->addItemAtPosition(upLabelLayout, 1, Qt::AlignLeft | Qt::AlignBottom);
    labelLayoutPolicy->addItemAtPosition(m_downLabel, 2, Qt::AlignLeft | Qt::AlignTop);
    labelLayoutPolicy->addItemAtPosition(spacer3, 3, Qt::AlignLeft | Qt::AlignBottom);
    labelLayoutPolicy->setSpacing(2);

    m_upLabel->setZValue(1);
    m_downLabel->setZValue(2);

    setMinimumHeight(rowHeight);
    setMaximumHeight(rowHeight);
}
