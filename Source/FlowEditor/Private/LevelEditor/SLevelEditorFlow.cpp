#include "LevelEditor/SLevelEditorFlow.h"
#include "FlowAsset.h"
#include "FlowSystemComponent.h"

#include "Engine/World.h"
#include "GameFramework/WorldSettings.h"
#include "Editor.h"
#include "Framework/MultiBox/MultiBoxDefs.h"
#include "PropertyCustomizationHelpers.h"
#include "SLevelOfDetailBranchNode.h"

#define LOCTEXT_NAMESPACE "SLevelEditorFlow"

void SLevelEditorFlow::Construct(const FArguments& InArgs)
{
	CreateFlowWidget();
	FEditorDelegates::OnMapOpened.AddRaw(this, &SLevelEditorFlow::OnMapOpened);
}

void SLevelEditorFlow::OnMapOpened(const FString& Filename, bool bAsTemplate)
{
	CreateFlowWidget();
}

void SLevelEditorFlow::CreateFlowWidget()
{
	if (UWorld* World = GEditor->GetEditorWorldContext().World())
	{
		if (const auto FlowSystemComponent = World->GetWorldSettings()->FindComponentByClass< UFlowSystemComponent >())
		{
			FlowPath = FlowSystemComponent->GetFlowAsset() ? FName(*FlowSystemComponent->GetFlowAsset()->GetPathName()) : FName();
		}
	}

	const TSharedRef<SWidget> FlowWidget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SObjectPropertyEntryBox)
					.AllowedClass(UFlowAsset::StaticClass())
					.DisplayThumbnail(false)
					.OnObjectChanged(this, &SLevelEditorFlow::OnFlowChanged)
					.ObjectPath(this, &SLevelEditorFlow::GetFlowPath)
			];

	ChildSlot
	[
		SNew(SLevelOfDetailBranchNode)
			.UseLowDetailSlot(FMultiBoxSettings::UseSmallToolBarIcons)
			.LowDetail()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						FlowWidget
					]
			]
			.HighDetail()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
					.AutoHeight()
					.VAlign(VAlign_Top)
					.Padding(5.0f)
					[
						FlowWidget
					]
			]
	];
}

void SLevelEditorFlow::OnFlowChanged(const FAssetData& NewAsset)
{
	FlowPath = NewAsset.ObjectPath;

	if (UWorld* World = GEditor->GetEditorWorldContext().World())
	{
		const auto WorldSettings = World->GetWorldSettings();
		if (const auto FlowSystemComponent = WorldSettings->FindComponentByClass< UFlowSystemComponent >())
		{
			FlowSystemComponent->SetFlowAsset(Cast<UFlowAsset>(NewAsset.GetAsset()));
			WorldSettings->MarkPackageDirty();
		}
	}
}

FString SLevelEditorFlow::GetFlowPath() const
{
	return FlowPath.IsValid() ? FlowPath.ToString() : FString();
}

#undef LOCTEXT_NAMESPACE
