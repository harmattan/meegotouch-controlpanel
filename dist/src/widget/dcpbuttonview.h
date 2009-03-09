#ifndef DCPBUTTONVIEW_H
#define DCPBUTTONVIEW_H

#include <duibuttonview.h>

class DcpButtonView: public DuiStylable<DcpButtonView, DuiButtonView>{
    Q_OBJECT

public:
    DcpButtonView(DuiButton *controller);

    static void registerStyleAttributes(DuiStyleDescription& description);

protected:
    virtual void paint ( QPainter * painter,
                         const QStyleOptionGraphicsItem * option,
                         QWidget * widget = 0 );
    virtual void styleUpdated ();

private:
    DuiButton* m_Controller;
    QString m_BgId;
};


#endif // DCPBUTTONVIEW_H
