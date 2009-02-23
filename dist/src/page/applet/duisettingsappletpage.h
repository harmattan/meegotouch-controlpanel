#ifndef DUISETTINGSAPPLETPAGE_H
#define DUISETTINGSAPPLETPAGE_H

#include "duisettingspage.h" 
#include "pages.h"

class DuiSettingsAppletPage : public DuiSettingsPage
{
    Q_OBJECT
public:
    DuiSettingsAppletPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    void init(const QString &appletBinary, const QString &appletMetaData,
              const QString &appletId);
};

#endif // DUISETTINGSAPPLETPAGE_H
