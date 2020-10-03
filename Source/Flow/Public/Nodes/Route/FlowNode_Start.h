#pragma once

#include "Nodes/FlowNode.h"
#include "FlowNode_Start.generated.h"

/**
 * Start
 */
UCLASS(NotBlueprintable, NotPlaceable, meta = (DisplayName = "Start"))
class FLOW_API UFlowNode_Start : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;
};
