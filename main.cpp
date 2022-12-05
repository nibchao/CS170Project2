#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int crossValidation(ifstream&, vector<int>, int);
double nearestNeighbor(vector<vector<double>>);
void searchAlgorithm(int);

const int TEMP_DATA_LIMIT_CONST = 495; // temp line for testing

struct datasetPoint
{
	int dataClass;
	vector<double> dataFeatures;
};

int main()
{
	string fileName = "";
	int algorithmInput = 0;

	int row = 0; int column = 0;
	int dataClass = 0; double a = 0;
	string line = "";

	vector<datasetPoint> dataVector;
	datasetPoint dataInEachLine;

	/*cout << "Welcome to Nicholas's Feature Selection Algorithm.\n";
	cout << "Type in the name of file to test : ";
	cin >> fileName;
	cout << "\nType the number of the algorithm you want to run.\n";
	cout << "1) Forward Selection\n";
	cout << "2) Backward Elimination\n";
	cin >> algorithmInput;
	ifstream dataFile(fileName);*/
	ifstream dataFile("CS170_Small_Data__103.txt"); // temp line for testing
	
	while (getline(dataFile, line))
	{
		row++;
		if (row == 1) // counts number of columns (features) in dataset
		{
			stringstream numberOfColumns(line);
			while (numberOfColumns >> a)
			{
				column++;
			}
		}
		stringstream storeDataClass(line);
		while (storeDataClass >> dataClass) // stores class into dataInEachLine dataClass field
		{
			dataInEachLine.dataClass = dataClass;
			stringstream storeDataFeatures(line);
			while (storeDataFeatures >> a) // stores feature numbers into dataInEachLine dataFeatures vector
			{
				dataInEachLine.dataFeatures.push_back(a);
			}
			dataVector.push_back(dataInEachLine); // stores the line as type datasetPoint into dataVector
			dataInEachLine.dataFeatures.clear();
		}
	}
	column--;
	//cout << "\nThis dataset has " << column << " features (not including the class attribute), with " << dataVector.size() << " instances.\n";
	searchAlgorithm(algorithmInput);
	//nearestNeighbor(dataVector);
	return 0;
}

double nearestNeighbor(vector<vector<double>> dataVector)
{
	vector<int> currentSetOfFeatures;
	int numberCorrectlyClassified = 0;

	for (int i = 1; i <= dataVector.size() - TEMP_DATA_LIMIT_CONST; i++)
	{
		double labelObjectToClassify = dataVector[i][0];
		double nearestNeighborDistance = INT_MAX;
		double nearestNeighborLocation = INT_MAX;
		double nearestNeighborLabel = 0;
		for (int k = 1; k <= dataVector.size() - TEMP_DATA_LIMIT_CONST; k++)
		{
			if (i != k)
			{			
				double distance = 0; // replace 0 with sqrt(sum(objectToClassify - data(k,2:end)).^2))
				if (distance < nearestNeighborDistance)
				{
					nearestNeighborDistance = distance;
					nearestNeighborLocation = k;
					nearestNeighborLabel = dataVector[nearestNeighborLocation][0]; // this is supposed to refer to first column class label for this specified nearest neighbor or data(nearestNeighborLocation,1)
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
	return numberCorrectlyClassified / dataVector.size();
}

void searchtemp()
{
	//for (int i = 1; i <= fileSize - TEMP_DATA_LIMIT_CONST; i++)
	//{
	//	cout << "On the " << i << "th level of the search tree\n";
	//	int featureToAddAtThisLevel;
	//	int bestSoFarAccuracy = 0;
	//	bool stop = false;
	//	for (int k = 1; k <= fileSize - TEMP_DATA_LIMIT_CONST; k++)
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

void searchAlgorithm(int algorithmInput)
{
	if (algorithmInput == 1)
	{
		// do forward selection
	}
	else if (algorithmInput == 2)
	{
		// do backward elimination
	}
}

int crossValidation(ifstream& dataFile, vector<int> currentSetOfFeatures, int featureToAdd)
{
	srand(time(0));
	return rand() % 100;
}
