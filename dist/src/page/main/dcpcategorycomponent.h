#ifndef DCPCATEGORYCOMPONENT_H
#define DCPCATEGORYCOMPONENT_H

#include <DcpComponent>

class DcpAppletButtons;

class DcpCategoryComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpCategoryComponent(DcpCategory *category, const QString& categoryName,
                         QGraphicsWidget *parent=0);
    virtual ~DcpCategoryComponent();
    virtual void createContents();
    virtual void add(DcpComponent*){}
    virtual void remove(DcpComponent*){}

    void reload();

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    DcpAppletButtons *m_AppletButtons;
    QString m_CategoryName;
};


#endif // DCPCATEGORYCOMPONENT_H
