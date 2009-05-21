#ifndef DCPSCENELAYEREFFECTDIALOGVIEW
#define DCPSCENELAYEREFFECTDIALOGVIEW

#include <duiwidgetview.h>
#include <QTimeLine>

class DuiSceneLayerEffect;

class DcpSceneLayerEffectDialogView : public DuiWidgetView
{
    Q_OBJECT
    
public:
    DcpSceneLayerEffectDialogView(DuiSceneLayerEffect *controller);
    virtual ~DcpSceneLayerEffectDialogView();
    //! \reimp
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = 0);
    virtual QRectF boundingRect() const;
    //! \reimp_end

protected:
    virtual void startEffect();
    virtual void stopEffect();

private:
    DuiSceneLayerEffect *m_Controller;
    QTimeLine m_TimeLine;
};
#endif // DCPSCENELAYEREFFECTDIALOGVIEW
