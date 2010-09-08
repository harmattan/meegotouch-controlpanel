#include "dcpcontentitemcellcreator.h"

QSizeF QGraphicsLayoutItem::effectiveSizeHint ( Qt::SizeHint,
                                                const QSizeF & ) const
{ return QSizeF (100, 100); }

MWidget* DcpContentItemCellCreator::createCell (const QModelIndex &,
                                                MWidgetRecycler &) const
{
    return 0;
}

void DcpContentItemCellCreator::updateCell(const QModelIndex&, MWidget*) const
{}

