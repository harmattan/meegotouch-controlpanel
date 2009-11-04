#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include <DcpMainCategory>

class DcpAppletMetadata;

class DcpAppletButtons  : public DcpMainCategory
{
    Q_OBJECT
    Q_PROPERTY(QString mattiID READ mattiID WRITE setMattiID)
public:
    DcpAppletButtons(const QString& logicalId,
                     const QString& categoryName,
                     const QString& title,
                     QGraphicsWidget *parent=0);

    void addComponent(DcpAppletMetadata *metadata, bool fullLine = false);

    virtual void reload();

    QString mattiID();
    void setMattiID(const QString &mattiID);

protected:
    virtual void createContents();
private:
  QString m_CategoryName;
  QString m_mattiID;
};

#endif
