#ifndef DUIAPPLICATIONWINDOW_H
#define DUIAPPLICATIONWINDOW_H

#include <QObject>
#include "./duiwindow-fake.h"

/* Fake DuiApplicationWindow
 *
 * Its purpose is to be able to avoid X usage when running unittests.
 *
 * ! Beware that this class is not a full replacement of Dui(Application)Window,
 * it works by avoiding to run its baseclass constructor (most specifically
 * QGraphicsView and QWidget), because they do not run without QApplication.
 *
 * How to use it:
 * - add the duiapplicationwindow-fake.cpp to your SOURCES.
 * - extend with the functionalities you require :)
 */


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

