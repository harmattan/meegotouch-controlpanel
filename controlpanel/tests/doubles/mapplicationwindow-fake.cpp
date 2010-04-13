#include "mapplicationwindow-fake.h"
#include "mapplicationpage.h"
#include "mapplication.h"

/*
 * See header on what this is about.
 */

MApplicationWindow::MApplicationWindow():
    MWindow(),
    m_CurrentPage(0)
{
}

MApplicationPage* MApplicationWindow::currentPage() const
{
    return m_CurrentPage;
}

void MApplicationWindow::setCurrentPage (MApplicationPage* page)
{
    m_CurrentPage = page;
    emit pageChanged(page);
}

void MWindow::raise() {
    m_IsRaised = true;
}

// this hack is to transfer the call to MWindow, because it is
// not a widget really in the tests
void QWidget::raise() {
    if ((void*)this == (void*)MApplication::activeApplicationWindow()) {
        MApplication::activeApplicationWindow()->raise();
    }
}

void MWindow::lower() {
    m_IsRaised = false;
}

bool MWindow::isRaised() {
    return m_IsRaised;
}

