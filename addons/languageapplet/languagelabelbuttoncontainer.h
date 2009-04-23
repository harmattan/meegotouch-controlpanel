#ifndef LANGUAGELABELBUTTONCONTAINER_H
#define LANGUAGELABELBUTTONCONTAINER_H

#include <DuiWidget>

class DuiLayout;
class RemovableListItem;

class LanguageLabelButtonContainer : public DuiWidget
{
    Q_OBJECT

public:
    enum Type {
            DOWNLOADED = 1,
            INSTALLED
    };

    LanguageLabelButtonContainer(LanguageLabelButtonContainer::Type type,
                                DuiWidget *parent = 0);
    virtual ~LanguageLabelButtonContainer();
    
protected:
    void initWidget();

private:
    LanguageLabelButtonContainer::Type  m_type;
    DuiLayout                           *m_mainLayout;
    QVector<RemovableListItem*>         m_itemVector;

private slots:
    virtual void deleteItem(RemovableListItem *item);

signals:
    void removeMe(LanguageLabelButtonContainer*);
};
#endif // LANGUAGELBELBUTTONCONTAINER_H
