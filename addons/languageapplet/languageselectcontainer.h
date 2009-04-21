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
    QString m_titleText;
    QStringList m_itemList;
    QVector<LanguageListItem*> m_listItemVector;

private slots:
    virtual void itemClicked(LanguageListItem *item);

signals:
    void changeBackToMain();
};
#endif  // LANGUAGESELECTCONTAINER_H
