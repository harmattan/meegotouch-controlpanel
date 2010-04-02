#ifndef DUIAPPLICATIONWINDOW_H
#define DUIAPPLICATIONWINDOW_H

#include <QObject>
#include "./duiwindow-fake.h"

class DuiApplicationPage;

class DuiApplicationWindow: public DuiWindow
{
    Q_OBJECT
public:
    DuiApplicationWindow();

    DuiApplicationPage* currentPage() const;
    void setCurrentPage(DuiApplicationPage* currentPage);

signals:
    void pageChanged(DuiApplicationPage *);

protected:
    DuiApplicationPage* m_CurrentPage;
};

#endif // DUIAPPLICATIONWINDOW_H

