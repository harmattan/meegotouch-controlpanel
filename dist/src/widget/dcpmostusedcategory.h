#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include "dcpmaincategory.h"

#include <QPixmap>


class DcpMostUsedCategory  : public DcpMainCategory
{

public:
    DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent=0);


    virtual void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

protected:
    virtual void createContents();

  QPixmap *m_Background;
};

#endif
