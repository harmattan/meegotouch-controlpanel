#include "dcpbackgroundcomponent.h"

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duitheme.h>

#include "dcpimageutils.h"

DcpBackgroundComponent::DcpBackgroundComponent(
                            DcpCategory *category,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent)
{
}


DcpBackgroundComponent::~DcpBackgroundComponent() {
}


void
DcpBackgroundComponent::createContents()
{
    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Caption->setObjectName("ComponentCaption");

    // TODO: move to stylesheet
    this->setContentsMargins(10, 0, 10, 0);

    QFont captionFont = m_Caption->font();
    captionFont.setPointSize(captionFont.pointSize()+2);
    captionFont.setBold(true);
    m_Caption->setFont(captionFont);
    // --

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Caption->setAcceptedMouseButtons(0);
    // --

    setLayout(m_Layout);
    addItem(m_Caption);
}


void
DcpBackgroundComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    // DcpComponent::onOrientationChange(orientation);
    Q_UNUSED(orientation);
}


void DcpBackgroundComponent::setTitle(const QString& title)
{
    m_Caption->setText(title);
    DcpComponent::setTitle(title);
}


void DcpBackgroundComponent::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // TODO: move to stylesheet
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QColor bgColor = Qt::black;
    QColor borderColor = Qt::lightGray;
    // --

    if (m_Background.isNull() || m_Background.width() != size().width()){
        m_Background = DcpImageUtils::instance()->scaledPixmap(
        //        "C2-container-dark-landscape-123px", size().toSize());
                "Mashup-container", size().toSize(), 30);
        if (m_Background.isNull()) {
            // qWarning ("theme lacks bg picture for settings component");
            return;
        }
    }
    painter->drawPixmap(QPoint(0, 0), m_Background);

    // line between the title & description:
    /* QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    qreal y = m_Caption->y() + m_Caption->size().height() + 2;
    painter->drawLine(borderWidth, y, size().width()-2*borderWidth, y);*/
}


void DcpBackgroundComponent::setTitleAlignment(Qt::Alignment align)
{
    m_Caption->setAlignment(align);
}


void DcpBackgroundComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}
