#ifndef TIMEZONECONTAINER_H
#define TIMEZONECONTAINER_H

#include <DuiWidget>
#include <QList>

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
    void backPushed(bool pushed);
    void updateLayout();
    void addMoreItems();
    void filter(const QString& sample);

protected:
    void initWidget();
    void updateSeparators();
    void updateGridSeparator();
    void updateHSeparator();

private:
    QList<TimeZoneListItem*> m_ItemList;
    DuiLayout *m_MainLayout;
    DuiGridLayoutPolicy *m_MainLayoutPolicy;
    DuiLinearLayoutPolicy *m_MainVLayoutPolicy;
    TimeZoneListItem *m_CheckedItem;
    bool m_BackPushed;
    QString m_FilterSample;
    void checkIfFiltered(TimeZoneListItem* item);
    void addItemToPolicies(TimeZoneListItem* item);

private slots:
    virtual void orientationChanged();
    virtual void itemClicked(TimeZoneListItem* item);

signals:
    void listItemAdded();
};
#endif // TIMEZONECONTAINER_H

