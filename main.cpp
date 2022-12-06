#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct datasetPoint
{
	int dataClass;
	vector<double> dataFeatures;
};

double nearestNeighbor(vector<datasetPoint>, vector<int>);
void searchAlgorithm(int);
double calculateDistance(datasetPoint, datasetPoint, vector<int>);

int main()
{
	string fileName = "";
	int algorithmInput = 0;

	int row = 0; int column = -1;
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

	//ifstream dataFile("CS170_Small_Data__103.txt"); // temp line for testing my data
	ifstream dataFile("CS170_Small_Data__96.txt"); // temp line for testing sue data

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
	vector<int> currentSetOfFeatures;
	for (int cnt = 0; cnt < column; cnt++)
	{
		currentSetOfFeatures.push_back(cnt + 1);
	}
	//cout << "\nThis dataset has " << column << " features (not including the class attribute), with " << dataVector.size() << " instances.\n\n";
	cout << "Running nearest neighbor with all " << column << " features, using 'leaving-one-out' evaluation, I get an accuracy of " << nearestNeighbor(dataVector, currentSetOfFeatures)*100 << "%\n\n";
	cout << "Beginning search.\n";
	searchAlgorithm(algorithmInput);
	return 0;
}

double nearestNeighbor(vector<datasetPoint> dataVector, vector<int> currentSetOfFeatures)
{
	double numberCorrectlyClassified = 0;
	datasetPoint leaveOneOut;

	for (int i = 0; i < dataVector.size(); i++)
	{
		datasetPoint objectToClassify = dataVector.at(i); // refers to an entire line (object) in dataVector
		double labelObjectToClassify = dataVector.at(i).dataClass;

		double nearestNeighborDistance = INT_MAX;
		double nearestNeighborLocation = INT_MAX;
		double nearestNeighborLabel = -1;
		for (int k = 0; k < dataVector.size(); k++)
		{
			if (i != k)
			{			
				double distance = calculateDistance(objectToClassify, dataVector.at(k), currentSetOfFeatures);
				if (distance < nearestNeighborDistance)
				{
					nearestNeighborDistance = distance;
					nearestNeighborLocation = k;
					nearestNeighborLabel = dataVector.at(k).dataClass;
				}
			}
		}
		if (objectToClassify.dataClass == nearestNeighborLabel)
		{
			numberCorrectlyClassified++;
		}
		cout << "Object " << i << " is class " << labelObjectToClassify << "\n";
		cout << "Its nearest_neighbor is " << nearestNeighborLocation << " which is in class " << nearestNeighborLabel << "\n\n";
	}
	return numberCorrectlyClassified / dataVector.size();
}

double calculateDistance(datasetPoint line, datasetPoint line2, vector<int> currentSetOfFeatures)
{
	double distance = 0;
	for (int cnt = 0; cnt < currentSetOfFeatures.size(); cnt++)
	{
		distance += pow(line.dataFeatures.at(currentSetOfFeatures.at(cnt)) - line2.dataFeatures.at(currentSetOfFeatures.at(cnt)), 2);
	}
	return pow(distance, 0.5);
}

void searchAlgorithm(int algorithmInput)
{
	if (algorithmInput == 1)
	{
		// do forward selection
		//for (int i = 1; i <= fileSize; i++)
		//{
		//	cout << "On the " << i << "th level of the search tree\n";
		//	int featureToAddAtThisLevel;
		//	int bestSoFarAccuracy = 0;
		//	bool stop = false;
		//	for (int k = 1; k <= fileSize; k++)
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
	else if (algorithmInput == 2)
	{
		// do backward elimination
		//for (int i = 1; i <= fileSize; i++)
		//{
		//	cout << "On the " << i << "th level of the search tree\n";
		//	int featureToAddAtThisLevel;
		//	int bestSoFarAccuracy = 0;
		//	bool stop = false;
		//	for (int k = 1; k <= fileSize; k++)
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
}
