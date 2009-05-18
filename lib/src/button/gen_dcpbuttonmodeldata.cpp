#include "dcpbuttonmodel.h"
#include "gen_dcpbuttonmodeldata.h"


DcpButtonModel::DcpButtonModel() :
    DuiWidgetModel(),
    data(new DcpButtonModelData)
{
}

DcpButtonModel::~DcpButtonModel()
{
    delete data;
}

DcpButtonModel::DcpButtonModel(DcpButtonModelData* data) :
    DuiWidgetModel(),
    data(data)
{
}

