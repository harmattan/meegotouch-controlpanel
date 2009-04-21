#ifndef REMOVABLELISTITEM_H
#define REMOVABLELISTITEM_H

#include <duiwidget.h>

class DuiButton;

class RemovableListItem : public DuiWidget
{
    Q_OBJECT

public:
    RemovableListItem(const QString &upText,
                      const QString &downText,
                      DuiWidget *parent = 0);
    RemovableListItem(const QString &text,
                      DuiWidget *parent = 0);
    virtual ~RemovableListItem();
    void setId(int id);
    int id();

protected:
    void initWidget();

private:
    QString     m_upText;
    QString     m_downText;
    int         m_id;
    DuiButton   *m_removeButton;

private slots:
    virtual void removeClicked();

signals:
    void clicked(int id);
};
#endif // REMOVABLELISTITEM_H
