/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#include "dcpappletloader.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include <QPluginLoader>
#include "dcpwrongapplets.h"

//#define DEBUG
#include "dcpdebug.h"

DcpAppletLoader::DcpAppletLoader (
        const DcpAppletMetadata *metadata)
: m_Metadata(metadata)
{
    m_Applet = 0;
    load ();
}

DcpAppletLoader::~DcpAppletLoader()
{
    if (m_Applet)
        delete m_Applet;

    m_Applet = 0;
}

/*
 * Loads the applet from a binary file (a shared object file) stores the 
 * DcpAppletIf plugin object and initializes it by calling the init() virtual 
 * function. Returns true if the object was loaded and initialized.
 */
bool 
DcpAppletLoader::loadPluginFile (
        const QString &binaryPath)
{
    /*
     * We check if the given binary is backlisted because of a previous fault
     * (e.g. segmentation fault).
     */
    if (DcpWrongApplets::instance()->isAppletRecentlyCrashed (binaryPath)) {
        DCP_WARNING ("The '%s' is a blacklisted applet", 
                DCP_STR (m_Metadata->name()));

        m_ErrorMsg = "Blacklisted applet";
        m_Applet = 0;
        return false;
    }

    QPluginLoader loader (binaryPath);
    if (!loader.load ()) {
        m_ErrorMsg = "Loading applet failed: " + loader.errorString();
	    DCP_WARNING ("The loading of applet '%s' has been failed: %s",
                DCP_STR (m_Metadata->name()),
                DCP_STR (loader.errorString()));
    } else {
        QObject *object = loader.instance();
        m_Applet = qobject_cast<DcpAppletIf*>(object);

        if (!m_Applet) {
            m_ErrorMsg = "Can't convert object to ExampleAppletInterface.";
            DCP_WARNING ("");
            return false;
        } else {
            m_Applet->init ();
            #if 0
            connect (object, SIGNAL(activate()),
                    m_Metadata, SIGNAL (activate()));
            #endif
        }
    }

    return true;
}

/*
 * Loads a DSL (Declarative Settings Language) file.
 * Not implemented yet.
 */
bool 
DcpAppletLoader::loadDslFile (
        const QString &binaryPath)
{
    Q_UNUSED (binaryPath);
    DCP_WARNING ("Unimplemented.");


    return false;
}

void 
DcpAppletLoader::load ()
{
    QString binaryPath = m_Metadata->fullBinary();
    QString dslFilename = m_Metadata->dslFilename ();

    DCP_DEBUG ("*** binaryPath          = '%s'", DCP_STR (binaryPath));
    DCP_DEBUG ("*** dslFilename         = '%s'", DCP_STR (dslFilename));
    DCP_DEBUG ("*** applicationCommand  = '%s'", 
            DCP_STR (m_Metadata->applicationCommand ()));

    if (!binaryPath.isEmpty()) {
        loadPluginFile (binaryPath);
    } else if (!dslFilename.isEmpty()) {
        loadDslFile (dslFilename);
    }
}

