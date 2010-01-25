/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#include "dcpappletloader.h"
#include "dcpappletloader_p.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include <QPluginLoader>
#include "dcpwrongapplets.h"

#define WARNING
#include "dcpdebug.h"

DcpAppletLoader::DcpAppletLoader (
        const DcpAppletMetadata *metadata):
   d_prt(new DcpAppletLoaderPrivate(metadata))
{
    load();
}

DcpAppletLoaderPrivate::DcpAppletLoaderPrivate(const DcpAppletMetadata* metadata):
    metadata(metadata)
{
    applet = 0;
}

DcpAppletLoaderPrivate::~DcpAppletLoaderPrivate ()
{}

DcpAppletLoader::~DcpAppletLoader()
{
    if (d_ptr->applet)
        delete d_ptr->applet;

    d_ptr->applet = 0;
}

/*!
 * \returns The applet interface of the applet loader.
 *
 * Returns the applet interface, the interface object created by the applet if
 * the applet loaded successfully. Returns NULL if the applet was not loaded.
 * Please note that this method might return NULL!
 */
DcpAppletIf *
DcpAppletLoader::applet() const 
{ 
    return d_ptr->applet; 
}

/*!
 * \returns the metadata of the applet
 */
const DcpAppletMetadata*
DcpAppletLoader::metadata () const 
{ 
    return d_ptr->metadata;
}

/*!
 * \returns the error message string describes the problem why the applet was
 *   not loaded. Returns the empty string if the applet was loaded 
 *   successfully.
 */
const QString 
DcpAppletLoader::errorMsg () const
{ 
    return d_ptr->errorMsg; 
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
        d_ptr->errorMsg =  "The " + binaryPath + "is a blacklisted applet";
        DCP_WARNING ("%s", DCP_STR (d_ptr->errorMsg));
        qCritical() << d_ptr->errorMsg;

        d_ptr->applet = 0;
        return false;
    }

    QPluginLoader loader (binaryPath);
    if (!loader.load ()) {
        d_ptr->errorMsg = "Loading applet failed: " + loader.errorString();
        DCP_WARNING ("%s", DCP_STR (d_ptr->errorMsg));
        qCritical () << d_ptr->errorMsg;
    } else {
        QObject *object = loader.instance();
        d_ptr->applet = qobject_cast<DcpAppletIf*>(object);

        if (!d_ptr->applet) {
            d_ptr->errorMsg = "Loading of the " + binaryPath +
                "applet failed: Invalid ExampleAppletInterface object.";
            DCP_WARNING ("%s", DCP_STR (d_ptr->errorMsg));
            qCritical() << d_ptr->errorMsg;
            return false;
        } else {
            d_ptr->applet->init ();
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
    DCP_WARNING ("Loading of the DSL file is not implemented yet.");

    return false;
}

void 
DcpAppletLoader::load ()
{
    QString binaryPath = d_ptr->metadata->fullBinary();
    QString dslFilename = d_ptr->metadata->dslFilename ();

    DCP_DEBUG ("*** binaryPath          = '%s'", DCP_STR (binaryPath));
    DCP_DEBUG ("*** dslFilename         = '%s'", DCP_STR (dslFilename));
    DCP_DEBUG ("*** applicationCommand  = '%s'", 
            DCP_STR (d_ptr->metadata->applicationCommand ()));

    if (!binaryPath.isEmpty()) {
        loadPluginFile (binaryPath);
    } else if (!dslFilename.isEmpty()) {
        loadDslFile (dslFilename);
    }
}

