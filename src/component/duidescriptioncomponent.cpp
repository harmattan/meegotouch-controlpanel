#include "duidescriptioncomponent.h"

#include <QtDebug>


#include <duilinearlayout.h>
#include <duilabel.h>
#include <duitheme.h>
#include <qpixmap.h>


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

    // TODO: move to stylesheet
    m_Description->setMaximumSize(340,100);
    m_Description->setMinimumSize(340,100);
    this->setContentsMargins(10,10,10,10);

    QFont captionFont = m_Caption->font();
    captionFont.setPointSize(captionFont.pointSize()+2);
    captionFont.setBold(true);
    m_Caption->setFont(captionFont);
    // --

    m_Description->setWordWrap(true);
    m_Layout->addItem(m_Caption);
    m_Layout->addItem(m_Description);
    setLayout(m_Layout);
}


void
DuiDescriptionComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);
}


void DuiDescriptionComponent::setTitle(const QString& title){
    m_Caption->setText(title);
    DuiSettingsComponent::setTitle(title);
}


void DuiDescriptionComponent::setDescription(const QString& desc){
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

    // background:
    //painter->setBrush(bgColor);
    QPen pen(borderColor);
    //pen.setWidth(borderWidth);
    //painter->setPen(pen);
    //painter->drawRoundedRect(boundingRect(), 20, 16);
    QPixmap *background = DuiTheme::pixmap("C2-container-dark-landscape-123px", QSize(380, 160));
    painter->drawPixmap(QPoint(0, 0), *background);

    // line between the title & description:
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    qreal y = m_Description->y()-3;
    painter->drawLine(borderWidth, y, size().width()-2*borderWidth, y);
}

