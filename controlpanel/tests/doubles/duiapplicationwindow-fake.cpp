#include "duiapplicationwindow-fake.h"
#include "duiapplicationpage.h"
#include "duiapplication.h"

/*
 * See header on what this is about.
 */

DuiApplicationWindow::DuiApplicationWindow():
    DuiWindow(),
    m_CurrentPage(0)
{
}

DuiApplicationPage* DuiApplicationWindow::currentPage() const
{
    return m_CurrentPage;
}

void DuiApplicationWindow::setCurrentPage (DuiApplicationPage* page)
{
    m_CurrentPage = page;
    emit pageChanged(page);
}

void DuiWindow::raise() {
    m_IsRaised = true;
}

// this hack is to transfer the call to DuiWindow, because it is
// not a widget really in the tests
void QWidget::raise() {
    if ((void*)this == (void*)DuiApplication::activeApplicationWindow()) {
        DuiApplication::activeApplicationWindow()->raise();
    }
}

void DuiWindow::lower() {
    m_IsRaised = false;
}

bool DuiWindow::isRaised() {
    return m_IsRaised;
}

