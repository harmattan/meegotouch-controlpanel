#include <mapplicationpage.h>

#include "mapplicationwindow-fake.h"
#include <mapplication.h>
#include <mscenewindow.h>
#include <QGraphicsLinearLayout>
#include <MLayout>
static QString sTitle;

MApplicationPage::MApplicationPage(QGraphicsItem *){}
MApplicationPage::~MApplicationPage(){}
void MApplicationPage::createContent(){
    setLayout(new MLayout(this));
}

MApplicationPageModel::ComponentDisplayMode MApplicationPage::componentDisplayMode(Component) const
{
    return MApplicationPageModel::Show;
}

void MApplicationPage::setComponentsDisplayMode(Components, MApplicationPageModel::ComponentDisplayMode){}
bool MApplicationPage::autoMarginsForComponentsEnabled() const{ return false; }
bool MApplicationPage::isContentCreated() const{ return true; }
bool MApplicationPage::rememberPosition() const{ return false; }
bool MApplicationPage::isPannable() const{ return false; }
Qt::Orientations MApplicationPage::panningDirection() const{ return Qt::Horizontal; }

QGraphicsWidget* MApplicationPage::centralWidget(){
    static QGraphicsWidget* widget = 0;
    if (!widget) widget = new QGraphicsWidget();
    return widget;
}

MApplicationWindow MApplicationPage::*applicationWindow(){ return 0;}
const QString MApplicationPage::title() const{ return sTitle; }
bool MApplicationPage::isProgressIndicatorVisible() const{ return false; }

MApplicationPageModel::PageEscapeMode MApplicationPage::escapeMode() const
{
    return MApplicationPageModel::EscapeAuto;
}

MPannableViewport* MApplicationPage::pannableViewport(){
    return 0;
}

void MApplicationPage::setAutoMarginsForComponentsEnabled(bool){}
void MApplicationPage::setCentralWidget(QGraphicsWidget *){}

void MApplicationPage::setTitle(const QString &title){
    sTitle = title;
}

void MApplicationPage::setRememberPosition(bool){}
void MApplicationPage::setPannable(bool){}
void MApplicationPage::setPanningDirection(Qt::Orientations){}
void MApplicationPage::setProgressIndicatorVisible(bool){}
void MApplicationPage::setEscapeMode(MApplicationPageModel::PageEscapeMode){}
void MApplicationPage::actionEvent(QActionEvent *){}

void MSceneWindow::appear (MWindow *, MSceneWindow::DeletionPolicy)
{
    this->appear();
    emit appeared();
}

void MSceneWindow::appear (MSceneWindow::DeletionPolicy)
{
    MApplication::activeApplicationWindow()->setCurrentPage((MApplicationPage*)this);
    emit appeared();
}

