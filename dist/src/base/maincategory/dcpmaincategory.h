#ifndef DCPMAINCATEGORY_H
#define DCPMAINCATEGORY_H

#include "dcpcategory.h"
#include <QMap>
class DuiLayout;
class DcpMainCategory : public DcpCategory
{
    Q_OBJECT

public:
    DcpMainCategory(const QString& title,
                    QGraphicsWidget *parent=0);

    virtual void add(DcpComponent *component);
    virtual void append(DcpComponent *component);
    virtual void setMaxColumns(int columns);
    DuiLayout* duiLayout() const {return m_Layout;};

    void setHorizontalSpacing(int space);
    void setVerticalSpacing(int space);
    void setCreateSeparators (bool create = true);
    void setDoNotRemoveLastSeparator(bool remove = true);

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    virtual void createContents();
    virtual void polishEvent();
    void fixSeparators();

    DuiLayout* m_Layout;
    class DuiGridLayoutPolicy* m_LandscapeLayout;
    class DuiLinearLayoutPolicy* m_PortraitLayout;

    int m_MaxColumns;

    int m_ColCount;
    int m_RowCount;
    int m_ItemCount;

    bool m_CreateSeparators;
    bool m_HasLastSeparator;
};

#endif // DCPMAINCATEGORY_H
