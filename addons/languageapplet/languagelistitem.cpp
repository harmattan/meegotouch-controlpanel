#include "languagelistitem.h"

#include <QDebug>
#include <QGraphicsGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <duilabel.h>
#include <duibutton.h>
#include <duiseparator.h>

const int height = 65;
static const QString normalLabelObjectName = "LanguageNormalListItem";
static const QString selectedLabelObjectName = "LanguageSelectedListItem";
static const QString separatorObjectName = "DcpSmallSeparator";

LanguageListItem::LanguageListItem(const QString &langCode,
                                   const QString &text, 
                                   DuiWidget *parent)
                 :DuiWidget(parent), 
                  m_LangCode(langCode),   
                  m_LabelText(text),
                  m_Checked(false),
                  m_Clicked(false)
{
    initWidget();
}

LanguageListItem::~LanguageListItem()
{
}

void LanguageListItem::checked(bool ok)
{
    m_Checked = ok;
    m_NormalLabel->setObjectName(ok ? selectedLabelObjectName
                                    : normalLabelObjectName);
    m_CheckMark->setVisible(ok);
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
    QGraphicsGridLayout *mainLayout = new QGraphicsGridLayout(this);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

    // height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    // normalLabel
    m_NormalLabel = new DuiLabel(m_LabelText, this);
    m_NormalLabel->setObjectName(normalLabelObjectName);
    m_NormalLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_NormalLabel->setAcceptedMouseButtons(0);

    // m_CheckMark
    m_CheckMark = new DuiButton(this);
    m_CheckMark->setObjectName("LanguageCheckMark");
    m_CheckMark->setAcceptedMouseButtons(0);
    m_CheckMark->setVisible(false);

    // m_GreySeparator
    m_GreySeparator = new DuiSeparator(this);
    m_GreySeparator->setObjectName(separatorObjectName);

    mainLayout->addItem (m_NormalLabel, 0,0, Qt::AlignLeft);
    mainLayout->addItem (m_CheckMark, 0, 1, Qt::AlignRight);
    mainLayout->addItem (m_GreySeparator, 1, 0, 1, 2);
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

