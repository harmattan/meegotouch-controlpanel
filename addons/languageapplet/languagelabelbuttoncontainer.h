#ifndef LANGUAGELABELBUTTONCONTAINER_H
#define LANGUAGELABELBUTTONCONTAINER_H

#include <DuiWidget>

class DuiLayout;

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
    ~LanguageLabelButtonContainer();
    
protected:
    void initWidget();

private:
    LanguageLabelButtonContainer::Type m_type;
    DuiLayout *m_mainLayout;

private slots:
    virtual void deleteItem(int id);
};
#endif // LANGUAGELBELBUTTONCONTAINER_H
