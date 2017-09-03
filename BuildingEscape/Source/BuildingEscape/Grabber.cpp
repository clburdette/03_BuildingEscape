// copyright Curtis Burdette 2017

#include "BuildingEscape.h"
#include "Grabber.h"


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
	FindPhysicsHandle();
	FindInputComponents();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent)
	{
		SetTestLinePos();
		PhysicsHandle->SetTargetLocation(TestLine);
	}
}

void UGrabber::Grab()
{
	SetFHitResult();
	if (HitResultActor)
	{
		PhysicsHandle->GrabComponent(
			Hit.GetComponent(),
			NAME_None,
			Hit.GetComponent()->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle component missing from: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::FindInputComponents()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found!"));
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component missing from: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetFHitResult()
{
	SetTestLinePos();
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewpointPosition, TestLine,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	HitResultActor = Hit.GetActor();
}

void UGrabber::SetTestLinePos()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewpointPosition, ViewpointRotation);
	TestLine = ViewpointPosition + ViewpointRotation.Vector() * reach;
}

