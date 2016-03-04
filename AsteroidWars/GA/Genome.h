#pragma once
#include <vector>
#include "Gene.h"

class Genome
{
public:
	Genome() : fitness(0) {}
	Genome(const int num_genes) : fitness(0)
	{
		for (int i = 0; i < num_genes; i++)
			genes.push_back(Gene());
	}

	bool operator < (const Genome& rhs) { return (fitness < rhs.fitness); }
	
	// data
	std::vector<Gene> genes;
	float fitness;
};