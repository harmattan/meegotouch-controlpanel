#ifndef DCPCATEGORYCOMPONENT_H
#define DCPCATEGORYCOMPONENT_H

#include <DcpComponent>

class DcpAppletButtons;
class DuiContainer;

class DcpCategoryComponent: public DcpComponent
{
    Q_OBJECT
    Q_PROPERTY(QString mattiID READ mattiID WRITE setMattiID)
public:
    DcpCategoryComponent(DcpCategory *category, const QString& categoryName,
                         const QString& logicalId,
                         QGraphicsWidget *parent=0);
    virtual ~DcpCategoryComponent();
    virtual void createContents();
    virtual void add(DcpComponent*){}
    virtual void remove(DcpComponent*){}

    void setTitle(const QString& text);

    void reload();

    QString mattiID();
    void setMattiID(const QString &mattiID);

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    DcpAppletButtons *m_AppletButtons;
    QString m_CategoryName;
    DuiContainer *m_Container;
    QString m_mattiID;
};


#endif // DCPCATEGORYCOMPONENT_H
