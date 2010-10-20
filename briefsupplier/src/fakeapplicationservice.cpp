#include "fakeapplicationservice.h"


FakeApplicationService::FakeApplicationService():
    MApplicationService ("duicontrolpanelhelper")
{
}

bool FakeApplicationService::isRegistered()
{
    return true;
}

bool FakeApplicationService::registerService()
{
    return true;
}

