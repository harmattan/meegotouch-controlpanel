#include "dcpbackgroundcomponent.h"

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duitheme.h>
#include <qpixmap.h>

#include "dcpimageutils.h"

DcpBackgroundComponent::DcpBackgroundComponent(
                            DcpCategory *category,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent),
    m_Background (NULL)
{

}


DcpBackgroundComponent::~DcpBackgroundComponent() {
    if (m_Background) {
        // DuiTheme::releasePixmap(m_Background);
        delete m_Background;
    }
}


void
DcpBackgroundComponent::createContents()
{
    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Caption->setObjectName("ComponentCaption");

    // TODO: move to stylesheet
    this->setContentsMargins(10,10,10,10);

    QFont captionFont = m_Caption->font();
    captionFont.setPointSize(captionFont.pointSize()+2);
    captionFont.setBold(true);
    m_Caption->setFont(captionFont);
    // --

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Caption->setAcceptedMouseButtons(0);
    // --

    m_Layout->addItem(m_Caption);
    setLayout(m_Layout);
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
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QColor bgColor = Qt::black;
    QColor borderColor = Qt::lightGray;
    // --

    if (m_Background == NULL || m_Background->width() != size().width()){
        if (m_Background) {
            // DuiTheme::releasePixmap(m_Background);
            delete m_Background;
        }
        m_Background = DuiTheme::pixmap("C2-container-dark-landscape-123px");
        if (!m_Background) {
            qWarning ("theme lacks bg picture for settings component");
            return;
        }

        /* TODO this is because DuiTheme does not want to resize the image
           above its size. Fix it with appropriate pixmap, or duitheme feature
           request. */
        QPixmap* themePix = m_Background;
        m_Background = new QPixmap(
                borderCorrectScale(*m_Background,
                                   size().toSize().width(),
                                   size().toSize().height())
        );
        DuiTheme::releasePixmap(themePix);
        /* -- */
    }
    painter->drawPixmap(QPoint(0, 0), *m_Background);

    // line between the title & description:
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    qreal y = m_Caption->y() + m_Caption->size().height() + 2;
    painter->drawLine(borderWidth, y, size().width()-2*borderWidth, y);
}


void DcpBackgroundComponent::setTitleAlignment(Qt::Alignment align)
{
    m_Caption->setAlignment(align);
}


void DcpBackgroundComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}
