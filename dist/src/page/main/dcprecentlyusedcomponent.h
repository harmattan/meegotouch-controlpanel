#ifndef DCPRECENTLYUSEDCOMPONENT_H
#define DCPRECENTLYUSEDCOMPONENT_H

#include "dcpbackgroundcomponent.h"

class DcpRecentlyUsedComponent: public DcpBackgroundComponent
{
    Q_OBJECT
public:
    DcpRecentlyUsedComponent(DcpCategory *category,
                            QGraphicsWidget *parent=0);

    virtual void createContents();

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
	
};


#endif // DCPRECENTLYUSEDCOMPONENT_H
