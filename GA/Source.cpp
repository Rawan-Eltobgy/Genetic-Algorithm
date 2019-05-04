#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <cstdlib>

using namespace std;
using std::string;

#define CROSSOVER_RATE            0.7
#define MUTATION_RATE             0.001
#define POPULTATION_SIZE                  10			//must be even number
//#define CHROMO_LENGTH             8
#define GENE_LENGTH               4            //4 bits
//#define NUMBER_OF_GENERATIONS	6         //no of generations

const int CHROMO_LENGTH = 8;
const int NUMBER_OF_GENERATIONS = 3;
int num[11];


class Chromosome{
private:
	string bits;
	float fitness;

public:
	Chromosome(){
		bits = CHROMO_LENGTH;
		fitness = 0.0;
	}

	Chromosome(string b, float f){
		bits = b;
		fitness = f;
	}

	void setBits(string b){
		bits = b;
	}

	void setFitness(float f){
		fitness = f;
	}

	string getBits(){
		return bits;
	}

	float getFitness(){
		return fitness;
	}
	
};

double calcResult(int value) {
		double result;
		result = (5 + value) / (sqrt(value) - cos(value));
		return result;
	}

	string	GetRandomBits(int length)
	{
		string bits;

		for (int i= 0; i<length; i++)
		{
			if (rand() % 2 == 0)

				bits += "0";

			else

				bits += "1";
		}

		return bits;
	}

	int	BinaryToInteger(string bits)
	{
		int val = 0;
		int value_to_add = 1;

		for (int i= bits.length(); i> 0; i--)
		{


			if (bits.at(i- 1) == '1')

				val += value_to_add;

			value_to_add *= 2;

		}//next bit

		return val;
	}

	bool ValueCmp(Chromosome & chromosome1, Chromosome  & chromosome2) {
		return chromosome1.getFitness() < chromosome2.getFitness();
	}
	
	Chromosome child1, child2;
	void crossover(Chromosome chromosome1, Chromosome chromosome2){
		int startIndex = 0, midIndex = (CHROMO_LENGTH / 2)-1 , endIndex = CHROMO_LENGTH-1;
		int temp;
		child1.setBits((chromosome1.getBits()).substr(startIndex, midIndex) + (chromosome2.getBits()).substr(midIndex + 1, endIndex));
		child2.setBits((chromosome2.getBits()).substr(startIndex, midIndex) + (chromosome1.getBits()).substr(midIndex + 1, endIndex));

		temp = BinaryToInteger(chromosome1.getBits());
		child1.setFitness(calcResult(temp));

		temp = BinaryToInteger(chromosome2.getBits());
		child2.setFitness(calcResult(temp));
	}

	Chromosome mutation(Chromosome chromosome){
		int temp;
		int index = rand() % 8;
		string bits = chromosome.getBits();
		if (bits[index] == '1')
			bits[index] = '0';
		else
			bits[index] = '1';

		chromosome.setBits(bits);
		temp = BinaryToInteger(chromosome.getBits());
		chromosome.setFitness(calcResult(temp));
		return chromosome;
	}

	void printGeneration(Chromosome chromosomes[POPULTATION_SIZE]){
		for (int j = 0; j< POPULTATION_SIZE; j++)
		{
			cout << chromosomes[j].getFitness() <<"\t";
		}
	}

int main()
{
	srand((int)time(NULL));
	Chromosome chromosomes[POPULTATION_SIZE];
	int value, min, min2, max;

	for (int j = 0; j < POPULTATION_SIZE; j++)
	{
		chromosomes[j] = Chromosome();
		//chromosomes[i].setBits(GetRandomBits(CHROMO_LENGTH));
		chromosomes[j].setBits(GetRandomBits(CHROMO_LENGTH));
		//cout << x << endl;
		value = BinaryToInteger(chromosomes[j].getBits());
		chromosomes[j].setFitness((value));
	}

	for (int i = 0; i < NUMBER_OF_GENERATIONS; i++){
		
		cout << "before sort" << endl;
		printGeneration(chromosomes);
		sort(chromosomes, chromosomes + POPULTATION_SIZE, ValueCmp);

		cout << "after sort" << endl;
		printGeneration(chromosomes);

		min = 0;
		chromosomes[min] = mutation(chromosomes[min]);
		//min2 = 1;
		max = POPULTATION_SIZE - 1;
		for (int j = 1; j < POPULTATION_SIZE - 1; j = j + 2){        //34an el crossover hy3dy mn awl 1 index l7d abl el a5er
			crossover(chromosomes[j], chromosomes[j + 1]);
			chromosomes[j] = child1;
			chromosomes[j + 1] = child2;


			//cout << "first best gene" << chromosomes[min1].getFitness() << endl;
			//cout << "second best gene" << chromosomes[min2].getFitness() << endl;
			
			//sort(chromosomes, chromosomes + POPULTATION_SIZE, ValueCmp);
		}
		
		cout << "best gene" << chromosomes[max].getFitness() << endl;
		cout << "worst gene" << chromosomes[min].getFitness() << endl;
		cout << "after crossover & mutations" << endl;
		printGeneration(chromosomes);
	}
	


	//cout <<CHROMO_LENGTH<< endl;

	int e;
	cin >> e;
	return 0;
}
