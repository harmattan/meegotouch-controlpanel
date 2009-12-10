#include "appleterrorsdialog.h"
#include "dcpwrongapplets.h"

#include <QGraphicsLinearLayout>
#include <DuiLabel>

static const QString description =
    "The following applets were disabled due to crash:";

AppletErrorsDialog::AppletErrorsDialog():
    DuiDialog()
{
    setTitle ("Disabled applets"); // TODO: localization etc.

    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout(Qt::Vertical, centralWidget());
    DuiLabel* descLabel = new DuiLabel (description);
    descLabel->setWordWrap(true);
    layout->addItem(descLabel);

    const QSet<QString> badApplets = DcpWrongApplets::instance()->badApplets();
    foreach (QString badApplet, badApplets) {
        layout->addItem(new DuiLabel (badApplet));
    }
}

void AppletErrorsDialog::showAppletErrors()
{
    if (!DcpWrongApplets::instance()->badApplets().isEmpty()) {
        (new AppletErrorsDialog)->appear(DuiSceneWindow::DestroyWhenDone);
    }
}

