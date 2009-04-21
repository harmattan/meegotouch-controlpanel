#ifndef KEYBOARDSELECTCONTAINER_H
#define KEYBOARDSELECTCONTAINER_H

#include <DuiWidget>
#include <QMap>
class LanguageListItem;

class KeyboardSelectContainer : public DuiWidget
{
    Q_OBJECT

public:
    KeyboardSelectContainer(const QString &title, 
                            QStringList itemList,
                            DuiWidget *parent = 0);
    ~KeyboardSelectContainer();

protected:
    void initWidget();

private:
    QString m_titleText;
    QStringList m_itemList;
    QMap<QString, LanguageListItem*> m_listItems;

private slots:
    virtual void itemClicked(LanguageListItem *item);
};
#endif  // KEYBOARDSELECTCONTAINER_H
