// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	// 4-5
	//-------------------------------------------------------
	Super::BeginPlay(); // 4-5
	//-------------------------------------------------------
	
	// 4-8
	//-------------------------------------------------------
	// UE_LOG(LogTemp, Warning, TEXT("Your MUM")); // 4-8
	//-------------------------------------------------------

	// 4-10
	//-------------------------------------------------------
	// FString Log = TEXT("Hello!");
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);
	//-------------------------------------------------------

	//-------------------------------------------------------
	// FString Log = TEXT("Hello!"); 
	// FString* PrtLog = &Log;

	// Log.Len();

	// (*PrtLog).Len(); // Accessing the member's when it comes to pointer. The reason why you need to put brackets is because * has lower precedence than . which means that . is evaluated first which means nothing. So need brackets. 
	// PrtLog->Len(); // Easier way to access member's len().

	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PrtLog); // Need a double ** here because you will be dereferencing and the other * will act as a overloading operator. Using no * operators you are just reading memory address which contain PrtLog. Using one * also won't work. 
	//-------------------------------------------------------
	// FString ObjectName = GetOwner()->GetName(); // Get Name is returning FString.
	// UE_LOG(LogTemp, Warning, TEXT("Object name is: %s"), *ObjectName);
	//-------------------------------------------------------

	// The code below is the same as the top one. 
	//-------------------------------------------------------
	// UE_LOG(LogTemp, Warning, TEXT("Object name is: %s"), *GetOwner()->GetName()); 
	//-------------------------------------------------------

	// 4-11
	// Verify that it is correct yourself!
	//-------------------------------------------------------
	// FString ObjectName = GetOwner()->GetName(); 
	// FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s postion in world is: %s"), *ObjectName, *ObjectPosition);
	//-------------------------------------------------------

	//-------------------------------------------------------
	// FString ObjectName = GetOwner()->GetName();
	// FString ObjectPosition1 = GetOwner()->GetActorTransform().ToString();
	// FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s postion in world is: %s"), *ObjectName, *ObjectPosition);
	// UE_LOG(LogTemp, Warning, TEXT("%s postion in world is: %s"), *ObjectName, *ObjectPosition1);
	//-------------------------------------------------------
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	// 4-5
	//-------------------------------------------------------
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//-------------------------------------------------------

}

