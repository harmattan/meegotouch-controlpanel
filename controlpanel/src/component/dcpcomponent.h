#ifndef DCPCOMPONENT_H
#define DCPCOMPONENT_H

#include <duiwidget.h>
#include <Pages>

class DcpCategory;

class DcpComponent : public DuiWidget
{
    Q_OBJECT
public:
    explicit DcpComponent(DcpCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0,
                                  const QString& logicalId="");

    QString title() const {return m_Title;}
    virtual void setTitle(const QString& title) {m_Title = title;}
    void setSubPage(const Pages::Handle& subPage) {m_SubPage = subPage;}
    void setSubPage(const Pages::Id id, const QString &param="")
        {m_SubPage.id = id; m_SubPage.param = param;}
    const Pages::Handle& subPage() const {return m_SubPage;}
    // Composite Pattern Interface
    virtual void add(DcpComponent *component)=0;
    virtual void remove(DcpComponent *component)=0;

    virtual DcpComponent* child(int i) const;
    DcpCategory* category() const {return m_Category;}

    virtual const QString logicalId() {return m_LogicalId;}
    void setLogicalId(const QString& logicalId) {m_LogicalId = logicalId;}
protected:
    virtual void createContents() = 0;

protected slots:
    virtual void switchToSubPage ();
    virtual void switchToSubPageWithReferer (
		    const QString refererName, 
		    int           refererId);

signals:
    void openSubPage (const Pages::Handle &);
    void openSubPageWithReferer (const Pages::Handle &, const QString &, int);

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    QString m_Title;
    QString m_LogicalId;
    DcpCategory* m_Category;
    Pages::Handle m_SubPage;
};
#endif //DCPCOMPONENT_H
