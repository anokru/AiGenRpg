// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AIGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AIGENRPG_API UAIGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

};
