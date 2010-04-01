#include <duiapplicationwindow.h>

DuiApplicationWindow::DuiApplicationWindow(QWidget *){}
DuiApplicationWindow::DuiApplicationWindow(DuiScene *, QWidget *){}
DuiApplicationWindow::~DuiApplicationWindow(){}
DuiApplicationPage* DuiApplicationWindow::currentPage() const{ return 0; }

QString DuiApplicationWindow::windowIconID() const{ return QString(); }
DuiTheme::ViewType DuiApplicationWindow::toolbarViewType() const{ return QString(); }
bool DuiApplicationWindow::isMenuOpen() const{ return false; }
void DuiApplicationWindow::openMenu(){}
void DuiApplicationWindow::closeMenu(){}
void DuiApplicationWindow::setWindowIconID(const QString &){}
void DuiApplicationWindow::setToolbarViewType(const DuiTheme::ViewType&){}
DuiApplicationWindow::DuiApplicationWindow(DuiApplicationWindowPrivate &, QWidget *){}
DuiApplicationWindow::DuiApplicationWindow(DuiApplicationWindowPrivate &, DuiScene *, QWidget *){}
bool DuiApplicationWindow::event(QEvent *){return true;}
void DuiApplicationWindow::closeEvent(QCloseEvent *){}
void DuiApplicationWindow::mousePressEvent(QMouseEvent *){}
void DuiApplicationWindow::mouseReleaseEvent(QMouseEvent *){}

