#ifndef DCPLANGUAGESELECTCONTAINER_H
#define DCPLANGUAGESELECTCONTAINER_H

#include <DuiWidget>

class LanguageListItem;
class DuiLayout;
class DuiLinearLayoutPolicy;
class DuiGridLayoutPolicy;

class DcpLanguageSelectContainer : public DuiWidget
{
    Q_OBJECT

public:
    typedef enum {
        SingleSelect = 1,
        MultiSelect
    } Type;
    DcpLanguageSelectContainer(DcpLanguageSelectContainer::Type type,
                               DuiWidget *parent = 0);
    virtual ~DcpLanguageSelectContainer();
    QStringList selectedLanguages();

protected:
    void initWidget();
    void initCheckedItems();
    
private:
    DcpLanguageSelectContainer::Type m_Type;
    QMap<QString, LanguageListItem*> m_ItemMap;
    DuiLayout *m_ItemLayout;
    DuiGridLayoutPolicy *m_LandscapePolicy;
    DuiLinearLayoutPolicy *m_PortraitPolicy;

private slots:
    virtual void orientationChanged();
    virtual void itemClicked(LanguageListItem *item);

signals:
    void closing();
};
#endif // DCPLANGUAGESELECTCONTAINER_H
