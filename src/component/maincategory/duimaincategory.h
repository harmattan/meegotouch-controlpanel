#ifndef DUIMAINCATEGORY_H
#define DUIMAINCATEGORY_H

#include "duisettingscategory.h"

class DuiMainCategory : public DuiSettingsCategory
{
public:
    DuiMainCategory(const QString& title=tr("Settings"),
                    QGraphicsWidget *parent=0);

    virtual void add(DuiSettingsComponent *component);
    virtual void add(DuiSettingsComponent *component,
                     DuiSettingsComponent *component);

protected:
    virtual void createContents();
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

};

#endif // DUIMAINCATEGORY_H
