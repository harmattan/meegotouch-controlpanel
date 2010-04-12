#ifndef DCPCATEGORYCOMPONENT_H
#define DCPCATEGORYCOMPONENT_H

#include <DcpComponent>

#include "maintranslations.h"


class DcpAppletButtons;
class DuiContainer;

/*!
 * \class DcpCategoryComponent
 * \brief A component for the recently used applets
 *
 * It is supplies the background and title for around DcpAppletButtons,
 * which contains the buttons. (Actually uses DuiContainer for that.)
 */
class DcpCategoryComponent: public DcpComponent
{
Q_OBJECT

public:
    DcpCategoryComponent (
                    DcpComponent      *category,
                    const DcpCategoryInfo  *categoryInfo,
                    QGraphicsWidget  *parent = 0);

    virtual ~DcpCategoryComponent ();
    virtual void createContents ();
    virtual void add (DcpComponent*){}
    virtual void remove (DcpComponent*){}
    virtual void retranslateUi ();

    void setTitle(const QString& text);

    void reload();

    // ! Can be misleading, because it returns the count of the items already
    // loaded
    int getItemCount ();

private:
    DcpAppletButtons *m_AppletButtons;
    const DcpCategoryInfo  *m_CategoryInfo;
    DuiContainer     *m_Container;
    QString           m_LogicalId;
};


#endif

