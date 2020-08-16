#pragma once
#include "AssetTypeActions_Base.h"

/*
	新建资源实例的菜单以及资源区域的实例图标
*/

class FCustomAssetActions : public FAssetTypeActions_Base
{
public:
	/*
		必须继承的纯虚函数
	*/
	//实例图标
	virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;

	//对应的资源类型
	virtual UClass* GetSupportedClass() const override;

	//菜单图标颜色
	virtual FColor GetTypeColor() const override;

	//菜单中的显示名称
	virtual FText GetName() const;

	//菜单中的所属目录
	virtual uint32 GetCategories();

	//双击图标时调用，打开编辑器实例
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/) override;
};