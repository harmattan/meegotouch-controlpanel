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
    virtual void append(DcpComponent *component);
    virtual void setMaxColumns(int columns){m_MaxColumns = columns;};
protected:
    virtual void createContents();

protected:
    class DuiGridLayout* m_Layout;
    int m_MaxColumns;
    int m_ColCount;
    int m_RowCount;
};

#endif // DCPMAINCATEGORY_H
