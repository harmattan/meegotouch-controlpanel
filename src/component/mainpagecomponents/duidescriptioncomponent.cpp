#include "duidescriptioncomponent.h"

#include <QtDebug>
#include <QGraphicsSceneResizeEvent>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duitheme.h>
#include <qpixmap.h>

static const QSize fullSize(720,55);
static const QSize halfSize(340,55);

DuiDescriptionComponent::DuiDescriptionComponent(DuiSettingsCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DuiSettingsComponent(category, title, parent),
    m_Background (NULL)
{
    createContents();
}


DuiDescriptionComponent::~DuiDescriptionComponent() {
    if (m_Background) {
        // DuiTheme::releasePixmap(m_Background);
        delete m_Background;
    }
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

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Description->setAcceptedMouseButtons(0);
    m_Caption->setAcceptedMouseButtons(0);
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

    if (m_Background == NULL || m_Background->width() != size().width()){
        if (m_Background) {
            // DuiTheme::releasePixmap(m_Background);
            delete m_Background;
        }
        m_Background = DuiTheme::pixmap("C2-container-dark-landscape-123px",
                                           size());
        if (!m_Background) {
            qWarning ("theme lacks bg picture for settings component");
            return;
        }

        /* TODO this is because DuiTheme does not want to resize the image
           above its size. Fix it with appropriate pixmap, or duitheme feature
           request. */
        QPixmap* themePix = m_Background;
        m_Background = new QPixmap(m_Background->scaled(size().toSize()));
        DuiTheme::releasePixmap(themePix);
        /* -- */
    }
    painter->drawPixmap(QPoint(0, 0), *m_Background);

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


void DuiDescriptionComponent::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    qDebug() << "XXX mouse press";
    DuiSettingsComponent::mousePressEvent(event);
    event->accept();
}

void DuiDescriptionComponent::mouseReleaseEvent (QGraphicsSceneMouseEvent * event)
{
    qDebug() << "XXX mouse release";
    DuiSettingsComponent::mouseReleaseEvent(event);
    event->accept();
}

