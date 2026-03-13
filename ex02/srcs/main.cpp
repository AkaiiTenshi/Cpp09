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
    clock_t startVec = clock();
    PmergeMe::sortVector(vec);
    clock_t endVec = clock();
    double timeVec = PmergeMe::getTimeDifference(startVec, endVec);
    
    // Afficher la séquence après tri
    PmergeMe::printSequence("After:  ", vec);
    
    // === TRIER AVEC DEQUE ===
    clock_t startDeq = clock();
    PmergeMe::sortDeque(deq);
    clock_t endDeq = clock();
    double timeDeq = PmergeMe::getTimeDifference(startDeq, endDeq);
    
    // Afficher les temps
    std::cout << "Time to process a range of " << vec.size() 
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() 
              << " elements with std::deque : " << timeDeq << " us" << std::endl;
    
    return 0;
}
