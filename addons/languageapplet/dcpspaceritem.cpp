#include "dcpspaceritem.h"

DcpSpacerItem::DcpSpacerItem(DuiWidget *parent, 
                             int width, int height,
                             QSizePolicy::Policy hPolicy,
                             QSizePolicy::Policy vPolicy)
              :DuiWidget(parent)
{
    setSizePolicy(hPolicy, vPolicy);
    setMinimumHeight(height);
    setMinimumWidth(width);
    
    if (hPolicy == QSizePolicy::Maximum || 
        hPolicy == QSizePolicy::Fixed)
    {
        setMaximumWidth(width);
    }

    if (vPolicy == QSizePolicy::Maximum ||
        vPolicy == QSizePolicy::Fixed)
    {
        setMaximumHeight(height);
    }
}

DcpSpacerItem::~DcpSpacerItem()
{
}

void DcpSpacerItem::changeSize(int width, int height,
                               QSizePolicy::Policy hPolicy,
                               QSizePolicy::Policy vPolicy)
{
    setMinimumHeight(height);
    setMaximumHeight(height);
    setMinimumWidth(width);
    setMaximumWidth(width);
    setSizePolicy(hPolicy, vPolicy);
}
