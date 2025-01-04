#include <chrono>

#include "global.hpp"

/**
 * Réponse à la question bonus 6.a
 */
void question6() {
    const int numReplications = 10;
    const long pointsPerReplication = 1'000'000'000;
    std::vector<double> data;
    std::ifstream file;
    double volume = 0.0;
    double mean;
    double variance;
    double standardDeviation;
    std::pair<double, double> confidenceInterval;

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < numReplications; ++i) {
        runSimulation(i, pointsPerReplication);
    }
    std::cout << "Toutes les réplications sont terminées.\n";

    for (int i = 0; i < numReplications; ++i) {
        file.open("./res/volume_sphere-Q5-"+std::to_string(i+1));
        if (file.is_open()) {
            file >> volume;
            data.push_back(volume);
            file.close();
        } else {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier '" << std::endl;
        }
    }

    mean = calculateMean(data);
    variance = calculateVariance(data, mean);
    standardDeviation = calculateStandardDeviation(variance);
    confidenceInterval = calculateConfidenceInterval(mean, standardDeviation, data.size());
    
    std::cout << std::endl << "Volume moyen sur les 10 réplications : " << mean << std::endl;
    std::cout << "Variance : " << variance << std::endl;
    std::cout << "Ecart type : " << standardDeviation << std::endl;
    std::cout << "Intervalle de confiance à 95% : [" << confidenceInterval.first << " - " <<
    confidenceInterval.second << "]" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Temps total pour 10 réplications avec OpenMP : " << elapsed.count() << " secondes\n";
}