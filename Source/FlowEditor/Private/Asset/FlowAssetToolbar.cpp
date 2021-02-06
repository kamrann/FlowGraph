#include "Asset/FlowAssetToolbar.h"
#include "Asset/FlowAssetEditor.h"
#include "DebuggerCommands.h"
#include "FlowEditorCommands.h"

#include "MultiBoxBuilder.h"

#define LOCTEXT_NAMESPACE "FlowAssetToolbar"

FFlowAssetToolbar::FFlowAssetToolbar(TSharedPtr<FFlowAssetEditor> InNodeEditor)
	: FlowAssetEditor(InNodeEditor)
{
}

void FFlowAssetToolbar::AddToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.BeginSection("FlowAsset");
	{
		ToolbarBuilder.AddToolBarButton(FFlowToolbarCommands::Get().RefreshAsset);
		ToolbarBuilder.AddSeparator();
		
		FPlayWorldCommands::BuildToolbar(ToolbarBuilder, false);
	}
	ToolbarBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE
