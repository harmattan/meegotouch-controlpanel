#ifndef TIMEZONEVIEW_H
#define TIMEZONEVIEW_H

#include "dcpwidget.h"

class DuiTextEdit;
class DcpTable;
class QModelIndex;
class QStandardItemModel;
class QSortFilterProxyModel;

class TimeZoneView : public DcpWidget
{
    Q_OBJECT

public:
    TimeZoneView(QGraphicsWidget *parent = 0);
    virtual ~TimeZoneView();

protected:
    void initWidget();

private:
    DuiTextEdit *m_TextEdit;
    DcpTable *m_Table;
    int m_SelectedItem;
    void selectItem(int item, bool selected = true);
    QStandardItemModel* m_FullModel;
    QSortFilterProxyModel* proxyModel();

private slots:
    void orientationChanged();
    void clearTextEdit(DuiTextEdit *textEdit);
    void filteringListItems();
    void onItemClicked( const QModelIndex &index);
};

#endif // TIMEZONEVIEW_H

