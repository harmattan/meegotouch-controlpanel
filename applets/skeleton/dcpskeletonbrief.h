#ifndef SKELETONBRIEF_H
#define SKELETONBRIEF_H

#include <DcpBrief>

class SkeletonBrief: public DcpBrief{
    Q_OBJECT
public:
    virtual QString valueText() const;

};


#endif // SKELETONBRIEF
