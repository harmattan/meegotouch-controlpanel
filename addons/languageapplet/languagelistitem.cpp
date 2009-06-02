#include "languagelistitem.h"
#include "dcpspaceritem.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiseparator.h>
#include <qgraphicswidget.h>
#include <duiscenemanager.h>
#include <duiseparator.h>

const int height = 65;
const int devide = 100;

LanguageListItem::LanguageListItem(const QString &langCode,
                                   const QString &text, 
                                   DuiWidget *parent)
                 :DuiWidget(parent), 
                  m_LangCode(langCode),   
                  m_LabelText(text),
                  m_Checked(false),
                  m_Clicked(false),
                  m_First(true)
{
    initWidget();
}

LanguageListItem::~LanguageListItem()
{
}

void LanguageListItem::checked(bool ok)
{
    m_Checked = ok;
    if (m_Checked) {
        m_NormalLabel->setText("<font color=#e48415>" + m_LabelText
                               + "</font>");
        if (m_First) 
        {
            // checkMarkLayout
            DuiLayout *checkMarkLayout = new DuiLayout(0);
            checkMarkLayout->setAnimator(0);
            checkMarkLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
            DuiLinearLayoutPolicy *checkMarkLayoutPolicy =
                new DuiLinearLayoutPolicy(checkMarkLayout, Qt::Vertical);
            checkMarkLayout->setPolicy(checkMarkLayoutPolicy);
            
            // checkMark
            m_CheckMark = new DuiButton(this);
            m_CheckMark->setObjectName("LanguageCheckMark");
            m_CheckMark->setAcceptedMouseButtons(0);
            m_CheckMark->setMinimumSize(QSize(32, 32));
            m_CheckMark->setMaximumSize(QSize(32, 32));

            // add items to checkMarkLayoutPolicy
            checkMarkLayoutPolicy->addItemAtPosition(m_CheckMark, 1, Qt::AlignCenter);
            
            m_LabelLayout->removeItem(m_LabelLayoutPolicy->itemAt(0, 2));
            m_LabelLayoutPolicy->addItemAtPosition(checkMarkLayout, 0, 2);
            m_First = false;
        }
        m_CheckMark->setVisible(true);
    } else {
        m_NormalLabel->setText("<font color=#ffffff>" + m_LabelText
                               + "</font>");
        if (!m_First)
        {
            m_CheckMark->setVisible(false);
        }
    }
}

bool LanguageListItem::isChecked()
{
    return m_Checked;
}

QString LanguageListItem::text() const
{
    return m_LabelText;
}

QString LanguageListItem::langCode() const
{
    return m_LangCode;
}

bool LanguageListItem::isClicked()
{
    return m_Clicked;
}

void LanguageListItem::setVisibleSeparator(bool enable)
{
    m_GreySeparator->setVisible(enable);
}

void LanguageListItem::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(1);
    
    // set height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    // m_LabelLayout
    m_LabelLayout = new DuiLayout(0);
    m_LabelLayout->setAnimator(0);
    m_LabelLayoutPolicy = new DuiGridLayoutPolicy(m_LabelLayout);
    m_LabelLayout->setPolicy(m_LabelLayoutPolicy);
    m_LabelLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_LabelLayoutPolicy->setSpacing(3);
        
    // normalLabel
    m_NormalLabel = new DuiLabel("<font color=#ffffff>" + m_LabelText + "</font>", this);
    m_NormalLabel->setObjectName("LanguageNormalListItem");
    m_NormalLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_NormalLabel->setAcceptedMouseButtons(0);
    
    m_LabelLayoutPolicy->addItemAtPosition(m_NormalLabel, 0, 0);
    m_LabelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
                    0, 1);
    m_LabelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 32, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                    0, 2);

    // checkMark
    m_CheckMark = 0;
    
    // m_GreySeparator
    m_GreySeparator = new DuiSeparator(this);
    m_GreySeparator->setObjectName("GreySeparator");

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_LabelLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_GreySeparator, 3, Qt::AlignCenter);

    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}

void LanguageListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mousePressEvent(event);
    event->accept();
    checked(!m_Checked);
    m_Clicked = true;
    emit clicked(this);
}

void LanguageListItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mouseReleaseEvent(event);
    event->accept();
}


void LanguageListItem::onOrientationAngleChanged()
{
    switch(DuiSceneManager::instance()->orientation()) {
        case Dui::Landscape:
            this->setMinimumWidth(
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 50);
            this->setMaximumWidth(
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 50);
            break;
        case Dui::Portrait:
            this->setMinimumWidth(
                    DuiSceneManager::instance()->visibleSceneRect().width() - 50);
            this->setMaximumWidth(
                    DuiSceneManager::instance()->visibleSceneRect().width() - 50);
            break;
        default:
            break;
    }
}
