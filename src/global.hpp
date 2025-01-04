#pragma once
#include "CLHEP/Random/MTwistEngine.h"
#include <iostream>
#include <fstream>
#include <omp.h>

void save(std::string statusFile, CLHEP::MTwistEngine *mt);
void restore(std::string statusFile, CLHEP::MTwistEngine *mt);
double calculateSphereVolume(CLHEP::MTwistEngine* mt, long points);
double calculateMean(const std::vector<double>& data);
double calculateVariance(const std::vector<double>& data, double mean);
double calculateStandardDeviation(double variance);
std::pair<double, double> calculateConfidenceInterval(double mean, double standardDeviation, double dataSize);
std::string getStatusFileName(int replicationIndex);
void runSimulation(const int replicationIndex, const long pointsPerReplication);

void question2();
void question3();
void question4();
void question5();
void question5Bis(std::string file);
void question6();