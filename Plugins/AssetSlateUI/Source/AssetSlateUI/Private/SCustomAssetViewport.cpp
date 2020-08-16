#include "SCustomAssetViewport.h"
#include "FCustomAssetViewportClient.h"
#include "AdvancedPreviewScene.h"

#include "Components/SkyLightComponent.h"
#include "Atmosphere/AtmosphericFogComponent.h"
#include "Components/DirectionalLightComponent.h"

void SCustomAssetViewport::Construct(const FArguments & InArgs)
{
	//���մ���ʱ���ݵĲ���
	CustomAsset = InArgs._CustomAsset.Get();	


	//���ó���
	{
		FAdvancedPreviewScene::ConstructionValues ViewConstructionValues;
		ViewConstructionValues.bCreatePhysicsScene = false;
		ViewConstructionValues.LightBrightness = 3;
		ViewConstructionValues.SkyBrightness = 1;

		PreviewScene = MakeShareable(new FAdvancedPreviewScene(ViewConstructionValues));
		PreviewScene->SetFloorVisibility(false);
		PreviewScene->SetFloorOffset(-100000);
	}

	USkyLightComponent *SkyLight = NewObject<USkyLightComponent>();
	PreviewScene->AddComponent(SkyLight, FTransform::Identity);

	UAtmosphericFogComponent *AtmosphericFog = NewObject<UAtmosphericFogComponent>();
	PreviewScene->AddComponent(AtmosphericFog, FTransform::Identity);

	PreviewScene->DirectionalLight->SetMobility(EComponentMobility::Movable);
	PreviewScene->DirectionalLight->CastShadows = true;
	PreviewScene->DirectionalLight->CastStaticShadows = true;
	PreviewScene->DirectionalLight->CastDynamicShadows = true;
	PreviewScene->DirectionalLight->SetIntensity(3);
	
	SEditorViewport::Construct(SEditorViewport::FArguments());	
}

SCustomAssetViewport::~SCustomAssetViewport()
{
	if (EditorViewportClient.IsValid())
	{
		EditorViewportClient->Viewport = NULL; // ��ֹҰָ����֣��������ӿ����ڲ����Զ�����
	}
}

TSharedRef<FEditorViewportClient> SCustomAssetViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable(new FCustomAssetViewportClient(*PreviewScene, CustomAsset));
	return EditorViewportClient.ToSharedRef();
}