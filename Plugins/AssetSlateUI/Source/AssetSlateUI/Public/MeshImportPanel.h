#pragma once 

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include <string>

// MeshImport在Editor这边的面板映射类(具体的映射工作在模块类中完成)
class FMeshImportDetail : public IPropertyTypeCustomization
{
public:
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

private:
	FReply HandleImportClicked();//点击import时激活的函数

	void OnLabelsRootTextCommited(const FText &InText, ETextCommit::Type InCommitType) const;//路径确认并提交后的响应函数

	void parseCubeFile(const std::string &path);

	TSharedPtr<class SEditableTextBox> EditableTextBox;//路径还原

	TSharedPtr<IPropertyHandle> HandleMeshSavePath; // 访问MeshImport中数据的Handle
};