/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#include "dcpappletloader.h"
#include "dcpappletloader_p.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include <QPluginLoader>
#include "dcpwrongapplets.h"

#define DEBUG
#define WARNING
#include "dcpdebug.h"

DcpAppletLoader::DcpAppletLoader (
        const DcpAppletMetadata *metadata):
   d_ptr(new DcpAppletLoaderPrivate(metadata))
{
    load();
}

DcpAppletLoaderPrivate::DcpAppletLoaderPrivate(
        const DcpAppletMetadata* metadata):
    metadata (metadata)
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
DcpAppletLoader::applet()
{
    /*
     * It is possible that the applet was disabled before, but it is enabled
     * now. 
     */
    DCP_DEBUG ("The applet is %s",
            d_ptr->metadata->isDisabled() ? "disabled" : "enabled");
    if (d_ptr->applet == 0 && 
            d_ptr->metadata && !d_ptr->metadata->isDisabled())
        loadPluginFile (d_ptr->metadata->fullBinary());

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
     * We only check that the applet is blacklicted or not (due for example to a
     * previous segfault), if the applet is disabled. This way the application
     * can re-enable the applet. We currently re-enable the applet when the user
     * explicitly clicks on the applet brief.
     */
    if (d_ptr->metadata && d_ptr->metadata->isDisabled ()) {
        if (DcpWrongApplets::instance()->isAppletRecentlyCrashed (binaryPath)) 
            d_ptr->errorMsg =  "The " + binaryPath + "is a blacklisted applet";
        else
            d_ptr->errorMsg =  "The " + binaryPath + "is a disabled applet";

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
            DCP_DEBUG ("Initializing %s", DCP_STR (binaryPath));
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

