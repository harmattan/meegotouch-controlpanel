#include <duiwindow.h>

DuiWindow::DuiWindow(QWidget *): d_ptr(0) {}
DuiWindow::DuiWindow(DuiSceneManager *, QWidget *): d_ptr(0){}
DuiWindow::~DuiWindow(){}
void DuiWindow::setTranslucentBackground(bool){}

DuiScene* DuiWindow::scene()
{
/*    static DuiScene* scene = 0;
    if (!scene) scene = new DuiScene();
    return scene; */
    return 0;
}

void DuiWindow::setSceneManager(DuiSceneManager *){}
DuiSceneManager* DuiWindow::sceneManager() const{ return 0; }
DuiSceneManager* DuiWindow::sceneManager(){ return 0; }
Dui::Orientation DuiWindow::orientation() const{ return Dui::Landscape; }
Dui::OrientationAngle DuiWindow::orientationAngle() const{ return Dui::Angle0; }
QSize DuiWindow::visibleSceneSize(Dui::Orientation) const{ return QSize(800,600);}
QSize DuiWindow::visibleSceneSize() const{ return QSize(800,600); }
bool DuiWindow::isOrientationAngleLocked() const{ return false; }
void DuiWindow::setOrientationAngleLocked(bool){}
bool DuiWindow::isOrientationLocked() const{ return false; }
void DuiWindow::setOrientationLocked(bool){}
bool DuiWindow::isOnDisplay() const{ return true; }
void DuiWindow::setOrientationAngle(Dui::OrientationAngle){}
void DuiWindow::setLandscapeOrientation(){}
void DuiWindow::setPortraitOrientation(){}
void DuiWindow::lockOrientationAngle(){}
void DuiWindow::unlockOrientationAngle(){}
void DuiWindow::lockOrientation(){}
void DuiWindow::unlockOrientation(){}
bool DuiWindow::event(QEvent *){return true;}
void DuiWindow::paintEvent(QPaintEvent *){}
void DuiWindow::onDisplayChangeEvent(DuiOnDisplayChangeEvent *){}
void DuiWindow::enterDisplayEvent(){}
void DuiWindow::exitDisplayEvent(){}
DuiWindow::DuiWindow(DuiWindowPrivate &, QWidget *): d_ptr(0){}
DuiWindow::DuiWindow(DuiWindowPrivate &, DuiScene *, QWidget *): d_ptr(0){}
DuiWindow::DuiWindow(DuiWindowPrivate &, DuiSceneManager *, QWidget *): d_ptr(0){}
void DuiWindow::setVisible(bool){}

