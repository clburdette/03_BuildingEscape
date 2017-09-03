// copyright Curtis Burdette 2017

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	FVector ViewpointPosition = { 0.0f, 0.0f, 0.0f };
	FVector TestLine = { 0.0f, 0.0f, 0.0f };
	FRotator ViewpointRotation;
	FHitResult Hit;
	AActor* HitResultActor = nullptr;
	UPROPERTY(EditAnywhere)
	float reach = 100.0f;
	void FindPhysicsHandle();
	void FindInputComponents();
	void SetFHitResult();
	void SetTestLinePos();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComp = nullptr;
	void Grab();
	void Release();
};
