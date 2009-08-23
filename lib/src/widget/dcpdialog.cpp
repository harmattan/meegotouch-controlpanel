#include "dcpdialog.h"

#include <duiscenemanager.h>
#include <duiscene.h>
#include <QEventLoop>

DcpDialog::DcpDialog(DuiWidget* parent) : DuiWidget(parent), m_Loop(0)
{
}

DcpDialog::~DcpDialog()
{}

void
DcpDialog::done (int result)
{
    m_Loop->exit(result);
}

int
DcpDialog::exec()
{
    Q_ASSERT(!m_Loop);
    connect (DuiSceneManager::instance(),
             SIGNAL(orientationChanged (const Dui::Orientation &)),
             this, SLOT(onOrientationChanged()));
    m_Loop = new QEventLoop(this);
    onOrientationChange();
    if (scene() == 0) {
        setZValue(1001);
        DuiSceneManager::instance()->scene()->addItem(this);
    }
    this->show();
    int result = m_Loop->exec();
    this->hide();
    disconnect (DuiSceneManager::instance(),
             SIGNAL(orientationChanged (const Dui::Orientation &)),
             this, SLOT(onOrientationChanged()));
    m_Loop->deleteLater();
    m_Loop = 0;
    return result;
}


void
DcpDialog::onOrientationChange()
{
    if (DuiSceneManager::instance() == 0) return;
    this->resize(DuiSceneManager::instance()->visibleSceneSize());
/*
    QSizeF dialogSize = DuiSceneManager::instance()->visibleSceneSize();
    m_Viewport->setMinimumSize(dialogSize);
    m_Viewport->setPreferredSize(dialogSize);
    m_Viewport->setMaximumSize(dialogSize);
    */
}

