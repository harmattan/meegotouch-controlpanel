#ifndef FT_DCPCOMPONENT_H
#define FT_DCPCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpComponent class declaration
#include <dcpcomponent.h>

Q_DECLARE_METATYPE(DcpComponent*);

class DcpSingleComponent : public DcpComponent
{
    Q_OBJECT
public:
    explicit DcpSingleComponent(DcpCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0,
                                  const QString& logicalId="");
    virtual void add(DcpComponent *component); 
    virtual void remove(DcpComponent *component); 
protected:
    virtual void createContents(); 
};

class Ft_DcpComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testSubPage();
    void testTitle();
    void testChild();
    void testCategory();
    void testLogicalId();    

private:
    DcpComponent* m_subject;
    DcpCategory* m_Category;
    QString m_Title;
    QGraphicsWidget *m_Parent;
    QString m_LogicalId;
    
};

#endif
