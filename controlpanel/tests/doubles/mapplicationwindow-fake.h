#ifndef MAPPLICATIONWINDOW_H
#define MAPPLICATIONWINDOW_H

#include <QObject>
#include "./mwindow-fake.h"

/* Fake MApplicationWindow
 *
 * Its purpose is to be able to avoid X usage when running unittests.
 *
 * ! Beware that this class is not a full replacement of M(Application)Window,
 * it works by avoiding to run its baseclass constructor (most specifically
 * QGraphicsView and QWidget), because they do not run without QApplication.
 *
 * How to use it:
 * - add the mapplicationwindow-fake.cpp to your SOURCES.
 * - extend with the functionalities you require :)
 */


class MApplicationPage;

class MApplicationWindow: public MWindow
{
    Q_OBJECT
public:
    MApplicationWindow();

    MApplicationPage* currentPage() const;
    void setCurrentPage(MApplicationPage* currentPage);

signals:
    void pageChanged(MApplicationPage *);

protected:
    MApplicationPage* m_CurrentPage;
};

#endif // MAPPLICATIONWINDOW_H

