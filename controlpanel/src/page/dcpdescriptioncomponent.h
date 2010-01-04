/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPDESCRIPTIONCOMPONENT_H
#define DCPDESCRIPTIONCOMPONENT_H

#include <DcpComponent>
class DuiContainer;

/*!
 * \class DcpDescriptionComponent
 * \brief DcpDescriptionComponent is a DcpComponent which is meant for
 * the main screen to providethe button that describes an an applet category.
 *
 * It displays a title and description about the category, and requests
 * the page switching if the user clicked on it.
 * Currently uses DuiContainer for all rendering stuff. 
 */
class DcpDescriptionComponent : public DcpComponent
{
Q_OBJECT

public:
    DcpDescriptionComponent(
            DcpCategory *category,
            const QString& title = "",
            QGraphicsWidget *parent = 0);

    void setDescription (const QString& desc);
    void setTextAlignment (Qt::Alignment align);

    virtual void add (DcpComponent*) {}
    virtual void remove (DcpComponent*) {}
    virtual void setTitle (const QString& title);

protected:
    virtual void createContents ();

private:
    class DuiLabel    *m_Description;
    Dui::Orientation   m_Orientation;
    DuiContainer      *m_Container;
};

#endif // DCPDESCRIPTIONCOMPONENT_H
