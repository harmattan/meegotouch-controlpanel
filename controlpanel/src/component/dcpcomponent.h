#ifndef DCPCOMPONENT_H
#define DCPCOMPONENT_H

#include <DuiWidget>
#include <Pages>

class DcpComponent : public DuiWidget
{
    Q_OBJECT
    Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)

public:
    explicit DcpComponent(DcpComponent *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0,
                                  const QString& logicalId="");

    QString title() const {return m_Title;}
    virtual void setTitle(const QString& title) {m_Title = title;}
    void setSubPage (const PageHandle &subPage) {m_SubPage = subPage;}
    void setSubPage (const PageHandle::PageTypeId id, const QString &param="", 
                     const int widgetId=-1, const bool isStandalone=false)
        { m_SubPage.id = id; m_SubPage.param = param; 
          m_SubPage.widgetId = widgetId; m_SubPage.isStandalone = isStandalone; }
    const PageHandle &subPage() const { return m_SubPage; }

    DcpComponent* category() const { return m_Category; }
    
    virtual const QString logicalId() { return m_LogicalId; }
    void setLogicalId(const QString& logicalId) { m_LogicalId = logicalId; }

    QString mattiID() const;
    void setMattiID(const QString &mattiID);

protected:
    virtual void createContents() = 0;

private:
    QString m_Title;
    QString m_LogicalId;
    QString m_MattiID;
    DcpComponent* m_Category;
    PageHandle m_SubPage;
};
#endif //DCPCOMPONENT_H
