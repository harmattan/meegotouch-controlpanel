#ifndef DCPRECENTLYUSEDCOMPONENT_H
#define DCPRECENTLYUSEDCOMPONENT_H

#include "dcpcomponent.h"

class DcpMostUsedCategory;

class DcpRecentlyUsedComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpRecentlyUsedComponent(DcpCategory *category, QGraphicsWidget *parent=0);

    virtual void createContents();
    virtual void add(DcpComponent*){}
    virtual void remove(DcpComponent*){}

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    DcpMostUsedCategory *m_MostUsedCategory;
	
};

#endif // DCPRECENTLYUSEDCOMPONENT_H
