
#include "global.hpp"

/**
 * Sauvegarde le statu dans un fichier
 * @param statusFile nom du fichier où sauvegarder
 * @param mt un pointeur sur le générateur
 */
void save(std::string statusFile, CLHEP::MTwistEngine *mt){
    mt->saveStatus(statusFile.c_str());
}

/**
 * Restaure le statu du générateur depuis un fichier
 * @param statusFile nom du fichier
 * @param mt un pointeur sur le générateur
 */
void restore(std::string statusFile, CLHEP::MTwistEngine *mt){
    mt->restoreStatus(statusFile.c_str());
}

/**
 * Réponse à la question 2
 */
void question2() {
    CLHEP::MTwistEngine *mt = new CLHEP::MTwistEngine();
    std::string statusFile = "./out/MTStatus-Q2.txt";

    save(statusFile, mt);

    std::cout << "Première séquence de 10 nombres :\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << mt->flat() << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
        mt->flat();
    }

    restore(statusFile, mt);

    std::cout << "Deuxième séquence après restauration (doit être identique) :\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << mt->flat() << " ";
    }
    std::cout << std::endl;

    delete mt;
}
