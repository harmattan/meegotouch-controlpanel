#ifndef LANGUAGESELECTCONTAINER_H
#define LANGUAGESELECTCONTAINER_H

#include <DuiWidget>

class LanguageListItem;

class LanguageSelectContainer : public DuiWidget
{
    Q_OBJECT

public:
    LanguageSelectContainer(const QString &title, 
                            QStringList itemList,
                            DuiWidget *parent = 0);
    ~LanguageSelectContainer();
    void selectItem(const QString &text);

protected:
    void initWidget();

private:
    QString m_TitleText;
    QStringList m_ItemList;
    QVector<LanguageListItem*> m_ListItemVector;

private slots:
    virtual void itemClicked(LanguageListItem *item);

signals:
    void changeBackToMain();
};
#endif  // LANGUAGESELECTCONTAINER_H
