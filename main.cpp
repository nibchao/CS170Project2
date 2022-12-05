#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int crossValidation(ifstream&, vector<int>, int);
void nearestneighbortemp();

int main()
{
	/*string fileName = "";
	int algorithmInput = 0;
	cout << "Welcome to Nicholas's Feature Selection Algorithm.\n";
	cout << "Type in the name of file to test : ";
	cin >> fileName;
	cout << "\nType the number of the algorithm you want to run.\n";
	cout << "1) Forward Selection\n";
	cout << "2) Backward Elimination\n";
	cin >> algorithmInput;

	ifstream dataFile(fileName);
	int fileSize = 0;
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
	int row = 0;
	int column = 0;
	float a = 0;
	while (getline(dataFile, line))
	{
		row++;
		if (row == 1)
		{
			stringstream lineStream(line);
			while (lineStream >> a) column++;
		}
	}
	cout << "\nThis dataset has " << column - 1 << " features (not including the class attribute), with " << fileSize << " instances.\n";*/
	nearestneighbortemp();
	return 0;
}

int crossValidation(ifstream& dataFile, vector<int> currentSetOfFeatures, int featureToAdd)
{
	srand(time(0));
	return rand() % 100;
}

void nearestneighbortemp()
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
	int numberCorrectlyClassified = 0;
	int accuracy = 0;
	for (int i = 1; i <= fileSize - 485; i++)
	{
		string objectToClassify = ""; // entire line
		float labelObjectToClassify = 0; // first column
		int nearestNeighborDistance = INT_MAX;
		int nearestNeighborLocation = INT_MAX;
		int nearestNeighborLabel = 0;

		getline(dataFile, objectToClassify);
		stringstream lineStream(objectToClassify);
		lineStream >> labelObjectToClassify;

		for (int k = 1; k <= fileSize - 486; k++)
		{
			if (i != k)
			{
				int distance = pow(4, 0.5); // replace 0 with sqrt(sum(objectToClassify - data(k,2:end)).^2))
				if (distance < nearestNeighborDistance)
				{
					nearestNeighborDistance = distance;
					nearestNeighborLocation = k;
					nearestNeighborLabel = nearestNeighborLocation; // this is supposed to refer to first column class label for this specified nearest neighbor or data(nearestNeighborLocation,1)
				}
			}
		}

		if (labelObjectToClassify == nearestNeighborLabel)
		{
			numberCorrectlyClassified++;
		}
		cout << "Object " << i << " is class " << labelObjectToClassify << "\n";
		cout << "Its nearest_neighbor is " << nearestNeighborLocation << " which is in class " << labelObjectToClassify << "\n\n";
	}
	accuracy = numberCorrectlyClassified / fileSize;
}

void searchtemp()
{
	//for (int i = 1; i <= fileSize - 485; i++)
	//{
	//	cout << "On the " << i << "th level of the search tree\n";
	//	int featureToAddAtThisLevel;
	//	int bestSoFarAccuracy = 0;
	//	bool stop = false;
	//	for (int k = 1; k <= fileSize - 485; k++)
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
}
