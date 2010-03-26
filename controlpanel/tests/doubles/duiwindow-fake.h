#ifndef DUIWINDOW_FAKE_H
#define DUIWINDOW_FAKE_H
/*
#include <QMetaType>
#include <QEventLoop>
#include <QTimer>

#include <DuiSceneManager>
#include <DuiSceneWindow>
*/
#include <DuiApplicationPage>
#include <DuiWindow>
/*
#include <DuiNavigationBar>
#include <DuiMessageBox>
#include <DuiOverlay>
#include <DuiNavigationBar>
#include "duidockwidget.h"
#include <DuiScene>
#include "duiscenemanager_p.h"
*/
#include <DuiComponentData>
#include <duiapplicationwindow.h>

// DuiWidgetController stubs
const DuiWidgetView *DuiWidgetController::view() const
{
    return 0;
}

// DuiDeviceProfile stubs
class DuiDeviceProfile
{
public:
    static DuiDeviceProfile *instance();
    QSize resolution() const;
};

DuiDeviceProfile *DuiDeviceProfile::instance()
{
    static DuiDeviceProfile p;
    return &p;
}

QSize DuiDeviceProfile::resolution() const
{
    return QSize(1000, 500);
}

// DuiComponentData stubs
DuiWindow *gActiveWindow = 0;
bool DuiComponentData::softwareRendering()
{
    return true;
}

bool DuiComponentData::fullScreen()
{
    return false;
}

void DuiComponentData::setActiveWindow(DuiWindow *window)
{
    gActiveWindow = window;
}

DuiWindow *DuiComponentData::activeWindow()
{
    return gActiveWindow;
}

DuiApplicationWindow *DuiComponentData::activeApplicationWindow()
{
    return qobject_cast<DuiApplicationWindow *>(gActiveWindow);
}

void DuiComponentData::registerWindow(DuiWindow *window)
{
    if (gActiveWindow == 0)
        setActiveWindow(window);
}

void DuiComponentData::unregisterWindow(DuiWindow *window)
{
    if (gActiveWindow == window)
        setActiveWindow(0);
}

// Avoid creating unnecessary OpenGL stuff
void DuiWindow::setTranslucentBackground(bool enable)
{
    Q_UNUSED(enable);
}

#endif // DUIWINDOW_FAKE_H
