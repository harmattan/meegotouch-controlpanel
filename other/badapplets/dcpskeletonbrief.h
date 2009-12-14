#ifndef SKELETONBRIEF_H
#define SKELETONBRIEF_H

#include <DcpBrief>

class SkeletonBrief: public DcpBrief{
    Q_OBJECT
public:
    SkeletonBrief();
    virtual QString valueText() const;

    virtual bool toggle() const;
    virtual void setToggle (bool toggle);
    virtual int widgetTypeID() const;

private:
    bool m_ToggleState;
};


#endif // SKELETONBRIEF
