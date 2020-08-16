#pragma once

#include "CoreMinimal.h"
#include "MeshImport.generated.h"

USTRUCT(BlueprintType)//可通过蓝图直接创建
struct FMeshImport
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "MeshSavePath")
	FText MeshSavePath;
};