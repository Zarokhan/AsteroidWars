#pragma once
#include <vector>
#include "GAAIControl.h"
#include "Genome.h"
#include "GASession.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

#define NUM_MAX_GENERATIONS 10000000

class GASession;
class GAAIControl;

class GAMachine
{
public:
	GAMachine(GAAIControl* parent) : parent(parent) { std::srand(std::time(0)); Init(); }
	~GAMachine();
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
	Genome& SelectMySelection(); // Home made selection
	//Genome& SelectTournament();
	//Genome& SelectRank();

	// Crossover operators - order based genes
	void CrossUniform(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	//void CrossSinglePoint(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	//void CrossMultiPoint(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	//void CrossPMX(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	//void CrossOrderBased(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);
	//void CrossPositionBased(const std::vector<Gene> &parent1, const std::vector<Gene> &parent2, std::vector<Gene> &offspring1, std::vector<Gene> &offspring2);

	// Mutation operators
	void MutateOffset(std::vector<Gene> &genes);
	// Mutation operators - order based genes
	//void MutateExchange(std::vector<Gene> &genes);
	//void MutateDisplacement(std::vector<Gene> &genes);
	//void MutateInsertion(std::vector<Gene> &genes);

	// Elitism
	void CopyEliteInto(std::vector<Genome> &destination);

	GASession* Session;

	inline const float GNR_RANDOM_FLOAT(int max = 1)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	}

	inline const int GNR_RANDOM_INT(int max)
	{
		return rand() % max;
	}

	std::ofstream myfile;


public:
	GAAIControl* parent;
	// Data
	std::vector<Genome> genomes;
	Genome bestGenome;
	bool elitism;
	int rankIndexLast;
	int generations;
	int liveCount;
	float crossoverRate;
	float mutationRate;
	float offsetSize;
	float bestFitness;
	float totalFitness;

	// Keeping track of best generation data
	int singleGeneration;
	int bestFitnessGeneration;

	int totalGeneration;
	int bestTotalFitnessGeneration;
};