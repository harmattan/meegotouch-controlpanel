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

const int height = 70;

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
            // checkMark
            m_CheckMark = new DuiButton(this);
            m_CheckMark->setObjectName("LanguageCheckMark");
            m_CheckMark->setAcceptedMouseButtons(0);
            m_CheckMark->setMaximumWidth(32);
            m_CheckMark->setMaximumHeight(32);
            m_LabelLayoutPolicy->addItemAtPosition(m_CheckMark, 0, 3);
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

void LanguageListItem::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(1.0, 1.0, 1.0, 1.0);
    mainLayoutPolicy->setSpacing(1);
    
    // label
    DuiLayout *labelLayout = new DuiLayout(NULL);
    labelLayout->setAnimator(NULL);
    m_LabelLayoutPolicy = new DuiGridLayoutPolicy(labelLayout);
    labelLayout->setPolicy(m_LabelLayoutPolicy);
    m_LabelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 15, 10, QSizePolicy::Fixed, QSizePolicy::Fixed),
                    0, 0);
    
    // normalLabel
    m_NormalLabel = new DuiLabel("<font color=#ffffff>" + m_LabelText + "</font>", this);
    m_NormalLabel->setObjectName("LanguageNormalListItem");
    m_NormalLabel->setAcceptedMouseButtons(0);
    
    m_LabelLayoutPolicy->addItemAtPosition(m_NormalLabel, 0, 1);
    m_LabelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, 2);

    // checkMark
    m_CheckMark = NULL;
    
    DuiWidget* labelWidget = new DuiWidget(this);
    labelWidget->setLayout(labelLayout);

    // greySeparator
    DuiSeparator *greySeparator = new DuiSeparator(this);
    greySeparator->setObjectName("GreySeparator");
    greySeparator->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - 60);
    
    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(labelWidget, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(greySeparator, 3, Qt::AlignCenter);

    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();

    // set height
    setMinimumHeight(height);
    setMaximumHeight(height);
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
    // set width
    int devide = 60;
    this->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    this->setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);
}
