/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef MOSTUSEDCOUNTER_H
#define MOSTUSEDCOUNTER_H

#include <QString>
class MostUsedCounterPrivate;

class MostUsedCounter
{
public:
    ~MostUsedCounter();

    static MostUsedCounter *instance ();
    static void destroy ();

    int incrementUsageCount (const QString &name);
    int getUsageCount (const QString &key);
    void dropKey (const QString &key);

protected:
    MostUsedCounter ();
private:
    MostUsedCounterPrivate *const d_ptr;
    Q_DISABLE_COPY(MostUsedCounter);
};
#endif

