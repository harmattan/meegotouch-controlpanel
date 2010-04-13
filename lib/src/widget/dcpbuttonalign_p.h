#ifndef DCPBUTTONALIGNPRIVATE_H
#define DCPBUTTONALIGNPRIVATE_H

class DcpButtonAlignPrivate { 
public:
    DcpButtonAlignPrivate ();
    MWidget              *alignedWidget;
    QGraphicsLinearLayout  *alignLayout;
    Qt::Alignment           alignment;
}; 
#endif // DCPBUTTONALIGNPRIVATE_H
