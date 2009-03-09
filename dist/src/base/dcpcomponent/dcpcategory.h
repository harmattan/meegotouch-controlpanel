#ifndef DCPCATEGORY_H
#define DCPCATEGORY_H
#include "dcpcomponent.h"
class DcpCategory : public DcpComponent
{
    Q_OBJECT
public:
    explicit DcpCategory(const QString& title,
                                 QGraphicsWidget *parent=0);

    // Composite Pattern Interface	
    virtual void add(DcpComponent *component);
    virtual void remove(DcpComponent *component);
    virtual DcpComponent* child(int i) const;
    DcpCategory* category() const {return 0;}

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    QVector<DcpComponent*> m_Children; 
};
#endif //DCPCATEGORY_H
