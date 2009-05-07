#ifndef LANGUAGESELECTCONTAINER_H
#define LANGUAGESELECTCONTAINER_H

#include <DuiWidget>

class LanguageListItem;
class DuiLayout;
class DuiGridLayoutPolicy;
class DuiLinearLayoutPolicy;

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
    DuiLayout *m_ItemLayout;
    DuiGridLayoutPolicy *m_LandscapePolicy;
    DuiLinearLayoutPolicy *m_PortraitPolicy;

private slots:
    virtual void itemClicked(LanguageListItem *item);
    virtual void onOrientationAngleChange();

signals:
    void changeBackToMain();
};
#endif  // LANGUAGESELECTCONTAINER_H
