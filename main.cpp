#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

struct datasetPoint // struct to store each line of the .txt files
{
    int dataClass; // int field to store class value
    vector<double> dataFeatures; // vector of type double to store the numbers for each feature
};

// function prototypes
double nearestNeighbor(vector<datasetPoint>, vector<int>, int);
void searchAlgorithm(int, vector<datasetPoint>, int, double);
double calculateDistance(datasetPoint, datasetPoint, vector<int>);
void printFeatures(vector<int>);
//

/*
* referenced https://stackoverflow.com/questions/40286788/keep-track-of-time-in-a-game-loop-in-c to keep track of how long it takes to run the program
*/
int main()
{
    string fileName = "";
    int algorithmInput = 0;
    int row = 0; int column = -1;
    double a = 0;
    int instances = 0;
    string line = "";
    vector<datasetPoint> dataVector; // vector of datasetPoint struct to store the entire .txt file
    datasetPoint dataInEachLine; // used as a way to push each line into dataVector
  
    cout << "Welcome to Nicholas's Feature Selection Algorithm.\n";
    cout << "Type in the name of file to test : ";
    cin >> fileName;
    cout << "\nType the number of the algorithm you want to run.\n";
    cout << "1) Forward Selection\n";
    cout << "2) Backward Elimination\n";
    cin >> algorithmInput;
    auto start_time = chrono::high_resolution_clock::now();
    ifstream dataFile(fileName);

    while (getline(dataFile, line))
    {
        row++;
        if (row == 1)
        {
            stringstream numberOfColumns(line);
            while (numberOfColumns >> a) // counts number of columns (features) in the dataset
            {
                column++;
            }
        }
        stringstream storeDataClass(line);
        storeDataClass >> a; // gets the class (first value of line) and stores into dataClass field
        dataInEachLine.dataClass = a;
        while (storeDataClass >> a) // stores the number for each feature (remaining values in line)
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
    double accuracy = nearestNeighbor(dataVector, currentSetOfFeatures, instances);
    cout << "Running nearest neighbor with all " << column << " features, using 'leaving-one-out' evaluation, I get an accuracy of " << accuracy << "%\n\n";
    cout << "Beginning search.\n\n";
    searchAlgorithm(algorithmInput, dataVector, instances, accuracy);

    auto current_time = chrono::high_resolution_clock::now();
    cout << "\nProgram has been running for " << chrono::duration_cast<chrono::seconds>(current_time - start_time).count() << " seconds";
    return 0;
}

/*
* referenced slides 57-63 in project 2 briefing slides
* 
* calculates the accuracy of nearest neighbor classification algorithm using the dataset
*/
double nearestNeighbor(vector<datasetPoint> dataVector, vector<int> currentSetOfFeatures, int instances)
{
    double numberCorrectlyClassified = 0;
    for (int i = 0; i < dataVector.size(); i++)
    {
        datasetPoint objectToClassify = dataVector.at(i); // refers to an entire line in dataVector
        double nearestNeighborDistance = INT_MAX;
        int nearestNeighborLabel = -1;
        for (int k = 0; k < i; k++)
        {
            if (i != k) // checks for comparing feature to itself
            {
                double distance = calculateDistance(objectToClassify, dataVector.at(k), currentSetOfFeatures);
                if (distance < nearestNeighborDistance)
                {
                    nearestNeighborDistance = distance;
                    nearestNeighborLabel = dataVector.at(k).dataClass;
                }
            }
        }
        if (objectToClassify.dataClass == nearestNeighborLabel)
        {
            numberCorrectlyClassified++;
        }
    }
    return numberCorrectlyClassified / instances * 100;
}

/*
* calculates the euclidean distance from one data point to another data point
*/
double calculateDistance(datasetPoint line, datasetPoint line2, vector<int> currentSetOfFeatures)
{
    double distance = 0;
    for (int cnt = 0; cnt < currentSetOfFeatures.size(); cnt++)
    {
        distance += pow(line.dataFeatures.at(currentSetOfFeatures.at(cnt)) - line2.dataFeatures.at(currentSetOfFeatures.at(cnt)), 2);
    }
    return pow(distance, 0.5);
}

/*
* referenced https://stackoverflow.com/a/3450906 to search for if an element exists in vector
* referenced https://stackoverflow.com/a/63712239 to see how to erase element in vector for backward elimination
* referenced slides 42-49 in project 2 briefing slides
* 
* contains the two search algorithms for the program; algorithmInput = 1 -> forward selection | algorithmInput = 2 -> backward elimination
*/
void searchAlgorithm(int algorithmInput, vector<datasetPoint> dataVector, int instances, double nearestNeighborAccuracy)
{
    vector<int> finalSetOfFeatures;
    vector<int> currentSetOfFeatures;
    double bestSoFarAccuracy = 0;
    double accuracy = 0;
    int featureToAddAtThisLevel = 0;
    int localFeatureToAddAtThisLevel = 0;
    double localAccuracy = 0;
    vector<int> temp;
    if (algorithmInput == 1) // do forward selection
    {
        for (int i = 0; i < dataVector.at(0).dataFeatures.size(); i++)
        {
            featureToAddAtThisLevel = -1;
            localFeatureToAddAtThisLevel = -1;
            localAccuracy = 0;
            for (int k = 0; k < dataVector.at(0).dataFeatures.size(); k++)
            {
                if (find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), k) != currentSetOfFeatures.end()) // if feature exists in vector, skip
                {
                    continue;
                }
                temp = currentSetOfFeatures;
                temp.push_back(k);
                accuracy = nearestNeighbor(dataVector, temp, instances);
                cout << "Using feature(s) ";
                printFeatures(temp);
                cout << "accuracy is " << accuracy << "%\n";
                if (accuracy > bestSoFarAccuracy)
                {
                    bestSoFarAccuracy = accuracy;
                    featureToAddAtThisLevel = k;
                }
                if (accuracy > localAccuracy)
                {
                    localAccuracy = accuracy;
                    localFeatureToAddAtThisLevel = k;
                }
            }
            if (featureToAddAtThisLevel >= 0) // if accuracy is better than bestSoFarAccuracy, updates final vector of features
            {
                currentSetOfFeatures.push_back(featureToAddAtThisLevel);
                finalSetOfFeatures.push_back(featureToAddAtThisLevel);
                cout << "\nFeature set ";
                printFeatures(currentSetOfFeatures);
                cout << "was best, accuracy is " << bestSoFarAccuracy << "%\n\n";
            }
            else // otherwise don't update final vector of features and continue search
            {
                cout << "\n(Warning, accuracy has decreased. Continuing search in case of local maxima)";
                currentSetOfFeatures.push_back(localFeatureToAddAtThisLevel);
                cout << "\nFeature set ";
                printFeatures(currentSetOfFeatures);
                cout << "was best, accuracy is " << localAccuracy << "%\n\n";
            }
            
        }
        cout << "Finished search. The best feature subset is ";
        printFeatures(finalSetOfFeatures);
        cout << "which has an accuracy of " << bestSoFarAccuracy << "%\n";
    }
    else if (algorithmInput == 2)
    {
        for (int cnt = 0; cnt < dataVector.at(0).dataFeatures.size(); cnt++) // fills both vectors with all features
        {
            currentSetOfFeatures.push_back(cnt);
            finalSetOfFeatures.push_back(cnt);
        }
        bestSoFarAccuracy = nearestNeighborAccuracy; // all features should have same starting accuracy as last tested subset in forward selection (from project 2 sample report)
        for (int i = 0; i < dataVector.at(0).dataFeatures.size(); i++)
        {
            featureToAddAtThisLevel = -1;
            localFeatureToAddAtThisLevel = -1;
            localAccuracy = 0;
            for (int k = 0; k < dataVector.at(0).dataFeatures.size(); k++)
            {
                if (find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), k) == currentSetOfFeatures.end()) // if element does not exist in vector, skip
                {
                    continue;
                }
                temp = currentSetOfFeatures;
                temp.erase(find(temp.begin(), temp.end(), k));
                accuracy = nearestNeighbor(dataVector, temp, instances);
                cout << "Using feature(s) ";
                printFeatures(temp);
                cout << "accuracy is " << accuracy << "%\n";
                if (accuracy > bestSoFarAccuracy)
                {
                    bestSoFarAccuracy = accuracy;
                    featureToAddAtThisLevel = k;
                }
                if (accuracy > localAccuracy)
                {
                    localAccuracy = accuracy;
                    localFeatureToAddAtThisLevel = k;
                }
            }
            if (featureToAddAtThisLevel >= 0) // if accuracy is better than bestSoFarAccuracy, updates final vector of features
            {
                currentSetOfFeatures.erase(find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), featureToAddAtThisLevel));
                finalSetOfFeatures.erase(find(finalSetOfFeatures.begin(), finalSetOfFeatures.end(), featureToAddAtThisLevel));
                cout << "\nFeature set ";
                printFeatures(currentSetOfFeatures);
                cout << "was best, accuracy is " << bestSoFarAccuracy << "%\n\n";
            }
            else // otherwise don't update final vector of features and continue search
            {
                cout << "\n(Warning, accuracy has decreased. Continuing search in case of local maxima)";
                currentSetOfFeatures.erase(find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), localFeatureToAddAtThisLevel));
                cout << "\nFeature set ";
                printFeatures(currentSetOfFeatures);
                cout << "was best, accuracy is " << localAccuracy << "%\n\n";
            }
        }
        cout << "Finished search. The best feature subset is ";
        printFeatures(finalSetOfFeatures);
        cout << "which has an accuracy of " << bestSoFarAccuracy << "%\n";
    }
}

/*
* prints out the contents of currentSetOfFeatures with { , } formatting
*/
void printFeatures(vector<int> currentSetOfFeatures)
{
    cout << "{";
    for (int cnt = 0; cnt < currentSetOfFeatures.size(); cnt++)
    {
        if (cnt < currentSetOfFeatures.size() - 1)
        {
            cout << currentSetOfFeatures[cnt] + 1 << ", ";
        }
        else
        {
            cout << currentSetOfFeatures[cnt] + 1;
        }
    }
    cout << "} ";
}