/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include <DcpCategoryPage>

class DcpMainCategory;
class DcpCategoryComponent;

class DcpMainPage : public DcpPage
{
    Q_OBJECT

public:
    DcpMainPage();
    
    virtual void createContent ();
    virtual void createContentsLate ();

    virtual void reload();

signals:
    void firstShown (void);

public slots:
    void back();
    void shown ();

protected:
    virtual void retranslateUi();

private:
    DcpCategoryComponent *m_RecentlyComp;
    bool                  m_HasContent;

};

#endif
