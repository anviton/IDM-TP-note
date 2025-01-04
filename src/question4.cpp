#include <cmath>
#include <chrono>

#include "global.hpp"

/**
 * Fonction pour calculer le volume d'une sphère de rayon 1 par Monte Carlo
 * @param mt un pointeur sur le générateur
 * @param points nombre de points de la simulation
 * @return le volume de la shère calculé lors d'une simulation
 */
double calculateSphereVolume(CLHEP::MTwistEngine* mt, long points) {
    double inside = 0;

    for (long i = 0; i < points; ++i) {
        double x = mt->flat();
        double y = mt->flat();
        double z = mt->flat();

        if (x * x + y * y + z * z <= 1.0) {
            ++inside;
        }
    }

    return 8.0 * inside / points;
}

/**
 * Fonction pour calculer la moyenne
 * @param data contient les données calculées
 * @return la moyenne
 */
double calculateMean(const std::vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

/**
 * Fonction pour calculer la variance
 * @param data contient les données calculées
 * @param mean moyenne de la série de données
 * @return la variance calculée
 */
double calculateVariance(const std::vector<double>& data, double mean) {
    double sumOfSquares = 0.0;
    double n = static_cast<double>(data.size());

    for (double value : data) {
        sumOfSquares = sumOfSquares + ((value - mean) * (value - mean));
    }

    return sumOfSquares / n;
}

/**
 * Fonction pour calculer l'écart type
 * @param variance la variance de la série de données
 * @return l'écart type
 */
double calculateStandardDeviation(double variance) {
    return std::sqrt(variance);
}

/**
 * Fonction pour calculer un intervalle de confiance à 95%
 * @param mean moyenne  de la série de données
 * @param standardDeviation écart type de la série de données
 * @param dataSize taille de la série de données
 * @return une paire contenant la borne inf et sup de l'intervalle de confiance à 95%
 */
std::pair<double, double> calculateConfidenceInterval(double mean, double standardDeviation, double dataSize) {
    double n = static_cast<double>(dataSize);
    double coef = 1.96;

    double margin = coef * (standardDeviation / std::sqrt(n));

    return {mean - margin, mean + margin};
}

/**
 * Réponse à la question 4
 * Exécution de 10 réplications de manière séquentielle avec 1 milliard de points par réplications
 */
void question4() {
    const int numReplications = 10;
    const long pointsPerReplication = 1'000'000'000;
    CLHEP::MTwistEngine *mt = new CLHEP::MTwistEngine();
    std::string statusFile = "./out/MTStatus-Q3-";
    std::vector<double> data;
    double volume;
    double mean;
    double variance;
    double standardDeviation;
    std::pair<double, double> confidenceInterval;
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numReplications; ++i) {
        restore(statusFile+std::to_string(i+1), mt);
        
        std::cout << "Réplication " << i + 1 << ": Calcul du volume de la sphère...\n";
        volume = calculateSphereVolume(mt, pointsPerReplication);
        data.push_back(volume);
        std::cout << "Volume estimé : " << volume << "\n";
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

    std::cout << "Temps total pour 10 réplications : " << elapsed.count() << " secondes\n";
    delete mt;
}