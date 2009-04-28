#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H
#include "dcpmaincategory.h"

class DcpAppletMetadata;

class DcpMostUsedCategory  : public DcpMainCategory
{

public:
    DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent=0);

    virtual void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    void addComponent(DcpAppletMetadata *metadata, bool line = true);

protected:
    virtual void createContents();

};

#endif
