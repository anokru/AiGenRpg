#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveSubsystem.generated.h"

class URPGSaveGame;

UCLASS()
class AIGENRPG_API USaveSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable)
    URPGSaveGame* CreateNewSave();

    UFUNCTION(BlueprintCallable)
    bool WriteSave(const FString& SlotName, int32 UserIndex);

    UFUNCTION(BlueprintCallable)
    URPGSaveGame* LoadOrCreate(const FString& SlotName, int32 UserIndex);

    UFUNCTION(BlueprintCallable)
    URPGSaveGame* GetCurrentSave() const { return CurrentSave; }

private:
    UPROPERTY()
    URPGSaveGame* CurrentSave = nullptr;
};
