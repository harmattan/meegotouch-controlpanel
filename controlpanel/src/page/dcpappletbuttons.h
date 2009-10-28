#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include <DcpMainCategory>

class DcpAppletMetadata;

class DcpAppletButtons  : public DcpMainCategory
{
    Q_OBJECT
public:
    DcpAppletButtons(const QString& logicalId, 
                     const QString& categoryName,
                     const QString& title,
                     QGraphicsWidget *parent=0);

    void addComponent(DcpAppletMetadata *metadata, bool fullLine = false);

    virtual void reload();

protected:
    virtual void createContents();
private:
  QString m_CategoryName;
};

#endif
