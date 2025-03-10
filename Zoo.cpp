#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

// Making Base Animal class, encapsulation.
class Animal {
protected:
    std::string name;
    int age;
    std::string species;
    
public:
    // Constructor
    Animal(const std::string& n, int a, const std::string& s) : name(n), age(a), species(s) {}
    
    // Virtual destructor for proper cleanup
    virtual ~Animal() {}
    
    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getSpecies() const { return species; }
    
    // Setters
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setSpecies(const std::string& s) { species = s; }
    
    // Virtual method for polymorphism
    virtual void makeSound() const {
        std::cout << "Animal makes a sound" << std::endl;
    }
};

// Hyena subclass, Inheritance
class Hyena : public Animal {
public:
    Hyena(const std::string& name, int age) : Animal(name, age, "Hyena") {}
    
    // Override makeSound for polymorphism
    void makeSound() const {
        std::cout << getName() << " laughs hysterically" << std::endl;
    }
};

// Lion subclass
class Lion : public Animal {
public:
    Lion(const std::string& name, int age) : Animal(name, age, "Lion") {}
    
    void makeSound() const {
        std::cout << getName() << " roars majestically" << std::endl;
    }
};

// Tiger subclass
class Tiger : public Animal {
public:
    Tiger(const std::string& name, int age) : Animal(name, age, "Tiger") {}
    
    void makeSound() const {
        std::cout << getName() << " growls fiercely" << std::endl;
    }
};

// Bear subclass
class Bear : public Animal {
public:
    Bear(const std::string& name, int age) : Animal(name, age, "Bear") {}
    
    void makeSound() const {
        std::cout << getName() << " grunts loudly" << std::endl;
    }
};

int main() {
    std::vector<Animal*> animals;
    std::map<std::string, int> speciesCount;
    
    // Open input file, took way too long to figure out how files work, Loops
    std::ifstream inFile("arrivingAnimals.txt");
    if (!inFile) {
        std::cout << "Error opening input file" << std::endl;//Just in case the file doesn't open, Recommended to put in by chat GPT
        return 1;
    }
    
    std::string line;
    while (getline(inFile, line)) {
        int age = 0;
        std::string species = "";
        
        // Parse age from the beginning of the linerecommended by Copilot to make the code smaller, to my understanding instead of going through every line to find all of the necessary information it just scans the beginning of each line to find the age of the animal.
        if (isdigit(line[0])) {
            age = atoi(line.c_str());
        }
        
        // Find species in the line
        if (line.find("hyena") != std::string::npos) {
            species = "Hyena";
        } else if (line.find("lion") != std::string::npos) {
            species = "Lion";
        } else if (line.find("tiger") != std::string::npos) {
            species = "Tiger";
        } else if (line.find("bear") != std::string::npos) {
            species = "Bear";
        }
        
        if (!species.empty()) {
            // Generate a simple name, I did the second line by myself but it kept resulting in every animal having a _0 after its name so chatgpt said that I only needed to add the first line to make it work, I completely forgot that ++ increases things by 1
            speciesCount[species]++;
            std::string name = species + std::string("_") + std::string(1, '0' + speciesCount[species]);
            
            // Create appropriate animal subclass
            Animal* animal = NULL;
            if (species == "Hyena") {
                animal = new Hyena(name, age);
            } else if (species == "Lion") {
                animal = new Lion(name, age);
            } else if (species == "Tiger") {
                animal = new Tiger(name, age);
            } else if (species == "Bear") {
                animal = new Bear(name, age);
            }
            
            if (animal) {
                animals.push_back(animal);
            }
        }
    }
    
    inFile.close();
    
    // Write to output file
    std::ofstream outFile("newAnimals.txt");
    if (!outFile) {
        std::cout << "Error opening output file" << std::endl;
        return 1;
    }

    // Write animal data by species
    std::map<std::string, int>::iterator it;
    for (it = speciesCount.begin(); it != speciesCount.end(); ++it) {
        std::cout << it->first << "s:" << std::endl;
        
        for (size_t i = 0; i < animals.size(); i++) {
            if (animals[i]->getSpecies() == it->first) {
                outFile << "  - " << animals[i]->getName() << ", Age: " << animals[i]->getAge() << std::endl;
            }
        }
        
        outFile << "Total " << it->first << "s: " << it->second << std::endl << std::endl;
    }
    
    outFile.close();
    
    std::cout << "Animal report generated successfully!" << std::endl;
    
    // Demonstrate polymorphism by having each animal make its sound
    std::cout << "\nAnimal sounds:" << std::endl;
    for (size_t i = 0; i < animals.size(); i++) {
        animals[i]->makeSound();
    }
    
    
    return 0;
}