#include "dcpbuttonview.h"
#include "dcpimageutils.h"
#include <duiviewfactory.h>
#include <duibutton.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>

static const QString styleBgName = "bgName";
static int BG_ATTRIB;

DcpButtonView::DcpButtonView(DuiButton *controller):
    DuiStylable<DcpButtonView, DuiButtonView>(controller),
    m_Controller(controller)
{
}

void DcpButtonView::paint ( QPainter * painter,
                            const QStyleOptionGraphicsItem * option,
                            QWidget * widget)
{
    Q_UNUSED(widget);

    if (!m_BgId.isEmpty()){
        // QRect rect = d_ptr->controller->size();
        QRect rect = m_Controller->rect().toRect();

        QPixmap bg = DcpImageUtils::instance()->scaledPixmap(m_BgId, rect.size());
        if (!bg.isNull()){
            painter->drawPixmap(rect, bg);
        }
    }
    DuiButtonView::paint(painter, option, widget);
}


void DcpButtonView::styleUpdated ()
{
    m_BgId = styleAttribute<QString>(BG_ATTRIB);
}

void DcpButtonView::registerStyleAttributes(DuiStyleDescription& description)
{
    DuiButtonView::registerStyleAttributes(description);
    BG_ATTRIB = description.numberOfAttributes() + 1;
    description.addAttribute(BG_ATTRIB, styleBgName);
}

DUI_REGISTER_VIEW("DcpButtonView", DcpButtonView, DuiButton);

