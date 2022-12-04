#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int crossValidation(ifstream&, vector<int>, int);

int main()
{
	ifstream dataFile("CS170_Small_Data__103.txt");
	int fileSize = 0;
	vector<int> currentSetOfFeatures;

	string line = "";
	while (getline(dataFile, line))
	{
		stringstream lineStream(line);
		float a;
		while (lineStream >> a)
		{
			fileSize++;
			break;
		}
		
	}

	/* get first number in each line ("class" for each feature)
	while (getline(dataFile, line))
	{
		stringstream lineStream(line);
		float a;
		while (lineStream >> a)
		{
			cout << a << " ";
			break;
		}
		cout << "\n";
	}*/

	for (int i = 497; i <= fileSize; i++)
	{
		cout << "On the " << i << "th level of the search tree\n";
		vector<int> featureToAddAtThisLevel;
		int bestSoFarAccuracy = 0;
		for (int k = 497; k <= fileSize; k++)
		{
			if (currentSetOfFeatures.empty())
			{
				cout << "--Considering adding the " << k << " feature\n";
				int accuracy = crossValidation(dataFile, currentSetOfFeatures, k + 1);
				if (accuracy > bestSoFarAccuracy)
				{
					bestSoFarAccuracy = accuracy;
					featureToAddAtThisLevel.push_back(k);
				}
			}
		}
	}
	return 0;
}

int crossValidation(ifstream& dataFile, vector<int> currentSetOfFeatures, int featureToAdd)
{
	srand(time(0));
	return rand() % 100;
}
