#ifndef LANGUAGEBRIEF_H
#define LANGUAGEBRIEF_H

#include "dcpbrief.h"

class LanguageBrief: public DcpBrief{
    Q_OBJECT
public:
    virtual QString valueText() const;

};


#endif // LANGUAGEBRIEF_H
