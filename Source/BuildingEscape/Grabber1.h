// WHYELAB 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h" // 4-44
#include "Grabber1.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber1 : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UGrabber1(); // Class derived from UObject.

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach = 100.0;
	
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr; // Set to nullptr to prevent UNREAL from crashing. And its type must matach with the UGrabber1::BeginPlay() 's PhysicsHandle at part 4-44.
	
	UPROPERTY()
	UInputComponent* InputComponent = nullptr; // Also to prevent crash.
	
	void Grab();
	void Release();
	void FindPhysicsHandle(); 
	void SetupInputComponent();
	
	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetPlayersReach() const;

	FVector GetPlayerWorldPos() const;
};
