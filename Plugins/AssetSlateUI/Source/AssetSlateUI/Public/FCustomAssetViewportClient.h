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
	void OnPropertyChanged();//����ģ��
	bool CreateMeshLOD(int32 LODNumber = 1);
private:
	UCustomAsset* CustomAsset;
	TArray<UProceduralMeshComponent*> ProceduralMesh;//Ԥ�������ģ��component��ÿһ����Ӧһ��LOD
};