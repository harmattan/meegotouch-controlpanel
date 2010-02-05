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
Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)

public:
    DcpCategoryComponent (
                    DcpComponent     *category, 
                    const QString   &categoryName,
                    const QString   &logicalId,
                    QGraphicsWidget *parent = 0);
    
    DcpCategoryComponent (
                    DcpComponent      *category, 
                    const DcpCategoryInfo  *categoryInfo,
                    QGraphicsWidget  *parent = 0);

    virtual ~DcpCategoryComponent ();
    virtual void createContents ();
    virtual void createContentsLate ();
    virtual void add (DcpComponent*){}
    virtual void remove (DcpComponent*){}
    virtual void retranslateUi ();

    void setTitle(const QString& text);

    void reload();
    int getItemCount ();

    QString mattiID();
    void setMattiID(const QString &mattiID);

private:
    DcpAppletButtons *m_AppletButtons;
    // m_CategoryName may be deprecated
    QString           m_CategoryName;
    const DcpCategoryInfo  *m_CategoryInfo;
    DuiContainer     *m_Container;
    QString           m_LogicalId;
    QString           m_mattiID;
};


#endif
