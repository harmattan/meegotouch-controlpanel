#ifndef TIMEZONECONTAINER_H
#define TIMEZONECONTAINER_H

#include <DuiWidget>
#include <QMap>

class TimeZoneListItem;
class DuiLayout;
class DuiGridLayoutPolicy;
class DuiLinearLayoutPolicy;

class TimeZoneContainer : public DuiWidget
{
    Q_OBJECT

public:
    TimeZoneContainer(DuiWidget *parent = 0);
    virtual ~TimeZoneContainer();
    QMap<int, TimeZoneListItem*> getMap();
    void updateLayout();

protected:
    void initWidget();
    void updateGridSeparator();
    void updateHSeparator();

private:
    QMap<int, TimeZoneListItem*> m_ItemMap;
    DuiLayout *m_MainLayout;
    DuiGridLayoutPolicy *m_MainLayoutPolicy;
    DuiLinearLayoutPolicy *m_MainVLayoutPolicy;
    TimeZoneListItem *m_CheckedItem;

private slots:
    virtual void orientationChanged();
    virtual void itemClicked(TimeZoneListItem* item);
};
#endif // TIMEZONECONTAINER_H

