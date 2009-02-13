#ifndef DUISETTINGSCATEGORY_H
#define DUISETTINGSCATEGORY_H
#include "duisettingscomponent.h"
class DuiSettingsCategory : public DuiSettingsComponent
{
    Q_OBJECT
public:
    explicit DuiSettingsCategory(const QString& title="",
                                 QGraphicsWidget *parent=0);
    virtual void paint (QPainter *painter, 
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget=0);
    // Composite Pattern Interface	
    virtual void add(DuiSettingsComponent *component);
    virtual void remove(DuiSettingsComponent *component);
    virtual DuiSettingsComponent* child(int i) const;
    DuiSettingsCategory* category() const {return 0;};
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);
private:
    QVector<DuiSettingsComponent*> m_Children; 
};
#endif //DUISETTINGSCATEGORY_H
