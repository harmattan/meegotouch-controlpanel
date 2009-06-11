#ifndef TIMEZONECONTAINER_H
#define TIMEZONECONTAINER_H

#include <DuiWidget>
#include <QMap>

class TimeZoneListItem;
class DuiLayout;
class DuiGridLayoutPolicy;

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

private:
    QMap<int, TimeZoneListItem*> m_ItemMap;
    DuiLayout *m_MainLayout;
    DuiGridLayoutPolicy *m_MainLayoutPolicy;

private slots:
    virtual void itemClicked(TimeZoneListItem* item);

// signals:
//    void closing();
};
#endif // TIMEZONECONTAINER_H

