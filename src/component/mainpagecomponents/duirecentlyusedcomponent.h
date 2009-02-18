#ifndef DUIRECENTLYUSEDCOMPONENT_H
#define DUIRECENTLYUSEDCOMPONENT_H

#include "duibackgroundcomponent.h"

class DuiRecentlyUsedComponent: public DuiBackgroundComponent
{
    Q_OBJECT
public:
    DuiRecentlyUsedComponent(DuiSettingsCategory *category,
                            QGraphicsWidget *parent=0);

    virtual void createContents();

protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
	
};


#endif // DUIRECENTLYUSEDCOMPONENT_H
