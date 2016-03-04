#include "GAMachine.h"

void GAMachine::SetupNextGeneration()
{
}

void GAMachine::CreateStartPopulation()
{
}

void GAMachine::Update(float dt)
{
	// Find best out of the maximum tries, then start over
	if (generations > NUM_MAX_GENERATIONS)
	{
		WriteSolution();
		// Reset
		CreateStartPopulation();
		Reset();
	}

	liveCount = 0;
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{

	}
}

void GAMachine::UpdateFitness(int index)
{
}

void GAMachine::Init()
{
}

void GAMachine::Reset()
{
}

void GAMachine::ApplyBehaviorRule(int index)
{
}

bool GAMachine::WriteSolution()
{
	return false;
}

bool GAMachine::ReadSolution()
{
	return false;
}

Genome & GAMachine::SelectRouletteWheel()
{
	// TODO: insert return statement here
}

Genome & GAMachine::SelectTournament()
{
	// TODO: insert return statement here
}

Genome & GAMachine::SelectRank()
{
	// TODO: insert return statement here
}

void GAMachine::CrossPMX(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
}

void GAMachine::CrossOrderBased(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
}

void GAMachine::CrossPositionBased(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
}

void GAMachine::MutateOffset(std::vector<Gene>& genes)
{
}

void GAMachine::MutateExchange(std::vector<Gene>& genes)
{
}

void GAMachine::MutateDisplacement(std::vector<Gene>& genes)
{
}

void GAMachine::MutateInsertion(std::vector<Gene>& genes)
{
}

void GAMachine::CopyEliteInto(std::vector<Genome>& destination)
{
}
