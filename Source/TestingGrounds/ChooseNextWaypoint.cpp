// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "TP_ThirdPerson/PatrollingGuard.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Patrol Patrol Route Component
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIOwner->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }
	
	// Get Patrol Points From PatrolRoute
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Warning: No Patrol Points Added"));
		return EBTNodeResult::Failed;
	}

	// OLD WAY OF CASTING TO THIRD PERSON CHARACTER
	/*
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	TArray<AActor*> PatrolPoint = PatrollingGuard->PatrolPointsCPP;
	*/

	// Set Next Waypoint
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName); // Finds name of index key in Behavior Tree
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	
	// Cycle The Index
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
