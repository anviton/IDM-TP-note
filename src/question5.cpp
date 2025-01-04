#include <cmath>
#include <chrono>
#include <thread>

#include "global.hpp"

/**
 * Fonction qui retourne le chemin correcte du statu du générateur
 * relatif à une réplication 
 * @param replicationIndex index de la réplication
 * @return chemin correcte du statu du générateur
 */
std::string getStatusFileName(int replicationIndex) {
    return "./out/MTStatus-Q3-" + std::to_string(replicationIndex+1);
}


/**
 * Fonction exécutée par chaque thread qui représente une simulation
 * @param replicationIndex index de la réplication
 * @param pointsPerReplication nombre de points par réplication
 */
void runSimulation(const int replicationIndex, const long pointsPerReplication) {
    std::string statusFile = getStatusFileName(replicationIndex);

    CLHEP::MTwistEngine *mt = new CLHEP::MTwistEngine();
    restore(statusFile, mt);
    #pragma omp critical
    {
        std::cout << "Réplication " << replicationIndex + 1 << ": calcul...\n";
    }
    double volume = calculateSphereVolume(mt, pointsPerReplication);

    #pragma omp critical
    {
        std::cout << "Réplication " << replicationIndex + 1 << ": Volume estimé : " << volume << "\n";
    }

    std::ofstream fichierSortie("./res/volume_sphere-Q5-"+std::to_string(replicationIndex+1));
    if (fichierSortie.is_open()) {
        fichierSortie << std::fixed << std::setprecision(10);
        fichierSortie << volume << std::endl;
        fichierSortie.close();
    } else {
        #pragma omp critical
        {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier pour écrire." << std::endl;
        }
    }
    delete mt;
}


/**
 * Réponse à la question 5 
 */
void question5() {
    const int numReplications = 10;
    const long pointsPerReplication = 1'000'000'000;

    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numReplications; ++i) {
        threads.emplace_back(runSimulation, i, pointsPerReplication);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Toutes les réplications sont terminées.\n";

    std::ifstream file;
    double volume = 0.0;
    double mean;
    double variance;
    double standardDeviation;
    std::vector<double> data;
    std::pair<double, double> confidenceInterval;

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
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Ecart type : " << standardDeviation << std::endl;
    std::cout << "Intervalle de confiance à 95% : [" << confidenceInterval.first << " - " <<
    confidenceInterval.second << "]" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Temps total pour 10 réplications : " << elapsed.count() << " secondes\n";

}

/**
 * Réponse à la question 5 (parallélisation grâce à un script bash)
 * @param file chemin pour du fichier qui va permettre de restaurer le statu du générateur
 */
void question5Bis(std::string file)
{
    CLHEP::MTwistEngine *mt = new CLHEP::MTwistEngine();
    std::cout << file << std::endl;
    restore(file, mt);
    double volume = calculateSphereVolume(mt, 1'000'000'000);
    std::cout << "Volume = " << volume << std::endl;
    delete mt;
}
