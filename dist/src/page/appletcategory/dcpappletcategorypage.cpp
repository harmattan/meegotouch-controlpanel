#include "dcpappletcategorypage.h"
#include <QDebug>
#include "dcpmaincategory.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#include "dcplabelcomponent.h"
#include "dcplabel2component.h"
#include "dcplabel2togglecomponent.h"
#include "dcplabel2imagecomponent.h"
#include "dcplabelbuttoncomponent.h"

DcpAppletCategoryPage::DcpAppletCategoryPage(const QString &appletCategory) 
                      : DcpCategoryPage(),
                        m_AppletCategory(appletCategory) 
{
    setHandle(Pages::APPLETCATEGORY);
    setReferer(Pages::MAIN);
}

DcpAppletCategoryPage::~DcpAppletCategoryPage()
{
} 

void DcpAppletCategoryPage::createContent()
{
    DcpCategoryPage::createContent();
    m_Category->setMaxColumns(2);
    DcpAppletDb::instance()->refresh();
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());

    if (!list.isEmpty())
    {
        bool odd =list.size() % 2 == 1;
    	DcpAppletMetadataList::const_iterator i;  
        for (i = list.begin(); i != list.end(); ++i)
        {
            addComponent(*i, i == list.end() - 1 && odd);
        }
    }
    
    setTitle(appletCategory());
}

void DcpAppletCategoryPage::addComponent(DcpAppletMetadata *metadata, bool odd)
{
    DcpComponent *component = 0;

#if 0
     switch(metadata->widgetTypeID()) {
         case DCPLABEL:
             component = new DcpLabelComponent(0, metadata);
         break;
         case DCPLABEL2:
             component = new DcpLabel2Component(0, metadata);
             /* FIXME: apply this to all components when bigbutton
                is on all DcpBasicComponent */
             qobject_cast<DcpLabel2Component*>(component)->setBgObjectName(
                     "AppletPageDcpButton");
         break;
         case DCPLABELBUTTON:
             component = new DcpLabelButtonComponent(0, metadata);
         break;
         case DCPLABEL2BUTTON:
             component = new DcpLabel2ButtonComponent(0, metadata);
         break;
         case DCPLABEL2IMAGE :
             component = new DcpLabel2ImageComponent(0, metadata);
         break;
         default:
         break;
     }
 
#endif
   // TODO: this is to show the new widget only (temporary)
    component = new DcpLabel2Component(0, metadata);
    component->setMaximumSize(99999, 99999);
 
    if (component) {

        component->setSubPage(Pages::APPLET, metadata->name());
        connect(component, SIGNAL(openSubPage(Pages::Handle)),
                        this, SIGNAL(openSubPage(Pages::Handle)));
        if (odd)
        {	
    qobject_cast<DcpLabel2Component*>(component)->setBgObjectName("AppletPageDcpButton2");
            qDebug("Dcp: ADD");
            component->setMinimumWidth(size().width());
            m_Category->add(component);
        }
	else
        {
    qobject_cast<DcpLabel2Component*>(component)->setBgObjectName("AppletPageDcpButton");
        	m_Category->append(component);
        }
    }
}
