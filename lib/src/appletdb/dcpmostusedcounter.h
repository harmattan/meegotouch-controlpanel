/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef MOSTUSEDCOUNTER_H
#define MOSTUSEDCOUNTER_H

#include <DuiGConfItem>

#include <QString>
#include <QMap>

class MostUsedCounter 
{
    public:
		~MostUsedCounter();

        static MostUsedCounter *instance ();
        static void destroy ();
        int add (const QString &name);
        int get (const QString &name);
        void clear (const QString &name);
	
    private:
        MostUsedCounter ();
        static MostUsedCounter *sm_Instance;
        QMap<QString, DuiGConfItem*> m_Data;
};
#endif // MOSTUSEDCOUNTER_H

