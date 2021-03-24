#include "FlowSystemComponent.h"
#include "FlowSubsystem.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"

UFlowSystemComponent::UFlowSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UFlowSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FlowAsset && GetOwnerRole() == ENetRole::ROLE_Authority)
	{
		if (UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
		{
			FlowSubsystem->StartRootFlow(GetWorld(), FlowAsset);
		}
	}
}

void UFlowSystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (FlowAsset && GetOwnerRole() == ENetRole::ROLE_Authority)
	{
		if (UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
		{
			FlowSubsystem->FinishRootFlow(GetWorld(), FlowAsset);
		}
	}

	Super::EndPlay(EndPlayReason);
}
