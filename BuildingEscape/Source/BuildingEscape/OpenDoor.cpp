// copyright Curtis Burdette 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	openerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (pressurePlate->IsOverlappingActor(openerActor) && !open)
	{
		OpenDoor();
	}
	else if (!pressurePlate->IsOverlappingActor(openerActor) && !closed)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	yvalue++;
	Owner->SetActorRotation(FRotator(0.0f, yvalue, 0.0f));
	if (yvalue >= OpenValue)
	{
		open = true;
	}
	if (yvalue > ClosedValue)
	{
		closed = false;
	}
}
void UOpenDoor::CloseDoor()
{
	yvalue--;
	Owner->SetActorRotation(FRotator(0.0f, yvalue, 0.0f));
	if (yvalue < OpenValue)
	{
		open = false;
	}
	if (yvalue <= ClosedValue)
	{
		closed = true;
	}
}
