#include <duiapplicationpage.h>

static QString sTitle;

DuiApplicationPage::DuiApplicationPage(QGraphicsItem *){}
DuiApplicationPage::~DuiApplicationPage(){}
void DuiApplicationPage::createContent(){}

DuiApplicationPageModel::ComponentDisplayMode DuiApplicationPage::componentDisplayMode(Component) const
{
    return DuiApplicationPageModel::Show;
}

void DuiApplicationPage::setComponentsDisplayMode(Components, DuiApplicationPageModel::ComponentDisplayMode){}
bool DuiApplicationPage::autoMarginsForComponentsEnabled() const{ return false; }
bool DuiApplicationPage::isContentCreated() const{ return false; }
bool DuiApplicationPage::rememberPosition() const{ return false; }
bool DuiApplicationPage::isPannable() const{ return false; }
Qt::Orientations DuiApplicationPage::panningDirection() const{ return Qt::Horizontal; }

QGraphicsWidget* DuiApplicationPage::centralWidget(){
    static QGraphicsWidget* widget = 0;
    if (!widget) widget = new QGraphicsWidget();
    return widget;
}

DuiApplicationWindow DuiApplicationPage::*applicationWindow(){ return 0;}
const QString DuiApplicationPage::title() const{ return sTitle; }
bool DuiApplicationPage::isProgressIndicatorVisible() const{ return false; }

DuiApplicationPageModel::PageEscapeMode DuiApplicationPage::escapeMode() const
{
    return DuiApplicationPageModel::EscapeAuto;
}

DuiPannableViewport* DuiApplicationPage::pannableViewport(){
    return 0;
}

void DuiApplicationPage::setAutoMarginsForComponentsEnabled(bool){}
void DuiApplicationPage::setCentralWidget(QGraphicsWidget *){}

void DuiApplicationPage::setTitle(const QString &title){
    sTitle = title;
}

void DuiApplicationPage::setRememberPosition(bool){}
void DuiApplicationPage::setPannable(bool){}
void DuiApplicationPage::setPanningDirection(Qt::Orientations){}
void DuiApplicationPage::setProgressIndicatorVisible(bool){}
void DuiApplicationPage::setEscapeMode(DuiApplicationPageModel::PageEscapeMode){}
void DuiApplicationPage::actionEvent(QActionEvent *){}

