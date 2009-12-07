#ifndef DCPAPPLETLOADER_APPLET_H__
#define DCPAPPLETLOADER_APPLET_H__

#include <QObject>
#include <QVector>
#include <DuiAction>
#include <QtDebug>

#include "dcpappletif.h"

class DcpAppletLoaderApplet : public QObject, public DcpAppletIf {
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

    public:
        DcpAppletLoaderApplet() : m_Initialized(false) {
        }
        virtual void init() { 
            m_Initialized = true;
        }
        virtual DcpWidget *constructWidget(int);
        virtual QString title() const { return 0; };
        virtual QVector<DuiAction *> viewMenuItems() {
            QVector<DuiAction*> empty;
            return empty;
        }
        virtual DcpBrief* constructBrief(int) { return 0; };

        bool initialized() {
            return m_Initialized;
        }

    private:
        bool m_Initialized;
};

#endif
