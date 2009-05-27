#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include "dcpmaincategory.h"

class DcpAppletMetadata;

class DcpMostUsedCategory  : public DcpMainCategory
{
    Q_OBJECT
public:
    DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent=0);

    void addComponent(DcpAppletMetadata *metadata, bool fullLine = false);

    virtual void onOrientationChange(const Dui::Orientation& orientation);

protected:
    virtual void createContents();
    void correctLines();

};

#endif
