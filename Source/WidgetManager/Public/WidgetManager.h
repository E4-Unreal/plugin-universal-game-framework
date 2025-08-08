#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FWidgetManagerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
