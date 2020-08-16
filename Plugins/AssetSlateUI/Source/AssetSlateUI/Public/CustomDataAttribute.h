#pragma once
#include "Widgets/SCompoundWidget.h"

class UCustomAsset;

class SCustomDataAttribute : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomDataAttribute) {}

	SLATE_ATTRIBUTE(UCustomAsset*, CustomAsset)

	SLATE_END_ARGS()

	void Construct(const FArguments &InArgs);

private:
	UCustomAsset * CustomAsset;
	TSharedPtr<IDetailsView> ConfigPanel;
};