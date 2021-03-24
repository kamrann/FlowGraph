#pragma once

#include "Components/ActorComponent.h"
#include "FlowSystemComponent.generated.h"

/**
* Component used to initialize the flow system in a world.
* Must be added to the world settings actor.
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class FLOW_API UFlowSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFlowSystemComponent();

	UFlowAsset* GetFlowAsset() const
	{
		return FlowAsset;
	}

	void SetFlowAsset(UFlowAsset* Asset)
	{
		FlowAsset = Asset;
	}

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Flow")
	class UFlowAsset* FlowAsset;
};
