#ifndef DISPLAYBRIEF_H
#define DISPLAYBRIEF_H

#include <DcpBrief>

class DisplayBrief: public DcpBrief{
    Q_OBJECT
public:
    virtual QString valueText() const;

};


#endif // DISPLAYBRIEF
