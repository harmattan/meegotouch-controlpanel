#include "grouptitlewidget.h"
#include "dcpspaceritem.h"

#include <duitheme.h>
#include <qpixmap.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

GroupTitleWidget::GroupTitleWidget(const QString &text, DuiWidget *parent)
                 :DuiWidget(parent), m_Background(NULL)
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);

    // label
    DuiLabel *label = new DuiLabel(text, this);
    label->setObjectName("DisplayLanguageSelectTitle");
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed),
                    0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayoutPolicy->addItemAtPosition(label, 1, Qt::AlignLeft | Qt::AlignVCenter);
    this->setLayout(mainLayout);
}

GroupTitleWidget::~GroupTitleWidget()
{
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
    }
}

void GroupTitleWidget::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_Background) {
        painter->drawPixmap(0, 0, *m_Background);
    }
}

void GroupTitleWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    QSize size = this->size().toSize();
    static const int border = 10;
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
    }
    
    m_Background = DuiTheme::boxedPixmap("Divider-with-label", size,
                                         border, border, border, border);
}
