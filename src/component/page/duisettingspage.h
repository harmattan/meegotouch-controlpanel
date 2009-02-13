#ifndef DUISETTINGSPAGE_H
#define DUISETTINGSPAGE_H

#include <DuiApplicationPage>

class DuiSettingsPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DuiSettingsPage();

    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);

protected slots:
    void onSizeChanged(const QSizeF & size1, const QSizeF & size2);

private:
    class DuiMainCategory* m_Category;
    class DuiPannableViewport* m_DesktopViewport;
};

#endif // DUISETTINGSPAGE_H
