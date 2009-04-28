#ifndef LANGUAGELABELBUTTONCONTAINER_H
#define LANGUAGELABELBUTTONCONTAINER_H

#include <DuiWidget>

class DuiLayout;
class RemovableListItem;

class LanguageLabelButtonContainer : public DuiWidget
{
    Q_OBJECT

public:
    typedef enum {
            DOWNLOADED = 1,
            INSTALLED
    } Type;
    LanguageLabelButtonContainer(LanguageLabelButtonContainer::Type type,
                                 DuiWidget *parent = 0);
    virtual ~LanguageLabelButtonContainer();
    
protected:
    void initWidget();

private:
    LanguageLabelButtonContainer::Type m_Type;
    DuiLayout *m_MainLayout;
    QVector<RemovableListItem*> m_ItemVector;

private slots:
    virtual void deleteItem(RemovableListItem *item);

signals:
    void removeMe(LanguageLabelButtonContainer*);
};
#endif // LANGUAGELBELBUTTONCONTAINER_H
