#include "global.hpp"
#include <locale>

/**
 * Fonction qui sauvegarde plusieurs status d'un générateur avec comme paramètre
 * nombre de status et le nombre de tirage entre chaque status
 * @param nbDraw nombre de tirages entre chaque sauvegarde
 * @param nbStatus nombre de status à sauvegarder
 */
void saveStatusWithParameter(long nbDraw, int nbStatus){
    CLHEP::MTwistEngine *mt = new CLHEP::MTwistEngine();
    std::string statusFile = "./out/MTStatus-Q3-"; 
    
    for (int i = 0; i < nbStatus; ++i) {
        save(statusFile+std::to_string(i+1), mt);
        std::cout << "Sauvegarde - " << i+1 << std::endl;
        for (long j = 0; j < nbDraw; ++j) {
            //std::cout << mt->flat() << " ";
            //std::cout << j << std::endl;
            mt->flat();
        }
    }
}

/**
 * Réponse à la question 3
 * Sauvegarde de 10 status espacés de 3 miliard de tirages
 */
void question3(){
    saveStatusWithParameter(3'000'000'000, 10);
}