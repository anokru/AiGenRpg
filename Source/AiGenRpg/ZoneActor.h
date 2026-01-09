#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoneActor.generated.h"

class UBoxComponent;
class UPCGComponent;
class ULocationTypeDefinition;

/**
 * ZoneActor — логическая зона мира.
 * Отвечает за:
 *  - идентичность зоны (ZoneId)
 *  - включение / выключение
 *  - детерминированный seed
 *  - тип локации (Forest / Hills / ...)
 *  - PCG-генерацию содержимого
 */
UCLASS()
class AIGENRPG_API AZoneActor : public AActor
{
    GENERATED_BODY()

public:
    AZoneActor();

    /** Уникальный ID зоны (используется для seed, логики, сохранений) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    FName ZoneId = NAME_None;

    /** Можно отключить зону без удаления */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    bool bEnabled = true;

    /**
     * Смещение относительно WorldSeed.
     * INT32_MIN => авто (детерминированно считается из ZoneId)
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    int32 SeedOffset = INT32_MIN;

    /** Тип локации (DataAsset): Forest, Hills, Plains, Swamp, Water... */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<ULocationTypeDefinition> LocationType = nullptr;

    /** Получить PCG-компонент зоны */
    UFUNCTION(BlueprintCallable, Category = "Zone")
    UPCGComponent* GetPCG() const { return PCG; }

    /** Итоговый seed-offset (ручной или авто) */
    UFUNCTION(BlueprintCallable, Category = "Zone")
    int32 GetResolvedSeedOffset() const;

    /** Итоговый ZoneId (если не задан — генерируется стабильно) */
    UFUNCTION(BlueprintCallable, Category = "Zone")
    FName GetResolvedZoneId() const;

protected:
    /** Границы зоны */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<UBoxComponent> Box;

    /** PCG генератор содержимого */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<UPCGComponent> PCG;

private:
    /** Стабильный хеш строки в int32 (для seed) */
    static int32 StableHashToOffset(const FString& S);
};
