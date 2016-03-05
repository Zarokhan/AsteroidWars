#include "GAMachine.h"
#include "../MathUtils.h"

void GAMachine::SetupNextGeneration()
{
	// Next generation
	std::vector<Genome> offspring;

	// Sort the population (for scaling and elitism)
	std::sort(genomes.begin(), genomes.end());
	rankIndexLast = POPULATION_SIZE - 1;

	// Statistics
	totalFitness = 0.f;
	for (int i = 0; i < POPULATION_SIZE; i++)
		totalFitness += genomes[i].fitness;
	bestFitness = genomes[POPULATION_SIZE - 1].fitness;

	CopyEliteInto(offspring);

	while (offspring.size() < POPULATION_SIZE)
	{
		// Selection operator
		Genome parent1 = SelectRouletteWheel();
		Genome parent2 = SelectRouletteWheel();

		// Crossover operation
		Genome offspring1, offspring2;
		CrossSinglePoint(parent1.genes, parent2.genes, offspring1.genes, offspring2.genes);

		// mutation operator
		MutateOffset(offspring1.genes);
		MutateOffset(offspring2.genes);

		// Add to new population;
		offspring.push_back(offspring1);
		offspring.push_back(offspring2);
	}

	// Replace old generation with new
	genomes = offspring;

	for (int i = 0; i < POPULATION_SIZE; i++)
		genomes[i].fitness = 0.f;

	generations++;

	// Reactivate the ships
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		// Reset test ships to startup state
		Ship* ship = (Ship*)Session->ships[i];
		ship->active = true;
		ship->ResetVelocity();
	}
}

void GAMachine::CreateStartPopulation()
{
	for (int i = 0; i < GENOME_SIZE; i++)
	{
		Genome genome;
		genomes.push_back(genome);
	}
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
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (!Session->ships[i]->active)
			continue;
		liveCount++;
		parent->UpdatePerceptions(dt, i);
		ApplyBehaviorRule(i);
		UpdateFitness(i);
	}

	if (!liveCount)
		SetupNextGeneration();
}

void GAMachine::UpdateFitness(int index)
{
	Ship* ship = (Ship*)Session->ships[index];
	if (ship && ship->active)
	{
		// If Im currently surviving a collision situation, increase fitness
		if (parent->currentEvasionSituation != -1)
			genomes[index].fitness++;
		liveCount++;
	}
}

void GAMachine::Init()
{
}

void GAMachine::Reset()
{
}

void GAMachine::ApplyBehaviorRule(int index)
{
	if (index < 0 || index > POPULATION_SIZE)
		return;

	Ship* ship = (Ship*)Session->ships[index];

	// not going to collide, just idle...
	if (parent->currentEvasionSituation == -1)
	{
		//ship->ThrustOFF
		//ship->stopturn
		return;
	}

	// thrust
	int thrustTp = genomes[index].genes[parent->currentEvasionSituation].thrust;
	//ship->stopturn
	if (thrustTp == Gene::THRUST_FORWARD)
		ship->ThrustForward();
	else if (thrustTp == Gene::THRUST_REVERSE)
		ship->ThrustBackward();
	//else
		//ship->thrustoff

	// Turn
	// -10 puts you in the middle of the sector
	float newDir = genomes[index].genes[parent->currentEvasionSituation].sector * 20 - 10;
	float angDelta = FunMath::CLAMPDIR180(ship->rotation - newDir);
	if (fabsf(angDelta) <= 90)
	{
		if (angDelta > 0)
			ship->SteerRight(1);
		else
			ship->SteerRight(-1);
	}
	else
	{
		if (angDelta < 0)
			ship->SteerRight(1);
		else
			ship->SteerRight(-1);
	}
}

bool GAMachine::WriteSolution()
{
	return false;
}

bool GAMachine::ReadSolution()
{
	return false;
}

Genome& GAMachine::SelectRouletteWheel()
{
	float wedge = GNR_RANDOM_FLOAT() * totalFitness;
	float total = 0.f;

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		total += genomes[i].fitness;
		if (total > wedge)
			return genomes[i];
	}

	return genomes[0];
}

Genome& GAMachine::SelectTournament()
{
	// TODO: insert return statement here
	return genomes[0];
}

Genome& GAMachine::SelectRank()
{
	// TODO: insert return statement here
	return genomes[0];
}

void GAMachine::CrossUniform(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
	if ((GNR_RANDOM_FLOAT() > crossoverRate) || (parent1 == parent2))
	{
		offspring1 = parent1;
		offspring2 = parent2;
		return;
	}
	for (int gene = 0; gene < GENOME_SIZE; gene++)
	{
		if (GNR_RANDOM_FLOAT() < crossoverRate)
		{
			// Switch the genes at this point
			offspring1.push_back(parent2[gene]);
			offspring2.push_back(parent1[gene]);
		}
		else
		{
			// Just copy into offspring
			offspring1.push_back(parent1[gene]);
			offspring2.push_back(parent2[gene]);
		}
	}
}

void GAMachine::CrossSinglePoint(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
}

void GAMachine::CrossMultiPoint(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
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

#define NUM_THRUST_STATES 2
#define NUM_SECTORS 18
void GAMachine::MutateOffset(std::vector<Gene>& genes)
{
	for (int gene = 0; gene < genes.size(); gene++)
	{
		// Check for thrust mutation
		if (GNR_RANDOM_FLOAT() < mutationRate)
		{
			genes[gene].thrust += (GNR_RANDOM_INT(1) ? -offsetSize : offsetSize);

			// Bounds check
			if (genes[gene].thrust > NUM_THRUST_STATES)
				genes[gene].thrust = 0;

			if (genes[gene].thrust < 0)
				genes[gene].thrust = NUM_THRUST_STATES;
		}

		// Check for angle mutation
		if (GNR_RANDOM_FLOAT() < mutationRate)
		{
			genes[gene].sector += (GNR_RANDOM_INT(1) ? -offsetSize : offsetSize);

			// Bounds check
			if (genes[gene].sector > NUM_SECTORS)
				genes[gene].sector = 0;
			if (genes[gene].sector < 0)
				genes[gene].sector = NUM_SECTORS;
		}
	}
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

#define NUM_ELITE 4
#define NUM_COPIES_ELITE 2
void GAMachine::CopyEliteInto(std::vector<Genome>& destination)
{
	int numberOfElite = NUM_ELITE;
	// Copy the elite over to the supplied destination
	for (int i = 0; i > 0; i--)
	{
		for (int j = 0; i < NUM_COPIES_ELITE; j++)
			destination.push_back(genomes[(POPULATION_SIZE - 1) - numberOfElite]);
	}
}

GAMachine::~GAMachine()
{
}