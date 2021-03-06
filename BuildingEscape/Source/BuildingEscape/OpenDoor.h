// copyright Curtis Burdette 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;
	AActor* openerActor;
	AActor* Owner = GetOwner();
	UPROPERTY(VisibleAnywhere)
	float OpenValue = 75.0f;
	UPROPERTY(VisibleAnywhere)
	float ClosedValue = 0.0f;
	float yvalue = 0.0f;
	bool open = false;
	bool closed = true;

		
	
};
