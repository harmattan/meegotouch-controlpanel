#include "dcpappletpage.h"

#include <DcpWidget>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletLoader>

#include <DuiLabel>
#include <DuiLocale>
#include <DuiAction>
#include <QtDebug>

DcpAppletPage::DcpAppletPage(DcpAppletMetadata *metadata):
    DcpPage(), 
	m_Metadata(metadata),
    m_MainWidget(0), 
	m_MissingLabel(0)
{
    setHandle(Pages::APPLET);
    setReferer(Pages::NOPAGE);
}

DcpAppletPage::~DcpAppletPage()
{
    clearup();
}

void DcpAppletPage::createContent()
{
    DcpPage::createContent();
    load();
}

bool DcpAppletPage::hasWidget() {
    return m_MainWidget;
}

bool DcpAppletPage::hasError() {
    return m_MissingLabel; 
}

void DcpAppletPage::load()
{
   m_LoadedMetadata = m_Metadata;
   if (m_Metadata && m_Metadata->isValid() && m_Metadata->applet()) {
       if (m_Metadata->partID() != -1)
          changeWidget(m_Metadata->partID());
       else
          changeWidget(0);
   } else {
       Q_ASSERT (!m_MissingLabel);
       m_MissingLabel = new DuiLabel(trid("dcp_no_applet_name",
                                    "Plugin not available"));
       m_MissingLabel->setAlignment(Qt::AlignCenter);
       append(m_MissingLabel);
       setTitle(trid("dcp_no_applet_title", "Missing plugin"));
   }
}

void DcpAppletPage::clearup()
{
    if (m_MainWidget) {
        m_MainWidget->deleteLater();
        m_MainWidget = 0;
    }
    if (m_MissingLabel) {
        m_MissingLabel->deleteLater();
        m_MissingLabel = 0;
    }
}

void DcpAppletPage::reload()
{
    if (m_Metadata != m_LoadedMetadata || !hasWidget()) {
        clearup();
        load();
    }
    DcpPage::reload();
    setReferer(Pages::NOPAGE); // means: referer should be set by pagefactory to the last page
}

void DcpAppletPage::back()
{
    if (!m_MainWidget || m_MainWidget->back())
        DcpPage::back();
}

void DcpAppletPage::changeWidget(int widgetId)
{
    if (m_MainWidget != 0) {
        remove (m_MainWidget);
    }

    m_MainWidget = m_Metadata->applet()->constructWidget(widgetId);

    // checks if applet does provide the widget

    if (!m_MainWidget) {
        return;
    }
    setPannableAreaInteractive(m_MainWidget->pagePans());

    connect(m_MainWidget, SIGNAL(changeWidget(int)), this, SLOT(changeWidget(int)));
    append(m_MainWidget);

    QVector<DuiAction*> vector = m_Metadata->applet()->viewMenuItems();
    if (!vector.isEmpty())
        for (int i = 0; i < vector.size(); i++)
            addAction(vector[i]);

    retranslateUi();
}

void DcpAppletPage::setMetadata (DcpAppletMetadata *metadata)
{
    m_Metadata = metadata;
}

void DcpAppletPage::retranslateUi()
{
    if (m_Metadata && m_Metadata->applet()) {
        setTitle(m_Metadata->applet()->title());
    }
}

