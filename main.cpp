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
	dataFile.clear();
	dataFile.seekg(0, dataFile.beg);
	for (int i = 497; i <= fileSize; i++)
	{
		getline(dataFile, line);
		stringstream lineStream(line);
		float a;
		lineStream >> a;
		cout << "Looping over i, at the " << i << " location\n";
		cout << "The " << i << "th object is in class " << a << "\n";
	}

	//for (int i = 497; i <= fileSize; i++)
	//{
	//	cout << "On the " << i << "th level of the search tree\n";
	//	int featureToAddAtThisLevel;
	//	int bestSoFarAccuracy = 0;
	//	bool stop = false;
	//	for (int k = 497; k <= fileSize; k++)
	//	{
	//		if (count(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), k))
	//		{
	//			break; // feature already added, skip
	//		}
	//		else
	//		{
	//			cout << "--Considering adding the " << k << " feature\n";
	//			int accuracy = crossValidation(dataFile, currentSetOfFeatures, k + 1);
	//			if (accuracy > bestSoFarAccuracy)
	//			{
	//				bestSoFarAccuracy = accuracy;
	//				featureToAddAtThisLevel = k;
	//			}
	//		}		
	//	}
	//	currentSetOfFeatures.push_back(featureToAddAtThisLevel);
	//	cout << "On level " << i << " I added feature " << featureToAddAtThisLevel << " to current set\n";
	//}
	return 0;
}

int crossValidation(ifstream& dataFile, vector<int> currentSetOfFeatures, int featureToAdd)
{
	srand(time(0));
	return rand() % 100;
}
