#ifndef KEYBOARDSELECTCONTAINER_H
#define KEYBOARDSELECTCONTAINER_H

#include <DuiWidget>
#include <QMap>
class LanguageListItem;
class DuiLayout;
class DuiGridLayoutPolicy;
class DuiLinearLayoutPolicy;

class KeyboardSelectContainer : public DuiWidget
{
    Q_OBJECT

public:
    KeyboardSelectContainer(const QString &title, 
                            QStringList itemList,
                            DuiWidget *parent = 0);
    virtual ~KeyboardSelectContainer();
    void putLastLanguageBack();

protected:
    void initWidget();

private:
    QString m_TitleText;
    QStringList m_ItemList;
    QMap<QString, LanguageListItem*> m_ListItems;
    QString m_LastRemovedLangCode;
    DuiLayout *m_ItemLayout;
    DuiGridLayoutPolicy *m_LandscapePolicy;
    DuiLinearLayoutPolicy *m_PortraitPolicy;
    
private slots:
    virtual void itemClicked(LanguageListItem *item);
    virtual void onOrientationAngleChange();
};
#endif  // KEYBOARDSELECTCONTAINER_H
