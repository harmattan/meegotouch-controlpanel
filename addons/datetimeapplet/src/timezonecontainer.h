#ifndef TIMEZONECONTAINER_H
#define TIMEZONECONTAINER_H

#include <DuiWidget>
#include <QMap>

class TimeZoneListItem;

class TimeZoneContainer : public DuiWidget
{
    Q_OBJECT

public:
    TimeZoneContainer(DuiWidget *parent = 0);
    virtual ~TimeZoneContainer();

protected:
    void initWidget();

private:
    QMap<int, TimeZoneListItem*> m_ItemMap;

private slots:
    virtual void itemClicked(TimeZoneListItem* item);

signals:
    void closing();
};

#endif // TIMEZONECONTAINER_H
