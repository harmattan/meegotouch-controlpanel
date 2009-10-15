#include "dcpbrief.h"
#include <DcpWidgetTypes>


DcpBrief::~DcpBrief()
{
}

int DcpBrief::widgetTypeID() const
{
    return DCPLABEL2;
}

QString DcpBrief::icon() const
{
    return QString();
}

QString DcpBrief::valueText() const
{
    return QString();
}

Qt::Alignment DcpBrief::align() const
{
    return Qt::AlignLeft;
}

bool DcpBrief::toggle() const
{
    return false;
}

QString DcpBrief::image() const
{
    return QString();
}

void DcpBrief::setToggle (bool) {}

