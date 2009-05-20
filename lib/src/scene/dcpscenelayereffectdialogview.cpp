#include "dcpscenelayereffectdialogview.h"
// DUI_STYLABLE_CPP(DcpSceneLayerEffectDialogView, DuiWidgetView)

#include <duiscenelayereffect.h>
#include <duiviewfactory.h>

DcpSceneLayerEffectDialogView::DcpSceneLayerEffectDialogView(DuiSceneLayerEffect *controller)
                              :DuiWidgetView(controller),
                               m_Controller(controller)
{
}

DcpSceneLayerEffectDialogView::~DcpSceneLayerEffectDialogView()
{
}

void DcpSceneLayerEffectDialogView::paint(QPainter *painter,
                                          const QStyleOptionGraphicsItem *option,
                                          QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal opacity = 0.75;
    painter->setOpacity(m_Controller->effectiveOpacity() * opacity);
    painter->fillRect(boundingRect(), QColor(0, 0, 0));
}

QRectF DcpSceneLayerEffectDialogView::boundingRect() const
{
    int value = 62;
    QSizeF controllerSize = m_Controller->size();
    controllerSize.setHeight(m_Controller->size().height() - value);
    return QRectF(QPoint(0, value), controllerSize);
}

/* void DcpSceneLayerEffectDialogView::styleUpdated()
{
    DuiWidgetView::styleUpdated();
}*/

void DcpSceneLayerEffectDialogView::startEffect()
{
    m_TimeLine.setDuration(5000);
    m_TimeLine.setLoopCount(0);
    m_TimeLine.setStartFrame(0);
    m_TimeLine.start();
}

void DcpSceneLayerEffectDialogView::stopEffect()
{
    m_TimeLine.stop();
}

/* void DcpSceneLayerEffectDialogView::registerStyleAttributes(DuiStyleDescription &description)
{
    Q_UNUSED(description);
}*/

DUI_REGISTER_VIEW("DcpSceneLayerEffectDialogView", DcpSceneLayerEffectDialogView, DuiSceneLayerEffect)
