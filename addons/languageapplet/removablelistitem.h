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

protected:
    void initWidget();

private:
    QString     m_upText;
    QString     m_downText;
    DuiButton   *m_removeButton;
};
#endif // REMOVABLELISTITEM_H
