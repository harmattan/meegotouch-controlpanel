#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QMap>
#include <QString>
#include "dcpapplet.h"
/*!
    \class DcpAppletMetadata    
    \brief This singleton class keeps track of all installed applets of Conrol Panel
    \details  Applet database can be filled with desktop files and then can
     be queried by category, usage, by applet name.
     The database is live, so any changes in the desktop files are applied on refresg
*/
class DcpAppletMetadata;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;
typedef QMap<QString, DcpAppletMetadata*> DcpAppletMetadataMap;


class DcpAppletDb
{
public:
    /*! \brief Initializes and returns the singleton instance.

        It only can be called once and only before instance() gets called.
        Calling this function is not mandatory. When it's not called,
        the instance will be initialized by DcpApplet::DefaultPath.

        \param pathName the initial path where the desktop files are found.
    */
    static DcpAppletDb *initInstance(const QString &pathName=DcpApplet::DefaultPath);
    /*! \brief Gives back the db instance
      */
    static DcpAppletDb *instance();
    /*! \brief adds files at a specified path pathName to the db */
    bool addPath(const QString &pathName);

    /* \brief adds files at specified pathName with specific name filter */
    bool addFiles(const QString& path, const QString& filter);
 
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
    DcpAppletMetadataList listByCategory(const QString& category);

    /*! \brief List the six most used applets
        \details gives backt the most used componnents but six*/
    DcpAppletMetadataList listMostUsed();

    /*! \reaturn metadata of an applet by name*/
    DcpAppletMetadata *applet(const QString& name);

    /*! \brief add one file to the db */
    bool addFile(const QString& filename);

    /*! \brief erase metadata from the db */
    void eraseEntry(DcpAppletMetadata *metadata);

    /*! \brief checks all the deskop files and reloads or erases them if needed*/
    void refresh();


    /*! \brief returns all applet names of the db */
    QStringList appletNames() const;

    /*! \brief checks if fileName has already added to the db */
    bool containsFile(const QString& fileName);

    /*! \brief checks if an applet with given name is already in the db */
    bool containsName(const QString& name);

    /*! \brief destroys all the contents (metadata) of the db */
	void destroyData(void);
    static void destroy(void);

protected:
    /*! \brief protected constructor for singleton*/
    DcpAppletDb(const QString &pathName);
    /*! \brief refresh a specified path*/
    void refreshPath(const QString &pathName);
private:
    DcpAppletMetadataMap m_AppletsByName;  
    DcpAppletMetadataMap m_AppletsByFile; 
    QList<QString> m_Paths;
    bool m_HasUniqueMetadata;
    static DcpAppletDb *sm_Instance;
};
#endif // DCPAPPLETDB_H

