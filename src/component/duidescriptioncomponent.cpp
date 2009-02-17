#include "duidescriptioncomponent.h"

#include <QtDebug>
#include <QGraphicsSceneResizeEvent>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duitheme.h>
#include <qpixmap.h>

static const QSize fullSize(670,65);
static const QSize halfSize(330,65);

DuiDescriptionComponent::DuiDescriptionComponent(DuiSettingsCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DuiSettingsComponent(category, title, parent)
{
    createContents();
}


void
DuiDescriptionComponent::createContents()
{

    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Caption->setObjectName("ComponentCaption");

    m_Description = new DuiLabel();
    m_Description->setObjectName("ComponentDescription");
    m_Description->setAlignment(Qt::AlignJustify | Qt::AlignTop);
    m_Description->setWordWrap(true);

    // TODO: move to stylesheet
    m_Description->setMaximumSize(halfSize);
    m_Description->setMinimumSize(halfSize);
    this->setContentsMargins(10,10,10,10);

    QFont captionFont = m_Caption->font();
    captionFont.setPointSize(captionFont.pointSize()+2);
    captionFont.setBold(true);
    m_Caption->setFont(captionFont);
    // --

    m_Layout->addItem(m_Caption);
    m_Layout->addItem(m_Description);
    setLayout(m_Layout);
}


void
DuiDescriptionComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);
}


void DuiDescriptionComponent::setTitle(const QString& title)
{
    m_Caption->setText(title);
    DuiSettingsComponent::setTitle(title);
}


void DuiDescriptionComponent::setDescription(const QString& desc)
{
    m_Description->setText(desc);
}


void DuiDescriptionComponent::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // TODO: move to stylesheet
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QColor bgColor = Qt::black;
    QColor borderColor = Qt::lightGray;
    // --

    QPixmap *background = DuiTheme::pixmap("C2-container-dark-landscape-123px",
                                           size());
    painter->drawPixmap(QPoint(0, 0), *background);

    // line between the title & description:
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    qreal y = m_Description->y()-3;
    painter->drawLine(borderWidth, y, size().width()-2*borderWidth, y);
}


void DuiDescriptionComponent::setTextAlignment(Qt::Alignment align)
{
    m_Caption->setAlignment(align);
    m_Description->setAlignment(align);
}


void DuiDescriptionComponent::setFullRowSize()
{
    /* prohibit the description to change the widget's width too big */
    m_Description->setMaximumSize(fullSize);
    m_Description->setMinimumSize(fullSize);

    setTextAlignment(Qt::AlignHCenter);
}

