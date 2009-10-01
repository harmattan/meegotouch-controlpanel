#ifndef TA_MKTACLASSNAME_H
#define TA_MKTACLASSNAME_H

#include <mtestapp.h>
#include <mtestpagefactory.h>
#include <QObject>

#include <DcpButton2>


class Ta_DcpButton2 : public  MTestPageFactory {
    Q_OBJECT

    public:
        virtual DuiWidget *addMainContent();
        virtual DuiWidget *addToolbar();

    public slots:
        void toggleText1(bool checked=false);
        void toggleText2(bool checked=false);
        void clicked(bool checked=false);

    private slots:
    
    private:
        DcpButton2* m_subject;
        DuiLabel *m_clickCounterLabel;

        int m_clickCounter;

};


#endif
