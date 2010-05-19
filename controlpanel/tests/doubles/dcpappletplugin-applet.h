#ifndef DCPAPPLETLOADER_APPLET_H__
#define DCPAPPLETLOADER_APPLET_H__

#include <QObject>
#include <QVector>
#include <MAction>
#include <QtDebug>

#include "dcpappletif.h"

class DcpAppletPluginApplet : public QObject, public DcpAppletIf {
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

    public:
        DcpAppletPluginApplet() : m_Initialized(false) {
        }
        virtual void init() { 
            m_Initialized = true;
        }
        virtual DcpWidget *constructWidget(int) {return 0;};
        virtual QString title() const { return 0; };
        virtual QVector<MAction *> viewMenuItems() {
            QVector<MAction*> empty;
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
