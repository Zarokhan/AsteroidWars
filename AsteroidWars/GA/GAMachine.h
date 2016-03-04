#pragma once
#include <vector>
#include "GAAIControl.h"
#include "Genome.h"

#define NUM_MAX_GENERATIONS 100
#define POPULATION_SIZE 10

class GAMachine
{
public:
	GAMachine(GAAIControl* parent) : parent(parent) {}
	void SetupNextGeneration();
	void CreateStartPopulation();
	void Update(float dt);
	void UpdateFitness(int index);
	void Init();
	void Reset();
	void ApplyBehaviorRule(int index);
	bool WriteSolution();
	bool ReadSolution();

	// Selection operators
	Genome& SelectRouletteWheel();
	Genome& SelectTournament();
	Genome& SelectRank();

	// Crossover operators - order based genes
	void CrossPMX(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	void CrossOrderBased(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	void CrossPositionBased(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);

	// Mutation operators
	void MutateOffset(std::vector<Gene> &genes);
	// Mutation operators - order based genes
	void MutateExchange(std::vector<Gene> &genes);
	void MutateDisplacement(std::vector<Gene> &genes);
	void MutateInsertion(std::vector<Gene> &genes);

	// Elitism
	void CopyEliteInto(std::vector<Genome> &destination);

protected:
	GAAIControl* parent;
	// Data
	std::vector<Genome> genomes;
	int rankIndexLast;
	Genome bestGenome;
	int generations;
	float crossoverRate;
	float mutationRate;
	float offsetSize;
	float bestFitness;
	float totalFitness;
	int liveCount;
};