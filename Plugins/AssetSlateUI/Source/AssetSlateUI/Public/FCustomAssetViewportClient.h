#pragma once
#include "EditorViewportClient.h"
#include "PreviewScene.h"

class UCustomAsset;
class UProceduralMeshComponent;

class FCustomAssetViewportClient : public FEditorViewportClient, public TSharedFromThis<FCustomAssetViewportClient>
{
public:
	FCustomAssetViewportClient(FPreviewScene &InPreviewScene, UCustomAsset* NewCustomAsset, const TWeakPtr<class SEditorViewport> &InEditorViewportWidget = nullptr);
	virtual void Tick(float DeltaSeconds) override;
	void OnPropertyChanged();//创建模型
	bool CreateMeshLOD(int32 LODNumber = 1);
private:
	UCustomAsset* CustomAsset;
	TArray<UProceduralMeshComponent*> ProceduralMesh;//预览用组件模型component，每一个对应一级LOD
};