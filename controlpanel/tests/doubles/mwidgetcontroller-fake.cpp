#include <MWidgetController>

void MWidgetController::setView(MWidgetView*) {}
MWidgetController::MWidgetController(QGraphicsItem *parent){ QGraphicsItem::setParentItem(parent); }
void MWidgetController::setObjectName (const QString&) {}
MWidgetController::~MWidgetController() {}


