/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletdb.h"
#include "dcpappletdb_p.h"
#include "dcpappletmetadata.h"
#include <QDir>
#include <QDebug>

#define DEBUG
#include "dcpdebug.h"

const QString AppletFilter = "*.desktop";
DcpAppletDb* DcpAppletDbPrivate::sm_Instance = 0;
DcpAppletDbPrivate::DcpAppletDbPrivate()
{
    hasUniqueMetadata = false;
}


DcpAppletDbPrivate::~DcpAppletDbPrivate()
{}

DcpAppletDb::DcpAppletDb (
        const QString   &pathName,
        const QString   &nameFilter) : d_ptr(new DcpAppletDbPrivate())
{
    if (!pathName.isEmpty()) 
        addFiles (pathName, nameFilter);
}

DcpAppletDb::~DcpAppletDb()
{
}

/*!
 *
 * Use this function to get the instance of the DcpAppletDb singleton, by
 * re-using the existing one and initializing it.
 */
DcpAppletDb *
DcpAppletDb::instance (
        const QString   &pathName,
        const QString   &nameFilter)
{
    if (!DcpAppletDbPrivate::sm_Instance) {
        DcpAppletDbPrivate::sm_Instance = new DcpAppletDb (pathName, nameFilter);
    }

    return DcpAppletDbPrivate::sm_Instance;
}


void 
DcpAppletDb::destroy ()
{
    if (!DcpAppletDbPrivate::sm_Instance) {
        DCP_WARNING ("There is no instance to destroy.");
        return;
    }

    DcpAppletDbPrivate::sm_Instance->destroyData();
    delete DcpAppletDbPrivate::sm_Instance;
    DcpAppletDbPrivate::sm_Instance = 0;
}

bool
DcpAppletDb::addFile (
        const QString& filename)
{
    if (containsFile(filename) || d_ptr->hasUniqueMetadata)
        return false;

    DcpAppletMetadata *metadata = new DcpAppletMetadata(filename);
    if (metadata->isValid()) {
        if (metadata->isUnique()) {
             d_ptr->appletsByName.clear();
             d_ptr->appletsByFile.clear();
             d_ptr->hasUniqueMetadata = true;
        }
        DCP_DEBUG ("Adding applet name '%s'", DCP_STR (metadata->name()));
        d_ptr->appletsByName[metadata->name()] = metadata;
        d_ptr->appletsByFile[filename] = metadata;
        return true;
    } else {
        metadata->deleteLater();
    }
    
    return false;
}

QStringList
DcpAppletDb::appletNames() const
{
    return d_ptr->appletsByName.keys();
}

bool
DcpAppletDb::containsFile(const QString& fileName)
{
    return d_ptr->appletsByFile.contains(fileName);
}

bool
DcpAppletDb::containsName (
        const QString &name)
{
    return d_ptr->appletsByName.contains (name);
}

bool
DcpAppletDb::addPath (const QString &pathName)
{
    DCP_DEBUG ("Will use filter '*.desktop'!");

    if (addFiles (pathName, "*.desktop")) {
        d_ptr->paths.append(pathName);
        return true;
    } else {
        return false;
    }
}

bool
DcpAppletDb::addFiles (
        const QString  &pathName, 
        const QString  &filter)
{
    QStringList nameFilters (filter);
    QDir        appDir (pathName);

    appDir.setNameFilters (nameFilters);
    foreach (QString appFile, appDir.entryList (QDir::Files)) {
        DCP_DEBUG ("Adding file '%s'", 
                DCP_STR (appDir.absoluteFilePath(appFile)));
        if (!addFile (appDir.absoluteFilePath(appFile)))
            return false;
    }

    return true;
}

DcpAppletMetadataList 
DcpAppletDb::list() const
{
    return d_ptr->appletsByFile.values();
}

/*!
 *
 */
DcpAppletMetadataList 
DcpAppletDb::listByCategory (
        const QString &category)
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, d_ptr->appletsByFile) {
        if (category.compare (item->category(), Qt::CaseInsensitive) == 0)
            filtered.append (item);

        // FIXME: This should not be done here!
        QString parentName = item->parentName ();
        if (parentName != "" && !item->parent()) {
            item->setParent (applet(parentName));
        }
    }

    qSort(filtered.begin(), filtered.end(), DcpAppletMetadata::orderLessThan);
    return filtered;
}

