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
    // Гарантируем создание Subsystem
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override
    {
        return true;
    }

    // Инициализация Subsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Создать новый сейв в памяти
    UFUNCTION(BlueprintCallable)
    URPGSaveGame* CreateNewSave();

    // Сохранить в слот
    UFUNCTION(BlueprintCallable)
    bool WriteSave(const FString& SlotName, int32 UserIndex);

    // Загрузить из слота (или создать новый, если нет)
    UFUNCTION(BlueprintCallable)
    URPGSaveGame* LoadOrCreate(const FString& SlotName, int32 UserIndex);

    // Получить текущий сейв
    UFUNCTION(BlueprintCallable)
    URPGSaveGame* GetCurrentSave() const { return CurrentSave; }

private:
    // Текущий активный сейв
    UPROPERTY()
    URPGSaveGame* CurrentSave = nullptr;
};
