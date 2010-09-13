#ifndef DCPCONTENTITEMCELLCREATOR_H
#define DCPCONTENTITEMCELLCREATOR_H

#include <MAbstractCellCreator>
#include <DcpContentItem>

class DcpContentItemCellCreator: public MAbstractCellCreator<DcpContentItem>
{
public:
    enum DataRole {
        MetadataRole = Qt::UserRole + 1,
        AppletRole,
        MattiRole
    };

    virtual MWidget * createCell (const QModelIndex &index,
                                  MWidgetRecycler &recycler) const;
    virtual void updateCell(const QModelIndex& index, MWidget * cell) const;

private:
	
};

Q_DECLARE_METATYPE (DcpAppletMetadata*)
Q_DECLARE_METATYPE (DcpAppletObject*)


#endif // DCPCONTENTITEMCELLCREATOR_H
