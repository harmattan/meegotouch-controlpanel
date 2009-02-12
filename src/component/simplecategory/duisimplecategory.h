#ifndef DUISIMPLECATEGORY_H
#define DUISIMPLECATEGORY_H
#include "duisettingscategory.h"
class DuiSimpleCategory : public DuiSettingsCategory
{
    Q_OBJECT
public:
    explicit DuiSimpleCategory(const QString& title="",
                                 QGraphicsWidget *parent=0);
    virtual void paint (QPainter *painter, 
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget=0);
protected:
    virtual void createContents();    
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);
};
#endif //DUISETTINGSCATEGORY_H
