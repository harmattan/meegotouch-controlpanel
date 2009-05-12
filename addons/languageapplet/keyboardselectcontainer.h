#ifndef KEYBOARDSELECTCONTAINER_H
#define KEYBOARDSELECTCONTAINER_H

#include <DuiWidget>
#include <QMap>
#include <QStringList>
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
    QStringList selectedLanguages();

protected:
    void initWidget();

private:
    QString m_TitleText;
    QStringList m_ItemList;
    QMap<QString, LanguageListItem*> m_ListItems;
    DuiLayout *m_ItemLayout;
    DuiGridLayoutPolicy *m_LandscapePolicy;
    DuiLinearLayoutPolicy *m_PortraitPolicy;

private slots:
    virtual void onOrientationAngleChange();
};
#endif  // KEYBOARDSELECTCONTAINER_H

