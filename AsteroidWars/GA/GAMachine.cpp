#include "GAMachine.h"
#include "../MathUtils.h"
#include <string>

void GAMachine::Init()
{
	crossoverRate = 0.5f;
	mutationRate = 0.15f;
	offsetSize = 1.f;
	elitism = true;
}

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

	// Best generation
	if (bestFitness > bestFitnessGeneration)
	{
		bestFitnessGeneration = bestFitness;
		singleGeneration = generations;
	}

	if (totalFitness > bestTotalFitnessGeneration)
	{
		bestTotalFitnessGeneration = totalFitness;
		totalGeneration = generations;
	}

	std::vector<std::string> lines;

	std::ifstream readfile;
	readfile.open("generations.txt");
	char output[10000];
	if (readfile.is_open())
	{
		while (!readfile.eof())
		{
			readfile >> output;
			lines.push_back(output);
		}
	}

	myfile.open("generations.txt");
	myfile << bestFitness << "\n";
	for (int i = 0; i < lines.size(); i++)
		myfile << lines[i] << "\n";
	myfile.close();

	if (elitism)
		CopyEliteInto(offspring);

	int i = 0;
	while (offspring.size() < POPULATION_SIZE)
	{
		// Selection operator
		Genome parent1 = genomes[i];		//SelectRouletteWheel();
		Genome parent2 = genomes[i + 1];	//SelectRouletteWheel();

		// Crossover operation
		Genome offspring1, offspring2;
		CrossUniform(parent1.genes, parent2.genes, offspring1.genes, offspring2.genes);

		// mutation operator
		MutateOffset(offspring1.genes);
		MutateOffset(offspring2.genes);

		// Add to new population;
		offspring.push_back(offspring1);
		offspring.push_back(offspring2);
		i += 2;
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
	Session->Restart();
}

void GAMachine::CreateStartPopulation()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		Genome genome;
		for (int i = 0; i < 112; i++)
		{
			Gene gene(GNR_RANDOM_INT(2), GNR_RANDOM_INT(NUM_SECTORS - 1));
			genome.genes.push_back(gene);
		}
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

void GAMachine::Reset()
{
}

void GAMachine::ApplyBehaviorRule(int index)
{
	if (index < 0 || index > POPULATION_SIZE)
		return;

	Ship* ship = (Ship*)Session->ships[index];

	// not going to collide, just idle...
	//if (Session->ships[index]->currentEvasionSituation == -1)
	//{
	//	//ship->ThrustOFF
	//	//ship->stopturn
	//	return;
	//}

	// thrust
	int thrustTp = genomes[index].genes[parent->currentEvasionSituation].thrust;
	//ship->stopturn
	if (thrustTp == 0)
		ship->ThrustForward();
	else if (thrustTp == 1)
		ship->ThrustBackward();
	//else
		//ship->thrustoff

	// Turn
	// -10 puts you in the middle of the sector
	float newDir = genomes[index].genes[parent->currentEvasionSituation].sector * 20 - 10;
	float angDelta = Utils::CLAMPDIR180(ship->rotation - newDir);
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

Genome & GAMachine::SelectMySelection()
{
	for (int i = 0; i < POPULATION_SIZE / 2; i += 2)
	{

	}
}

void GAMachine::CrossUniform(const std::vector<Gene>& parent1, const std::vector<Gene>& parent2, std::vector<Gene>& offspring1, std::vector<Gene>& offspring2)
{
	if ((GNR_RANDOM_FLOAT() > crossoverRate) || (parent1 == parent2))
	{
		offspring1 = parent1;
		offspring2 = parent2;
		return;
	}
	for (int gene = 0; gene < POPULATION_SIZE; gene++)
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

#define NUM_THRUST_STATES 2
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