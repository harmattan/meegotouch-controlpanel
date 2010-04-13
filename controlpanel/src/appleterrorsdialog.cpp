/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "appleterrorsdialog.h"
#include "dcpwrongapplets.h"

#include <QGraphicsLinearLayout>
#include <MLabel>

static const QString 
description = "The following applets were disabled due to crash:";

AppletErrorsDialog::AppletErrorsDialog():
    MDialog ()
{
    // TODO: localization etc.
    setTitle ("Disabled applets"); 

    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout (Qt::Vertical, centralWidget());

    MLabel* descLabel = new MLabel (description);
    descLabel->setWordWrap(true);
    layout->addItem(descLabel);

    const QSet<QString> badApplets = DcpWrongApplets::instance()->badApplets();
    foreach (QString badApplet, badApplets) {
        layout->addItem (new MLabel (badApplet));
    }
}

void 
AppletErrorsDialog::showAppletErrors()
{
    if (!DcpWrongApplets::instance()->badApplets().isEmpty()) {
        (new AppletErrorsDialog)->appear(MSceneWindow::DestroyWhenDone);
    }
}

