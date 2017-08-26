// copyright Curtis Burdette 2017

#include "BuildingEscape.h"
#include "Grabber.h"
//#include "Runtime/Core/Public/Math/Color.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewpointPosition, ViewpointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Position: %s, Rotation: %s"),*ViewpointPosition.ToString(),*ViewpointRotation.ToString());
	FVector testLine = ViewpointPosition + ViewpointRotation.Vector() * reach;
	DrawDebugLine(GetWorld(), ViewpointPosition, testLine, FColor::Red, false, 0.0f, 0.0f, 5.0f);
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewpointPosition, testLine,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	HitActor = Hit.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trace Hit Actor: %s"), *HitActor->GetName());
	}
}