/*!
 * \param category An array of string pointers with the category names. All
 *   categories with these names will be added.
 * \param n_categories The size of the name array.
 * \param checkFunction If not NULL the function will be called with the
 *   category name of the metadata items and those that are getting false return
 *   value are going to be added too. Used to handle the uncategorized applets.
 */
DcpAppletMetadataList 
DcpAppletDb::listByCategory (
        const char **category,
        int          n_categories,
        checkCategory   checkFunction)
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, d_ptr->appletsByFile) {
        for (int n = 0; n < n_categories && category[n] != 0; ++n) {
            /*
             * We add this item if we asked to include the uncategorized
             * items and this is an uncategorized item or if the item is in the
             * category we are requested for.
             */
            #if 0
            DCP_WARNING ("------------------------------");
            DCP_WARNING ("applet        = %s", DCP_STR(item->name()));
            DCP_WARNING ("category      = %s", DCP_STR(item->category()));
            DCP_WARNING ("checkFunction = %p", checkFunction);
            DCP_WARNING ("checked       = %s", 
                    checkFunction && checkFunction (item->category ()) ?
                    "true" : "false");
            #endif

            if ((checkFunction && !checkFunction (item->category ())) ||
                    !item->category().compare (
                        QString(category[n]), Qt::CaseInsensitive)) {
                //DCP_WARNING ("Adding applet %s", DCP_STR(item->name()));
                filtered.append (item);
                break;
            }
        }

        // FIXME: This should not be done here!
        QString parentName = item->parentName ();
        if (parentName != "" && !item->parent()) {
            item->setParent (applet(parentName));
        }
    }

    qSort (filtered.begin(), filtered.end(), DcpAppletMetadata::orderLessThan);
    return filtered;
}

DcpAppletMetadataList 
DcpAppletDb::listMostUsed ()
{
    DcpAppletMetadataList mostUsed;

    for (QMap<QString, DcpAppletMetadata*>::iterator iter =
            d_ptr->appletsByName.begin(); iter != d_ptr->appletsByName.end(); iter++)
        if (iter.value()->usage())
            mostUsed.push_back(iter.value());

   qSort (mostUsed.begin(), mostUsed.end(), 
           DcpAppletMetadata::usageGreatherThan); 

   /*
    * Yes, the UI specification states the maximum number of items shown in the
    * 'most used category'. The number might change, but there always will be a
    * limit.
    */
   return mostUsed.mid (0, DcpApplet::MaxMostUsed);
}


/*!
 * \brief Returns the applet found in the database by its name.
 *
 * FIXME: This is actually a localized name, that is changed when the language
 * settings are changed. This might cause some problems in the future.
 */
DcpAppletMetadata *
DcpAppletDb::applet (
        const QString &name)
{
    DcpAppletMetadata *metadata = d_ptr->appletsByName.value(name, 0);

    if (!metadata)
        qWarning() << "No such applet:" << name;

    return metadata;
}

void DcpAppletDb::refresh()
{
    foreach(QString pathName, d_ptr->paths)
        refreshPath(pathName);

    foreach(DcpAppletMetadata *metadata, d_ptr->appletsByName) {
        if (!metadata->isValid()) {
            eraseEntry(metadata);
        } else if (metadata->isModified()) {
             QString fileName = metadata->fileName();
             eraseEntry(metadata);
             addFile(fileName);
        } 
    }
}

void 
DcpAppletDb::refreshPath (
        const QString &pathName)
{
    DCP_DEBUG ("");

    /*
     * FIXME: Should not we re-use the already set filterName?
     */
    QDir appDir(pathName, AppletFilter);
    if (!appDir.exists()) {
        qWarning() << "Applet dir" << pathName << "does not exists";
        return;
    }
    
    foreach(QString appFile, appDir.entryList()) {
        QString fileName = appDir.absoluteFilePath(appFile);
        if (!d_ptr->appletsByFile.contains(appFile)) {
            addFile(fileName);
        }
    }
}

void 
DcpAppletDb::eraseEntry (
        DcpAppletMetadata *metadata)
{
    d_ptr->appletsByName.remove(metadata->name());
    d_ptr->appletsByFile.remove(metadata->fileName());
    metadata->deleteLater();
}

void 
DcpAppletDb::destroyData ()
{
    DCP_WARNING ("Destroying all metadata.");
    foreach(DcpAppletMetadata *metadata, d_ptr->appletsByName) {
        metadata->deleteLater();
    }
}

