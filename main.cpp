﻿#include <iostream>
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

    auto start_time = chrono::high_resolution_clock::now();
    

    /*cout << "Welcome to Nicholas's Feature Selection Algorithm.\n";
    cout << "Type in the name of file to test : ";
    cin >> fileName;
    cout << "\nType the number of the algorithm you want to run.\n";
    cout << "1) Forward Selection\n";
    cout << "2) Backward Elimination\n";
    cin >> algorithmInput;
    ifstream dataFile(fileName);*/

    ifstream dataFile("CS170_Small_Data__103.txt"); // my small data
    //ifstream dataFile("CS170_Large_Data__74.txt"); // my large data
    
    // Sue
    //ifstream dataFile("sueCS170_Small_Data__96.txt"); // On small dataset 96 the error rate can be 0.94 when using only features 1 3 6;
    //ifstream dataFile("sueCS170_Large_Data__21.txt"); // On large dataset 21 the error rate can be 0.947 when using only features 37 36 40

    // Joe
    //ifstream dataFile("joeCS170_Small_Data__6.txt"); // On small dataset 6 the error rate can be 0.916 when using only features 2 5 3; 
    //ifstream dataFile("joeCS170_Large_Data__96.txt"); // On large dataset 96 the error rate can be 0.947 when using only features 21 8 10
    
    // Van
    //ifstream dataFile("vanCS170_Small_Data__88.txt"); // van data On small dataset 88 the error rate can be 0.936 when using only features 5 2 1; 
    //ifstream dataFile("vanCS170_Large_Data__6.txt"); // On large dataset 6 the error rate can be 0.954 when using only features 22 1 6

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
    double accuracy = nearestNeighbor(dataVector, currentSetOfFeatures, instances);
    cout << "Running nearest neighbor with all " << column << " features, using 'leaving-one-out' evaluation, I get an accuracy of " << accuracy << "%\n\n";
    cout << "Beginning search.\n\n";
    //searchAlgorithm(algorithmInput, dataVector, instances, accuracy);
    
    //searchAlgorithm(1, dataVector, instances, accuracy);
    searchAlgorithm(2, dataVector, instances, accuracy);

    auto current_time = chrono::high_resolution_clock::now();
    cout << "\nProgram has been running for " << chrono::duration_cast<chrono::seconds>(current_time - start_time).count() << " seconds";
    return 0;
}

double nearestNeighbor(vector<datasetPoint> dataVector, vector<int> currentSetOfFeatures, int instances)
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
            //cout << "On the " << i + 1 << "th level of the search tree\n";
            featureToAddAtThisLevel = -1;
            localFeatureToAddAtThisLevel = -1;
            localAccuracy = 0;
            for (int k = 0; k < dataVector.at(0).dataFeatures.size(); k++)
            {
                if (find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), k) != currentSetOfFeatures.end())
                {
                    continue;
                }
                //cout << "--Considering adding the " << k + 1 << " feature\n";
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
            if (featureToAddAtThisLevel >= 0)
            {
                currentSetOfFeatures.push_back(featureToAddAtThisLevel);
                finalSetOfFeatures.push_back(featureToAddAtThisLevel);
                cout << "\nFeature set ";
                printFeatures(currentSetOfFeatures);
                cout << "was best, accuracy is " << bestSoFarAccuracy << "%\n\n";
            }
            else
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
        for (int cnt = 0; cnt < dataVector.at(0).dataFeatures.size(); cnt++)
        {
            currentSetOfFeatures.push_back(cnt);
            finalSetOfFeatures.push_back(cnt);
        }
        bestSoFarAccuracy = nearestNeighborAccuracy;
        for (int i = 0; i < dataVector.at(0).dataFeatures.size(); i++)
        {
            featureToAddAtThisLevel = -1;
            localFeatureToAddAtThisLevel = -1;
            localAccuracy = 0;
            for (int k = 0; k < dataVector.at(0).dataFeatures.size(); k++)
            {
                if (find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), k) == currentSetOfFeatures.end())
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
            if (featureToAddAtThisLevel >= 0)
            {
                currentSetOfFeatures.erase(find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), featureToAddAtThisLevel));
                finalSetOfFeatures.erase(find(finalSetOfFeatures.begin(), finalSetOfFeatures.end(), featureToAddAtThisLevel));
                cout << "\nFeature set ";
                printFeatures(currentSetOfFeatures);
                cout << "was best, accuracy is " << bestSoFarAccuracy << "%\n\n";
            }
            else
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