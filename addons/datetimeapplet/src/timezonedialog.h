#ifndef TIMEZONEDIALOG_H
#define TIMEZONEDIALOG_H

#include "dcpcommondialog.h"

class TimeZoneDialog : public DcpCommonDialog
{
    Q_OBJECT

public:
        TimeZoneDialog();
        virtual ~TimeZoneDialog();

protected:
        void initWidget();
};
#endif //TIMEZONEDIALOG_H

