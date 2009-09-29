#ifndef TA_MKTACLASSNAME_H
#define TA_MKTACLASSNAME_H

#include <mtestapp.h>
#include <mtestpagefactory.h>
#include <QObject>

#include <mktaclassname.h>


class Ta_MkTaClassName : public  MTestPageFactory {
    Q_OBJECT

    public:
        virtual DuiWidget *addMainContent();
        virtual DuiWidget *addToolbar();

    public slots:
    private slots:
    
    private:
        MkTaClassName* m_subject;

};


#endif
