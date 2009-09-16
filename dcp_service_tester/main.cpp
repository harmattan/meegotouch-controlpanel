#include <DuiControlPanelIf>

int main(int argc, char *argv[])
{
    // instantiate the interface
    DuiControlPanelIf* m_DcpIf = new DuiControlPanelIf();

    // check the interface is valid
    if (!m_DcpIf->isValid()) {
        qDebug() << "Err: Service unavailable";
        exit(0);
    }

    qDebug() << "Using service:" << m_DcpIf->serviceName();

    if (argc>1){
        QString page = argv[1];
        qDebug() << "Starting applet page" << page;
        m_DcpIf->appletPage(page);
    } else {
        qDebug() << "Starting main page";
        m_DcpIf->mainPage();
    }
    return 0;
}

