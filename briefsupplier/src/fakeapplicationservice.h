#ifndef FAKEAPPLICATIONSERVICE_H
#define FAKEAPPLICATIONSERVICE_H

#include <MApplicationService>

class FakeApplicationService: public MApplicationService
{
    Q_OBJECT
public:
    FakeApplicationService();

    virtual bool isRegistered ();
    virtual bool registerService ();

private:
	
};


#endif // FAKEAPPLICATIONSERVICE_H
