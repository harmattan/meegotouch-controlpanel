#ifndef DUIMAINCATEGORY_H
#define DUIMAINCATEGORY_H

#include "duisettingscategory.h"

class DuiMainCategory : public DuiSettingsCategory
{
    Q_OBJECT

public:
    DuiMainCategory(const QString& title,
                    QGraphicsWidget *parent=0);

    virtual void add(DuiSettingsComponent *component);
    virtual void add(DuiSettingsComponent *component1,
                     DuiSettingsComponent *component2);

protected:
    virtual void createContents();

protected:
    class DuiGridLayout* m_Layout;

};

#endif // DUIMAINCATEGORY_H
