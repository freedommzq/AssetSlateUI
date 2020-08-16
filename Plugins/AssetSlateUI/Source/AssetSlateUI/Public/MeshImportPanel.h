#pragma once 

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include <string>

// MeshImport��Editor��ߵ����ӳ����(�����ӳ�乤����ģ���������)
class FMeshImportDetail : public IPropertyTypeCustomization
{
public:
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

private:
	FReply HandleImportClicked();//���importʱ����ĺ���

	void OnLabelsRootTextCommited(const FText &InText, ETextCommit::Type InCommitType) const;//·��ȷ�ϲ��ύ�����Ӧ����

	void parseCubeFile(const std::string &path);

	TSharedPtr<class SEditableTextBox> EditableTextBox;//·����ԭ

	TSharedPtr<IPropertyHandle> HandleMeshSavePath; // ����MeshImport�����ݵ�Handle
};