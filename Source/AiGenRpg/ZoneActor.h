#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoneActor.generated.h"

class UBoxComponent;
class UPCGComponent;
class ULocationTypeDefinition;

UCLASS()
class AIGENRPG_API AZoneActor : public AActor
{
    GENERATED_BODY()

public:
    AZoneActor();

    // Уникальный ID зоны (для логов/детерминизма/будущих систем)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    FName ZoneId = "Zone";

    // Можно отключать зону без удаления
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    bool bEnabled = true;

    // Смещение относительно WorldSeed.
    // INT32_MIN = авто-расчёт по ZoneId (детерминированно)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    int32 SeedOffset = INT32_MIN;

    // Тип локации (лес/холмы/поле/вода/болото) — масштабируемо через DataAsset
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<ULocationTypeDefinition> LocationType;

    UFUNCTION(BlueprintCallable, Category = "Zone")
    UPCGComponent* GetPCG() const;

    UFUNCTION(BlueprintCallable, Category = "Zone")
    int32 GetResolvedSeedOffset() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UBoxComponent> Box;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UPCGComponent> PCG;

private:
    static int32 StableHashToOffset(const FString& S);
};
