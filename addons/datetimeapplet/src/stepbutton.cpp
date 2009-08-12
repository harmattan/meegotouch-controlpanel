#include "stepbutton.h"

StepButton::StepButton(StepButton::Type type, DuiWidget *parent)
           :DuiButton(parent),
            m_Type(type)
{
}

StepButton::~StepButton()
{
}

void StepButton::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QColor(255, 255, 255, 255));
    painter->setBrush(QColor(255, 255, 255, 255));
    switch (m_Type) {
        case StepButton::Left:
                static const QPointF lPoints[3] = {
                        QPointF(rect().width(), 0.0),
                        QPointF(0.0, rect().height() / 2),
                        QPointF(rect().width(), rect().height())
                };
                painter->drawPolygon(lPoints, 3);
                break;
        case StepButton::Right: 
                static const QPointF rPoints[3] = {
                    QPointF(0.0, 0.0),
                    QPointF(rect().width(), rect().height() / 2),
                    QPointF(0.0, rect().height())
                };
                painter->drawPolygon(rPoints, 3);
                break;
    }
}

