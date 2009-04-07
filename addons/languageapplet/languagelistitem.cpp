#include "languagelistitem.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>

const int height = 60;

LanguageListItem::LanguageListItem(const QString &text, 
                                   bool checked,
                                   DuiWidget *parent)
                 :DuiWidget(parent), 
                  m_labelText(text), 
                  m_checked(checked)
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
    int devide = 40;
    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
}

void LanguageListItem::checked(bool ok)
{
    m_checked = ok;
}

bool LanguageListItem::isChecked()
{
    return m_checked;
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
    DuiLinearLayoutPolicy *labelLayoutPolicy = 
            new DuiLinearLayoutPolicy(labelLayout, Qt::Horizontal);
    labelLayout->setPolicy(labelLayoutPolicy);
    
    DuiLabel *mainLabel = new DuiLabel(m_labelText, this);
    mainLabel->setObjectName("LanguageNormalListItem");
    labelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed),
                    0, Qt::AlignLeft | Qt::AlignVCenter);
    labelLayoutPolicy->addItemAtPosition(mainLabel, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayoutPolicy->addItemAtPosition(labelLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5,
                            QSizePolicy::Fixed, QSizePolicy::Expanding),
                    2, Qt::AlignCenter);
}
