// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CustomFactory.generated.h"

/**
 * 
 */
UCLASS()
class /*ASSETSLATEUI_API*/ UCustomFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCustomFactory();

	//创建自定义数据类型
	virtual UObject * FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags Flags, UObject * Context, FFeedbackContext * Warn, FName CallingContext) override;
};
