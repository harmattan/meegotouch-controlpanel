#ifndef SPECIALICON_H
#define SPECIALICON_H

#include <DcpWidget>

class SpecialIcon: public DcpWidget
{
    Q_OBJECT

public:
    SpecialIcon();

protected slots:
    void onClick1();
    void onClick2();

private:

};


#endif // SPECIALICON_H
