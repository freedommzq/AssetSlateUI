#pragma once
#include "SEditorViewport.h"

class UCustomAsset;

class SCustomAssetViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SCustomAssetViewport){}

	SLATE_ATTRIBUTE(UCustomAsset*, CustomAsset)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments &InArgs);

	~SCustomAssetViewport();

	//返回相应的client
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	UCustomAsset* CustomAsset;
	TSharedPtr<class FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<class FCustomAssetViewportClient> EditorViewportClient;
};