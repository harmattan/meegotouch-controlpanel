#ifndef DCPMAINCATEGORY_H
#define DCPMAINCATEGORY_H

#include "dcpcategory.h"

class DcpMainCategory : public DcpCategory
{
    Q_OBJECT

public:
    DcpMainCategory(const QString& title,
                    QGraphicsWidget *parent=0);

    virtual void add(DcpComponent *component);
    virtual void add(DcpComponent *component1,
                     DcpComponent *component2);

protected:
    virtual void createContents();

protected:
    class DuiGridLayout* m_Layout;

};

#endif // DCPMAINCATEGORY_H
