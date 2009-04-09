#ifndef KEYBOARDSELECTCONTAINER_H
#define KEYBOARDSELECTCONTAINER_H

#include <DuiWidget>

class LanguageListItem;

class KeyboardSelectContainer : public DuiWidget
{
    Q_OBJECT

public:
    KeyboardSelectContainer(const QString &title, 
                            QStringList itemList,
                            DuiWidget *parent = 0);
    ~KeyboardSelectContainer();

    void selectItem(const QString &text);

protected:
    void initWidget();

private:
    QString m_titleText;
    QStringList m_itemList;
    QVector<LanguageListItem*> m_listItemVector;

private slots:
    virtual void itemClicked();
};
#endif  // KEYBOARDSELECTCONTAINER_H
