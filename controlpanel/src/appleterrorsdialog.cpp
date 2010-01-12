/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "appleterrorsdialog.h"
#include "dcpwrongapplets.h"

#include <QGraphicsLinearLayout>
#include <DuiLabel>

static const QString 
description = "The following applets were disabled due to crash:";

AppletErrorsDialog::AppletErrorsDialog():
    DuiDialog ()
{
    // TODO: localization etc.
    setTitle ("Disabled applets"); 

    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout (Qt::Vertical, centralWidget());

    DuiLabel* descLabel = new DuiLabel (description);
    descLabel->setWordWrap(true);
    layout->addItem(descLabel);

    const QSet<QString> badApplets = DcpWrongApplets::instance()->badApplets();
    foreach (QString badApplet, badApplets) {
        layout->addItem (new DuiLabel (badApplet));
    }
}

void 
AppletErrorsDialog::showAppletErrors()
{
    if (!DcpWrongApplets::instance()->badApplets().isEmpty()) {
        (new AppletErrorsDialog)->appear(DuiSceneWindow::DestroyWhenDone);
    }
}

