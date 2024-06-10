#pragma once

#include "./ModelH/Observable.h" // Include necessary header files
#include "./ModelH/Observer.h"
#include "./ModelH/HallOfFame.h"

// HofController class declaration, inheriting from Observable and Observer
class HofController : public Observable, public Observer {
public:
    // Constructor
    HofController();
    
    // Destructor
    ~HofController();

    // Method to read data from a text file
    void readTxtFile();
    
    // Method to write data to a text file
    void writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel);
    
    // Method to sort data by difficulty level
    void sortDataByDifficulty(int difficultyReceived);
    
    // Method to get the top three sorted data
    void topThreeSortedData(int difficultyReceived);
    
    // Method to get sorted data from HallOfFame
    vector<Data> getSortedDataFoh() const;
    
    // Observer update method
    void update() override;

private:
    HallOfFame hallOfFame; // Instance of HallOfFame
};