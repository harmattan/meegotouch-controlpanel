#ifndef DUISIMPLECATEGORY_H
#define DUISIMPLECATEGORY_H

#include "duisettingscategory.h"

class DuiLinearLayout;

class DuiSimpleCategory : public DuiSettingsCategory
{
    Q_OBJECT
public:
    explicit DuiSimpleCategory(const QString& title="",
                                 QGraphicsWidget *parent=0);
    virtual void paint (QPainter *painter, 
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget=0);
    virtual void add(DuiSettingsComponent *component);

protected:
    virtual void createContents();    

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    DuiLinearLayout *m_Layout;

 };

#endif //DUISETTINGSCATEGORY_H
