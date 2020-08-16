#pragma once
#include "Toolkits/AssetEditorToolkit.h"

/*
	�༭������
*/

class UCustomAsset;

class FCustomAssetEditorToolkit : public FAssetEditorToolkit
{
	typedef FAssetEditorToolkit Super;
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//˫��ͼ��ʱ���еĳ�ʼ��
	void initialize(UCustomAsset *InTextAsset, const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InToolkitHost);

	virtual FName GetToolkitFName() const override;//�༭������
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;//(��������)ѡ�ǰ׺
	virtual FLinearColor GetWorldCentricTabColorScale() const;

private:
	UCustomAsset * CustomTextAsset;
};