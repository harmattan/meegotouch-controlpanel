#ifndef LANGUAGELABELBUTTONCONTAINER_H
#define LANGUAGELABELBUTTONCONTAINER_H

#include <DuiWidget>

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
};
#endif // LANGUAGELBELBUTTONCONTAINER_H
