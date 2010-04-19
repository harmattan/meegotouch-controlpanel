#ifndef DCPCATEGORYCOMPONENT_H
#define DCPCATEGORYCOMPONENT_H

#include <DcpComponent>

#include "maintranslations.h"


class DcpAppletButtons;
class MContainer;

/*!
 * \class DcpCategoryComponent
 * \brief A component for the recently used applets
 *
 * It is supplies the background and title for around DcpAppletButtons,
 * which contains the buttons. (Actually uses MContainer for that.)
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

    bool reload();

    // ! Can be misleading, because it returns the count of the items already
    // loaded
    int getItemCount ();
//signals:
    // emit after reloading contents
  //  void reloaded(); 
private:
    DcpAppletButtons *m_AppletButtons;
    const DcpCategoryInfo  *m_CategoryInfo;
    MContainer     *m_Container;
    QString           m_LogicalId;
    friend class Ut_DcpCategoryComponent;
};


#endif

