#ifndef DCPSIMPLECATEGORY_H
#define DCPSIMPLECATEGORY_H

#include "dcpcategory.h"

class DuiLinearLayout;

class DcpSimpleCategory : public DcpCategory
{
    Q_OBJECT
public:
    explicit DcpSimpleCategory(const QString& title="",
                                 QGraphicsWidget *parent=0);
    virtual void paint (QPainter *painter, 
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget=0);
    virtual void add(DcpComponent *component);

protected:
    virtual void createContents();    

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    DuiLinearLayout *m_Layout;

 };

#endif //DCPSETTINGSCATEGORY_H
