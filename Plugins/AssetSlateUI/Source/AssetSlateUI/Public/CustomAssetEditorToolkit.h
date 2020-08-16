#pragma once
#include "Toolkits/AssetEditorToolkit.h"

/*
	编辑器窗口
*/

class UCustomAsset;

class FCustomAssetEditorToolkit : public FAssetEditorToolkit
{
	typedef FAssetEditorToolkit Super;
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//双击图标时进行的初始化
	void initialize(UCustomAsset *InTextAsset, const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InToolkitHost);

	virtual FName GetToolkitFName() const override;//编辑器名字
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;//(世界中心)选项卡前缀
	virtual FLinearColor GetWorldCentricTabColorScale() const;

private:
	UCustomAsset * CustomTextAsset;
};