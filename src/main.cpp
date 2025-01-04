#include "global.hpp"

int main(int argc, const char *argv[]){
    if(argc >= 2){
        int select = atoi(argv[1]);
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "Réponse question " << select << " :" << std::endl;
        switch (select)
        {
            case 2 :
                question2();
                break;
            case 3 :
                question3();
                break;
            case 4 :
                question4();
                break;
            case 5 :
                if (argc == 3)
                    question5Bis(argv[2]);
                else
                    question5();
                break;
            case 6 :
                question6();
                break;
            default:
                std::cout << "Valeur incorrecte" << std::endl;
                break;
        }
    }
    else
        std::cout << "Paramètre manquant" << std::endl;
    return 0;
}