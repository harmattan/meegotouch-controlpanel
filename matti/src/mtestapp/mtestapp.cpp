#include "mtestapp.h"
#include "mtestpagefactory.h"
#include <iostream>
#include <DuiWidget>
#include <DuiLinearLayoutPolicy>

#include <iostream>


void MTestApp::debug(QString str) {
    std::cout << str.toAscii().constData() << std::endl;
}


MTestApp::MTestApp(MTestPageFactory *factory, Qt::Orientations direction) 
    :  _layout(0), _f(factory), _direction(direction)
{
}


void MTestApp::createContent() {
    DuiApplicationPage::createContent();
    setObjectName("TestApplicationPage");
    if ( _f ) {
        DuiWidget *w1 =  _f->addMainContent();
        DuiWidget *w2 =  _f->addToolbar();
        if ( w1 && w2 ) {
            qDebug() << "Adding content with toolbar and dividers";
            DuiWidget *panel = new DuiWidget();
            panel->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
            DuiLayout* layout = new DuiLayout(panel);
            if (_direction == Qt::Vertical) {
              DuiLinearLayoutPolicy *lt= new DuiLinearLayoutPolicy(layout, Qt::Vertical);
              DuiWidget *spacer = new DuiWidget();
              spacer->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
              lt->addItem(w1);
              lt->addItem(spacer);
              lt->addItem(w2);
            } else {
              DuiGridLayoutPolicy *lt =  new DuiGridLayoutPolicy(layout);
              lt->setContentsMargins(0,0,0,0);
              lt->addItemAtPosition(w1,0,0);
              lt->addItemAtPosition(w2,0,1);
            }
            setCentralWidget(panel);
        } else if (w1) {
            qDebug() << "Adding content";
            setCentralWidget(w1);
        }
    }
}
MTestApp::~MTestApp() {
	/*
    if (_page) {
        delete _page;
        _page = 0;
    }
	*/
}

DuiGridLayoutPolicy *MTestApp::createLayout(DuiWidget *panel) {
    DuiLayout * layout = new DuiLayout(panel);
    panel->setLayout(layout);
    DuiGridLayoutPolicy * policy = new DuiGridLayoutPolicy(layout);
    policy->setContentsMargins(20, 0, 20, 0); // TODO: Set the correct margins
    return policy;
}

