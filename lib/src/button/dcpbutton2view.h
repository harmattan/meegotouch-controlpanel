
#ifndef DCPBUTTON2VIEW_H
#define DCPBUTTON2VIEW_H

#include <DuiWidgetView>
#include "dcpbutton.h"

#include "dcpbuttonview.h"

#include "dcpbuttonmodel.h"
#include "dcpbuttonstyle.h"


class QPainter;

class DcpButton2View : public DcpButtonView
{
    Q_OBJECT
    //DUI_STYLABLE
	DUI_VIEW(DcpButtonModel, DcpButtonStyle)

public:
    DcpButton2View(DcpButton *controller);

    virtual ~DcpButton2View();

    virtual void paintText(QPainter *painter);

	virtual QRectF boundingRect() const;

private:
    Q_DISABLE_COPY(DcpButton2View);
};

#endif
