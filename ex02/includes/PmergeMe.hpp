#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <ctime>
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
    static double getTimeDifference(clock_t start, clock_t end);

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
