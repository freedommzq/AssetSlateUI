#pragma once

#include "CoreMinimal.h"
#include "MeshImport.generated.h"

USTRUCT(BlueprintType)//��ͨ����ͼֱ�Ӵ���
struct FMeshImport
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "MeshSavePath")
	FText MeshSavePath;
};