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
void searchAlgorithm(int, vector<datasetPoint>);
double calculateDistance(datasetPoint, datasetPoint, vector<int>);

int instances = 0;
int column = -1;

int main()
{
    string fileName = "";
    int algorithmInput = 0;

    int row = 0;
    double a = 0;
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
        if (row == 1)
        {
            stringstream numberOfColumns(line);
            while (numberOfColumns >> a)
            {
                column++;
            }
        }
        stringstream storeDataClass(line);
        storeDataClass >> a;
        dataInEachLine.dataClass = a;
        while (storeDataClass >> a)
        {
            dataInEachLine.dataFeatures.push_back(a);
        }
        dataVector.push_back(dataInEachLine);
        dataInEachLine.dataFeatures.clear();
    }
    vector<int> currentSetOfFeatures;
    for (int cnt = 0; cnt < column; cnt++)
    {
        currentSetOfFeatures.push_back(cnt);
    }
    instances = dataVector.size();
    cout << "\nThis dataset has " << column << " features (not including the class attribute), with " << instances << " instances.\n\n";
    cout << "Running nearest neighbor with all " << column << " features, using 'leaving-one-out' evaluation, I get an accuracy of " << nearestNeighbor(dataVector, currentSetOfFeatures) << "%\n\n";
    cout << "Beginning search.\n";
    searchAlgorithm(1, dataVector);
    //searchAlgorithm(2, dataVector);
    return 0;
}

double nearestNeighbor(vector<datasetPoint> dataVector, vector<int> currentSetOfFeatures)
{
    double numberCorrectlyClassified = 0;
    for (int i = 0; i < dataVector.size(); i++)
    {
        datasetPoint objectToClassify = dataVector.at(i); // refers to an entire line (object) in dataVector
        //int labelObjectToClassify = dataVector.at(i).dataClass;
        double nearestNeighborDistance = INT_MAX;
        //double nearestNeighborLocation = INT_MAX;
        int nearestNeighborLabel = -1;
        for (int k = 0; k < i; k++)
        {
            if (i != k)
            {
                double distance = calculateDistance(objectToClassify, dataVector.at(k), currentSetOfFeatures);
                if (distance < nearestNeighborDistance)
                {
                    nearestNeighborDistance = distance;
                    //nearestNeighborLocation = k;
                    nearestNeighborLabel = dataVector.at(k).dataClass;
                }
            }
        }
        if (objectToClassify.dataClass == nearestNeighborLabel)
        {
            numberCorrectlyClassified++;
        }
        //cout << "Object " << i << " is class " << labelObjectToClassify << "\n";
        //cout << "Its nearest_neighbor is " << nearestNeighborLocation << " which is in class " << nearestNeighborLabel << "\n\n";
    }
    return numberCorrectlyClassified / instances * 100;
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

void searchAlgorithm(int algorithmInput, vector<datasetPoint> dataVector)
{
    vector<int> currentSetOfFeatures;
    double bestSoFarAccuracy = 0.01;
    double accuracy = 0;
    int featureToAddAtThisLevel = 0;
    double prevAccuracy = 0;
    if (algorithmInput == 1) // do forward selection
    {
        while (prevAccuracy < bestSoFarAccuracy)
        {
            prevAccuracy = bestSoFarAccuracy;
            for (int i = 0; i < dataVector.at(0).dataFeatures.size(); i++)
            {
                bool stop = false;
                //cout << "On the " << i + 1 << "th level of the search tree\n";
                for (int k = 0; k < currentSetOfFeatures.size(); k++)
                {
                    if (currentSetOfFeatures.at(k) == i)
                    {
                        stop = true;
                    }
                }
                if (!stop)
                {
                    //cout << "--Considering adding the " << k + 1 << " feature\n";
                    currentSetOfFeatures.push_back(i);
                    accuracy = nearestNeighbor(dataVector, currentSetOfFeatures);
                    cout << "Feature ";
                    for (int cnt = 0; cnt < currentSetOfFeatures.size(); cnt++)
                    {
                        cout << currentSetOfFeatures[cnt] + 1 << " ";
                    }
                    cout << "accuracy is " << accuracy << "\n";
                    if (accuracy > bestSoFarAccuracy)
                    {
                        bestSoFarAccuracy = accuracy;
                        featureToAddAtThisLevel = i;
                    }
                    currentSetOfFeatures.pop_back();
                }
            }
            if (prevAccuracy == bestSoFarAccuracy)
            {
                break;
            }
            currentSetOfFeatures.push_back(featureToAddAtThisLevel);
            for (int cnt = 0; cnt < currentSetOfFeatures.size(); cnt++)
            {
                cout << currentSetOfFeatures[cnt] + 1 << " ";
            }
            cout << "was best accuracy of " << bestSoFarAccuracy << "\n";
        }
        cout << "\ndone search\n";
		cout << "best features were ";
		for (int cnt = 0; cnt < currentSetOfFeatures.size(); cnt++)
		{
			cout << currentSetOfFeatures[cnt] + 1 << " ";
		}
		cout << bestSoFarAccuracy;
    }
    else if (algorithmInput == 2)
    {

    }
}