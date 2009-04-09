#include "languagelistitem.h"
#include "dcpspaceritem.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
// #include <duilayout.h>
// #include <duilinearlayoutpolicy.h>
#include <duilinearlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <qgraphicswidget.h>

const int height = 60;

LanguageListItem::LanguageListItem(const QString &text, 
                                   bool checked,
                                   DuiWidget *parent)
                 :DuiWidget(parent), 
                  m_labelText(text), 
                  m_checked(checked),
                  m_clicked(false)
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

    // set height
    setMinimumHeight(height);
    setMaximumHeight(height);

    // set width
    int devide = 20;
    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
}

void LanguageListItem::checked(bool ok)
{
    m_checked = ok;
    if (m_checked) {
        m_normalLabel->setVisible(false);
        m_labelLayout->removeItem(m_normalLabel);
        m_highlightLabel->setVisible(true);
        m_checkMark->setVisible(true);
    } else {
        m_normalLabel->setVisible(true);
        m_labelLayout->insertItem(1, m_normalLabel);
        m_highlightLabel->setVisible(false);
        m_checkMark->setVisible(false);
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
    /* DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, 
                            QSizePolicy::Fixed, QSizePolicy::Expanding),
                    0, Qt::AlignCenter);*/

    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
    mainLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding));

    // label
    /* DuiLayout *labelLayout = new DuiLayout(NULL);
    DuiLinearLayoutPolicy *labelLayoutPolicy = 
            new DuiLinearLayoutPolicy(labelLayout, Qt::Horizontal);
    labelLayout->setPolicy(labelLayoutPolicy);*/
    m_labelLayout = new DuiLinearLayout(Qt::Horizontal, NULL);
    
    // normalLabel
    m_normalLabel = new DuiLabel(m_labelText, this);
    m_normalLabel->setObjectName("LanguageNormalListItem");
    m_normalLabel->setAcceptedMouseButtons(0);
    /* labelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed),
                    0, Qt::AlignLeft | Qt::AlignVCenter);
    labelLayoutPolicy->addItemAtPosition(m_normalLabel, 1, Qt::AlignLeft | Qt::AlignVCenter);*/
    m_labelLayout->addItem(new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    m_labelLayout->addItem(m_normalLabel);
    
    // highlightLabel
    m_highlightLabel = new DuiLabel(m_labelText, this);
    m_highlightLabel->setObjectName("LanguageHighlightListItem");
    m_highlightLabel->setAcceptedMouseButtons(0);
    /* labelLayoutPolicy->addItemAtPosition(m_highlightLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayoutPolicy->addItemAtPosition(labelLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5,
                            QSizePolicy::Fixed, QSizePolicy::Expanding),
                    2, Qt::AlignCenter);*/
    m_labelLayout->addItem(m_highlightLabel);
    m_labelLayout->setAlignment(m_highlightLabel, Qt::AlignLeft | Qt::AlignVCenter);
    m_labelLayout->addItem(new DcpSpacerItem(this, 200, 5, QSizePolicy::Expanding, QSizePolicy::Fixed));

    // checkMark
    m_checkMark = new DuiButton(this);
    m_checkMark->setObjectName("LanguageCheckMark");
    m_checkMark->setAcceptedMouseButtons(0);
    m_checkMark->setMaximumWidth(32);
    m_checkMark->setMaximumHeight(32);
    m_labelLayout->addItem(m_checkMark);
    m_labelLayout->setAlignment(m_checkMark, Qt::AlignRight | Qt::AlignVCenter);
    
    mainLayout->addItem(m_labelLayout);
    mainLayout->addItem(new DcpSpacerItem(this, 5, 5,
                            QSizePolicy::Fixed, QSizePolicy::Expanding));

    if (m_checked) {
        m_normalLabel->setVisible(false);
        m_labelLayout->removeItem(m_normalLabel);
        m_highlightLabel->setVisible(true);
        m_checkMark->setVisible(true);
    } else {
        m_normalLabel->setVisible(true);
        m_highlightLabel->setVisible(false);
        m_checkMark->setVisible(false);
    }
}

void LanguageListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mousePressEvent(event);
    event->accept();
    // checked(!m_checked);
    m_clicked = true;
    emit clicked();
}

void LanguageListItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mouseReleaseEvent(event);
    event->accept();
}
