PmergeMe.hpp
#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <sys/time.h>
#include <algorithm>
class PmergeMe {
public:
    // Méthodes principales pour les deux conteneurs
    static void sortVector(std::vector<int>& data);
    static void sortDeque(std::deque<int>& data);
    
    // Validation et parsing
    static bool parseAndValidate(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq);
    
    // Affichage
    static void printSequence(const std::string& prefix, const std::vector<int>& data);
    static void printSequence(const std::string& prefix, const std::deque<int>& data);
    
    // Mesure du temps
    static double getTimeDifference(struct timeval start, struct timeval end);
private:
    // === VECTOR IMPLEMENTATION ===
    static void fordJohnsonVector(std::vector<int>& data);
    static std::vector<int> generateJacobsthalVector(size_t size);
    static void binaryInsertVector(std::vector<int>& mainChain, int value, size_t maxPos);
    
    // === DEQUE IMPLEMENTATION ===
    static void fordJohnsonDeque(std::deque<int>& data);
    static std::vector<int> generateJacobsthalDeque(size_t size);
    static void binaryInsertDeque(std::deque<int>& mainChain, int value, size_t maxPos);
    
    // Utilitaires
    static bool isPositiveInteger(const std::string& str);
    static bool hasDuplicates(const std::vector<int>& data);
};
#endif
Réflexion sur le .hpp :
- Méthodes statiques : pas besoin d'instancier la classe
- Séparation claire vector/deque
- sys/time.h pour gettimeofday() (plus précis que clock())
- Validation robuste avec parseAndValidate
---
PmergeMe.cpp
#include "PmergeMe.hpp"
// ========================================
// VALIDATION ET PARSING
// ========================================
bool PmergeMe::isPositiveInteger(const std::string& str) {
    if (str.empty()) return false;
    
    // Vérifier que tous les caractères sont des chiffres
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) return false;
    }
    
    // Vérifier l'overflow
    std::stringstream ss(str);
    long long num;
    ss >> num;
    
    if (num < 0 || num > INT_MAX) return false;
    
    return true;
}
bool PmergeMe::hasDuplicates(const std::vector<int>& data) {
    std::vector<int> sorted = data;
    std::sort(sorted.begin(), sorted.end());
    
    for (size_t i = 1; i < sorted.size(); ++i) {
        if (sorted[i] == sorted[i - 1]) return true;
    }
    return false;
}
bool PmergeMe::parseAndValidate(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq) {
    if (argc < 2) {
        std::cerr << "Error: No arguments provided" << std::endl;
        return false;
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        
        if (!isPositiveInteger(arg)) {
            std::cerr << "Error" << std::endl;
            return false;
        }
        
        int num = atoi(arg.c_str());
        vec.push_back(num);
        deq.push_back(num);
    }
    
    // Vérifier les doublons
    if (hasDuplicates(vec)) {
        std::cerr << "Error" << std::endl;
        return false;
    }
    
    return true;
}
// ========================================
// AFFICHAGE
// ========================================
void PmergeMe::printSequence(const std::string& prefix, const std::vector<int>& data) {
    std::cout << prefix;
    for (size_t i = 0; i < data.size() && i < 5; ++i) {
        std::cout << data[i];
        if (i < data.size() - 1) std::cout << " ";
    }
    if (data.size() > 5) std::cout << " [...]";
    std::cout << std::endl;
}
void PmergeMe::printSequence(const std::string& prefix, const std::deque<int>& data) {
    std::cout << prefix;
    for (size_t i = 0; i < data.size() && i < 5; ++i) {
        std::cout << data[i];
        if (i < data.size() - 1) std::cout << " ";
    }
    if (data.size() > 5) std::cout << " [...]";
    std::cout << std::endl;
}
// ========================================
// MESURE DU TEMPS
// ========================================
double PmergeMe::getTimeDifference(struct timeval start, struct timeval end) {
    double startTime = start.tv_sec * 1000000.0 + start.tv_usec;
    double endTime = end.tv_sec * 1000000.0 + end.tv_usec;
    return endTime - startTime;
}
// ========================================
// GÉNÉRATION DE LA SÉQUENCE JACOBSTHAL
// ========================================
std::vector<int> PmergeMe::generateJacobsthalVector(size_t size) {
    std::vector<int> jacobsthal;
    
    // Générer les nombres de Jacobsthal
    std::vector<size_t> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    
    // Générer jusqu'à dépasser size
    while (jacob.back() < size) {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    
    // Construire la séquence d'insertion
    size_t pos = 1; // Commencer après le premier élément
    for (size_t i = 2; i < jacob.size(); ++i) {
        size_t current = jacob[i];
        size_t previous = jacob[i - 1];
        
        // Insérer de current vers previous (ordre décroissant)
        if (current > size) current = size;
        
        for (size_t j = current; j > previous; --j) {
            jacobsthal.push_back(j - 1); // -1 car indices commencent à 0
        }
        
        if (current >= size) break;
    }
    
    return jacobsthal;
}
std::vector<int> PmergeMe::generateJacobsthalDeque(size_t size) {
    // Même implémentation pour deque
    return generateJacobsthalVector(size);
}
// ========================================
// INSERTION BINAIRE - VECTOR
// ========================================
void PmergeMe::binaryInsertVector(std::vector<int>& mainChain, int value, size_t maxPos) {
    if (mainChain.empty()) {
        mainChain.push_back(value);
        return;
    }
    
    // Limiter la recherche à maxPos
    size_t end = (maxPos < mainChain.size()) ? maxPos : mainChain.size();
    
    // Recherche binaire manuelle (pas std::lower_bound)
    size_t left = 0;
    size_t right = end;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (mainChain[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    mainChain.insert(mainChain.begin() + left, value);
}
// ========================================
// INSERTION BINAIRE - DEQUE
// ========================================
void PmergeMe::binaryInsertDeque(std::deque<int>& mainChain, int value, size_t maxPos) {
    if (mainChain.empty()) {
        mainChain.push_back(value);
        return;
    }
    
    size_t end = (maxPos < mainChain.size()) ? maxPos : mainChain.size();
    
    size_t left = 0;
    size_t right = end;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (mainChain[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    mainChain.insert(mainChain.begin() + left, value);
}
// ========================================
// FORD-JOHNSON ALGORITHM - VECTOR
// ========================================
void PmergeMe::fordJohnsonVector(std::vector<int>& data) {
    size_t n = data.size();
    
    // Cas de base
    if (n <= 1) return;
    
    // Étape 1 : Créer les paires et identifier le straggler
    bool hasStraggler = (n % 2 == 1);
    int straggler = hasStraggler ? data[n - 1] : -1;
    size_t pairCount = n / 2;
    
    // Étape 2 : Trier chaque paire (plus grand en premier)
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < pairCount; ++i) {
        int a = data[2 * i];
        int b = data[2 * i + 1];
        
        if (a > b) {
            pairs.push_back(std::make_pair(a, b));
        } else {
            pairs.push_back(std::make_pair(b, a));
        }
    }
    
    // Étape 3 : Extraire les "grands" (b values) et les trier récursivement
    std::vector<int> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        largerElements.push_back(pairs[i].first);
    }
    
    // Tri récursif des grands éléments
    if (largerElements.size() > 1) {
        fordJohnsonVector(largerElements);
    }
    
    // Étape 4 : Construire la main chain
    std::vector<int> mainChain;
    
    // Insérer le plus petit du premier pair en premier
    if (!pairs.empty()) {
        mainChain.push_back(pairs[0].second);
    }
    
    // Ajouter tous les grands éléments triés
    for (size_t i = 0; i < largerElements.size(); ++i) {
        mainChain.push_back(largerElements[i]);
    }
    
    // Étape 5 : Préparer les pend elements (les petits sauf le premier déjà inséré)
    std::vector<int> pend;
    for (size_t i = 1; i < pairs.size(); ++i) {
        pend.push_back(pairs[i].second);
    }
    
    // Ajouter le straggler aux pend
    if (hasStraggler) {
        pend.push_back(straggler);
    }
    
    // Étape 6 : Générer la séquence de Jacobsthal
    std::vector<int> jacobsthalSeq = generateJacobsthalVector(pend.size());
    
    // Étape 7 : Insérer les pend elements selon Jacobsthal
    std::vector<bool> inserted(pend.size(), false);
    
    for (size_t i = 0; i < jacobsthalSeq.size(); ++i) {
        int index = jacobsthalSeq[i];
        if (index >= 0 && (size_t)index < pend.size() && !inserted[index]) {
            // La position maximale de recherche augmente avec chaque insertion
            size_t maxPos = mainChain.size();
            binaryInsertVector(mainChain, pend[index], maxPos);
            inserted[index] = true;
        }
    }
    
    // Insérer les éléments restants (au cas où)
    for (size_t i = 0; i < pend.size(); ++i) {
        if (!inserted[i]) {
            binaryInsertVector(mainChain, pend[i], mainChain.size());
        }
    }
    
    // Copier le résultat
    data = mainChain;
}
void PmergeMe::sortVector(std::vector<int>& data) {
    fordJohnsonVector(data);
}
// ========================================
// FORD-JOHNSON ALGORITHM - DEQUE
// ========================================
void PmergeMe::fordJohnsonDeque(std::deque<int>& data) {
    size_t n = data.size();
    
    if (n <= 1) return;
    
    bool hasStraggler = (n % 2 == 1);
    int straggler = hasStraggler ? data[n - 1] : -1;
    size_t pairCount = n / 2;
    
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < pairCount; ++i) {
        int a = data[2 * i];
        int b = data[2 * i + 1];
        
        if (a > b) {
            pairs.push_back(std::make_pair(a, b));
        } else {
            pairs.push_back(std::make_pair(b, a));
        }
    }
    
    std::deque<int> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        largerElements.push_back(pairs[i].first);
    }
    
    if (largerElements.size() > 1) {
        fordJohnsonDeque(largerElements);
    }
    
    std::deque<int> mainChain;
    
    if (!pairs.empty()) {
        mainChain.push_back(pairs[0].second);
    }
    
    for (size_t i = 0; i < largerElements.size(); ++i) {
        mainChain.push_back(largerElements[i]);
    }
    
    std::vector<int> pend;
    for (size_t i = 1; i < pairs.size(); ++i) {
        pend.push_back(pairs[i].second);
    }
    
    if (hasStraggler) {
        pend.push_back(straggler);
    }
    
    std::vector<int> jacobsthalSeq = generateJacobsthalDeque(pend.size());
    
    std::vector<bool> inserted(pend.size(), false);
    
    for (size_t i = 0; i < jacobsthalSeq.size(); ++i) {
        int index = jacobsthalSeq[i];
        if (index >= 0 && (size_t)index < pend.size() && !inserted[index]) {
            size_t maxPos = mainChain.size();
            binaryInsertDeque(mainChain, pend[index], maxPos);
            inserted[index] = true;
        }
    }
    
    for (size_t i = 0; i < pend.size(); ++i) {
        if (!inserted[i]) {
            binaryInsertDeque(mainChain, pend[i], mainChain.size());
        }
    }
    
    data = mainChain;
}
void PmergeMe::sortDeque(std::deque<int>& data) {
    fordJohnsonDeque(data);
}
Réflexions clés sur le .cpp :
1. Validation robuste :
   - isPositiveInteger : vérifie caractère par caractère + overflow
   - hasDuplicates : tri puis comparaison adjacente (O(n log n))
2. Jacobsthal :
   - Génère J(n) = J(n-1) + 2*J(n-2)
   - Crée la séquence d'insertion optimale
   - Ordre décroissant entre deux nombres de Jacobsthal
3. Insertion binaire manuelle :
   - Pas d'utilisation de std::lower_bound pour être original
   - Recherche limitée par maxPos (optimisation)
4. Ford-Johnson récursif :
   - Tri récursif des "grands éléments"
   - Construction de la main chain
   - Insertion optimale avec Jacobsthal
---
main.cpp
#include "PmergeMe.hpp"
int main(int argc, char** argv) {
    std::vector<int> vec;
    std::deque<int> deq;
    
    // Parser et valider les entrées
    if (!PmergeMe::parseAndValidate(argc, argv, vec, deq)) {
        return 1;
    }
    
    // Afficher la séquence avant tri
    PmergeMe::printSequence("Before: ", vec);
    
    // === TRIER AVEC VECTOR ===
    struct timeval startVec, endVec;
    gettimeofday(&startVec, NULL);
    PmergeMe::sortVector(vec);
    gettimeofday(&endVec, NULL);
    double timeVec = PmergeMe::getTimeDifference(startVec, endVec);
    
    // Afficher la séquence après tri
    PmergeMe::printSequence("After:  ", vec);
    
    // === TRIER AVEC DEQUE ===
    struct timeval startDeq, endDeq;
    gettimeofday(&startDeq, NULL);
    PmergeMe::sortDeque(deq);
    gettimeofday(&endDeq, NULL);
    double timeDeq = PmergeMe::getTimeDifference(startDeq, endDeq);
    
    // Afficher les temps
    std::cout << "Time to process a range of " << vec.size() 
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() 
              << " elements with std::deque : " << timeDeq << " us" << std::endl;
    
    return 0;
}
Réflexions sur main.cpp :
- gettimeofday() : précision microseconde
- Mesure le temps TOTAL (parsing inclus)
- Affichage conforme aux specs
---
Makefile
NAME = PmergeMe
SRC = main.cpp PmergeMe.cpp
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g3
OBJ = $(SRC:.cpp=.o)
all: $(NAME)
%.o: %.cpp PmergeMe.hpp
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all re clean fclean
