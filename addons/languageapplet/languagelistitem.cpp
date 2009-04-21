#include "languagelistitem.h"
#include "dcpspaceritem.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <qgraphicswidget.h>

const int height = 60;

LanguageListItem::LanguageListItem(const QString &text, 
                                   DuiWidget *parent)
                 :DuiWidget(parent), 
                  m_labelText(text), 
                  m_checked(false),
                  m_clicked(false),
                  m_first(true)
{
    initWidget();
}

LanguageListItem::~LanguageListItem()
{
}

void LanguageListItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    // Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    int borderWidth = 2;
    QColor lineColor = QColor(80, 80, 80, 244);
    QPen pen = painter->pen();
    pen.setWidth(1);
    pen.setColor(lineColor);
    painter->setPen(pen);

    qreal y = size().height();
    painter->drawLine(borderWidth, y,
                      geometry().size().width() - 2 * borderWidth, y); 
}

void LanguageListItem::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);
}

void LanguageListItem::checked(bool ok)
{
    m_checked = ok;
    if (m_checked) {
        m_normalLabel->setText("<font color=#e48415>" + m_labelText
                               + "</font>");
        if (m_first) 
        {
            // checkMark
            m_checkMark = new DuiButton(this);
            m_checkMark->setObjectName("LanguageCheckMark");
            m_checkMark->setAcceptedMouseButtons(0);
            m_checkMark->setMaximumWidth(32);
            m_checkMark->setMaximumHeight(32);
            m_labelLayoutPolicy->addItemAtPosition(m_checkMark, 0, 3);
            m_first = false;
        }
        m_checkMark->setVisible(true);
    } else {
        m_normalLabel->setText("<font color=#ffffff>" + m_labelText
                               + "</font>");
        if (!m_first)
        {
            m_checkMark->setVisible(false);
        }
    }
}

bool LanguageListItem::isChecked()
{
    return m_checked;
}

QString LanguageListItem::text() const
{
    return m_labelText;
}

bool LanguageListItem::isClicked()
{
    return m_clicked;
}

void LanguageListItem::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, 
                            QSizePolicy::Fixed, QSizePolicy::Expanding),
                    0, Qt::AlignCenter);

    // label
    DuiLayout *labelLayout = new DuiLayout(NULL);
    m_labelLayoutPolicy = new DuiGridLayoutPolicy(labelLayout);
    labelLayout->setPolicy(m_labelLayoutPolicy);
    m_labelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 15, 10, QSizePolicy::Fixed, QSizePolicy::Fixed),
                    0, 0);
    
    // normalLabel
    m_normalLabel = new DuiLabel("<font color=#ffffff>" + m_labelText + "</font>", this);
    m_normalLabel->setObjectName("LanguageNormalListItem");
    m_normalLabel->setAcceptedMouseButtons(0);
    m_normalLabel->setMinimumWidth(200);
    m_labelLayoutPolicy->addItemAtPosition(m_normalLabel, 0, 1);
    
    m_labelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 130, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, 2);

    // checkMark
    m_checkMark = NULL;
    
    mainLayoutPolicy->addItemAtPosition(labelLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(new DcpSpacerItem(this, 5, 5,
                                  QSizePolicy::Fixed, QSizePolicy::Expanding),
                                  2, Qt::AlignCenter);

    // set height
    setMinimumHeight(height);
    setMaximumHeight(height);

    // set width
    int devide = 20;
    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
}

void LanguageListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mousePressEvent(event);
    event->accept();
    checked(!m_checked);
    m_clicked = true;
    emit clicked(this);
}

void LanguageListItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mouseReleaseEvent(event);
    event->accept();
}
