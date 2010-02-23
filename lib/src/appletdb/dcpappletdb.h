/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QMap>
#include <QString>
#include "dcpapplet.h"

/*!
 * \class DcpAppletMetadata    
 * \brief This singleton class keeps track of all installed applets of Conrol
 *   Panel
 * \details Applet database can be filled with desktop files and then can
 *   be queried by category, usage, by applet name.  The database is live, so
 *   any changes in the desktop files are applied on refresg
 */
class DcpAppletMetadata;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;

typedef bool (*checkCategory)(const QString &);

class DcpAppletDbPrivate;
class DcpAppletDb
{
public:
    /*!
     * \brief Gives back the db instance
     *
     * This function has two optional arguments, so the path and the filter can
     * be initialized as the very first step.
     */
    static DcpAppletDb *instance (
            const QString &pathName = DcpApplet::DefaultPath,
            const QString &nameFilter = "*.desktop");
    
    /*! \brief adds files at a specified path pathName to the db */
    bool addPath (const QString &pathName);

    /* \brief adds files at specified pathName with specific name filter */
    bool addFiles (const QString &path, const QString &filter);
 
    /*! \brief Database destructor */
    virtual ~DcpAppletDb();

    /*! \brief List all applets
        \return the metadata list of the applets
     */
    DcpAppletMetadataList list() const;

    /*! \brief Queries the db for a specified applet category
        \param category the name of the category
        \return the metadata list of the matching applets
    */
    DcpAppletMetadataList listByCategory(
                    const QString &category);
    
    DcpAppletMetadataList listByCategory (
                    const char    **category, 
                    int             n_categories,
                    checkCategory   checkFunction = 0);

    /*! \brief List the six most used applets
        \details gives backt the most used componnents but six*/
    DcpAppletMetadataList listMostUsed();

    /*! \reaturn metadata of an applet by name*/
    DcpAppletMetadata *applet(const QString& name);

    /*! \brief add one file to the db */
    bool addFile(const QString& filename);

    /*! \brief erase metadata from the db */
    void eraseEntry(DcpAppletMetadata *metadata);

    /*! \brief returns all applet names of the db */
    QStringList appletNames() const;

    /*! \brief checks if fileName has already added to the db */
    bool containsFile(const QString& fileName);

    /*! \brief checks if an applet with given name is already 
        in the db */
    bool containsName(const QString& name);

    /*! \brief destroys all the contents (metadata) of the db */
    void destroyData (void);
    static void destroy (void);

protected:
    /*! \brief protected constructor for singleton*/
    DcpAppletDb (const QString &pathName, const QString &nameFilter);

private:
    DcpAppletDbPrivate *const d_ptr;
    Q_DISABLE_COPY(DcpAppletDb);  
};
#endif // DCPAPPLETDB_H

