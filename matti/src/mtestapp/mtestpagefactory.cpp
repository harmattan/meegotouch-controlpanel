#include "mtestpagefactory.h"

DuiWidget *MTestPageFactory::addMainContent() {
//  qDebug() << "WARNING: Virtual implementation of addMainContent()";
    return NULL;
}

DuiWidget *MTestPageFactory::addToolbar() {
//  qDebug() << "WARNING: Virtual implementation of addToolbar()";
    return NULL;
}


DuiButton *MTestPageFactory::createToolbarButton(QString text, bool checkable ) {
    static int counter = 0;
    DuiButton *b = NULL;
    b = new DuiButton();
    if (b != NULL && b != 0) {
        b->setObjectName(QString("ToolBarbutton") + QString::number(counter));
        b->setText(text);
        b->setCheckable(checkable);
		counter ++;
    } 
    return b;
}
