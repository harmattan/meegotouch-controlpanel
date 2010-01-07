/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPMAINCATEGORY_H
#define DCPMAINCATEGORY_H

#include "dcpcategory.h"

class DuiLayout;
class QShowEvent;

/*!
 * A rectangular table like widget inside the main page and the category pages.
 */
class DcpMainCategory : public DcpCategory
{
    Q_OBJECT

public:
    DcpMainCategory(
            const QString    &title,
            QGraphicsWidget  *parent = 0,
            const QString    &logicalId = "");

    virtual ~DcpMainCategory ();

    
    virtual void appendWidget (DcpComponent *component);
    virtual int  maxColumns ();
    virtual void setMaxColumns (int columns);
    DuiLayout* duiLayout() const { return m_Layout; }

    void setHorizontalSpacing (int space);
    void setVerticalSpacing (int space);
    void setCreateSeparators (bool create = true);
    void setDoNotRemoveLastSeparator (bool remove = true);

    int getItemCount () { return m_ItemCount; };
    void deleteItems();

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    virtual void createContents ();
    virtual void showEvent (QShowEvent *);

    DuiLayout                    *m_Layout;
    class DuiGridLayoutPolicy    *m_LandscapeLayout;
    class DuiLinearLayoutPolicy  *m_PortraitLayout;

private:
    void appendSeparatorsIfNeeded ();
    void incrementRowAndCol ();

    int m_MaxColumns;

    /*
     * These will point to the first empty coordinate available for inserting a
     * new item.
     */
    int m_ColCount;
    int m_RowCount;
    /*
     * The number of real items added (not the separators).
     * FIXME: We can implement the whole stuff without this, can't we?
     */
    int m_ItemCount;

    bool m_CreateSeparators;
    bool m_HasLastSeparator;
};

#endif
