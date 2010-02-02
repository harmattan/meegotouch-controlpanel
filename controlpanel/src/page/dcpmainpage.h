/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include <DcpCategoryPage>

/*!
 * If this macro is defined the windows will be first shown then the content
 * will be created. This feature is implemented so that the user will get a
 * feedback about the started application as soon as possible. Please note, that
 * the late initialization is not fully implemented, it does not look nice yet.
 * We have to see how the libdui is changing to implement some nice effect for
 * this.
 */
#define INITIALIZE_LATE

class DcpMainCategory;
class DcpCategoryComponent;

class DcpMainPage : public DcpPage
{
    Q_OBJECT

public:
    DcpMainPage();
    virtual ~DcpMainPage();
    
    #ifdef INITIALIZE_LATE
    virtual void createContentLate ();
    #else 
    virtual void createContent ();
    #endif

    virtual void reload();

public slots:
    void back();
    #ifdef INITIALIZE_LATE
    void shown ();
    #endif

protected:
    virtual void retranslateUi();
    virtual void organizeContent(const Dui::Orientation& ori);

private:
    DcpCategoryComponent *m_RecentlyComp;
    bool                  m_HasContent;
};

#endif
