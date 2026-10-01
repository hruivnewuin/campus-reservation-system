#include "Resource.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

Resource::Resource() : resourceID(""), resourceName(""), resourceType(""), available(true) {}

Resource::Resource(const std::string& id, const std::string& name, const std::string& type, bool isAvailable) : resourceID(id), resourceName(name), resourceType(type), available(isAvailable) {}

std::string Resource::getResourceID() const { return resourceID; }
std::string Resource::getResourceName() const { return resourceName; }
std::string Resource::getResourceType() const { return resourceType; }
bool Resource::isAvailable() const { return available; }

void Resource::setResourceID(const std::string& id) { resourceID = id; }
void Resource::setResourceName(const std::string& name) { resourceName = name; }
void Resource::setResourceType(const std::string& type) { resourceType = type; }
void Resource::setAvailable(bool isAvailable) { available = isAvailable; }

void Resource::display() const {
    std::cout << "ID: " << resourceID << " | Name: " << resourceName << " | Type: " << resourceType << " | Available: " << (available ? "Yes" : "No") << std::endl;
}

ResourceManager::ResourceManager() {}

//Expected file format is pipe delimited

bool ResourceManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(inFile, line)) {

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, name, type, availStr;

        if (!std::getline(ss, id, '|')) continue;
        if (!std::getline(ss, name, '|')) continue;
        if (!std::getline(ss, type, '|')) continue;
        if (!std::getline(ss, availStr, '|')) continue;

        bool avail = (availStr == "Available");
        resources.push_back(Resource(id, name, type, avail));
    }

    inFile.close();
    return true;
}

bool ResourceManager::addResource(const Resource& resource) {
    resources.push_back(resource);
    return true;
}

void ResourceManager::displayAllResources() const {
    if (resources.empty()) {
        std::cout << "No resources loaded." << std::endl;
        return;
    }
    for (const auto& r : resources) {
        r.display();
    }

}

void ResourceManager::displayAvailability() const {
    bool foundAny = false;
    for (const auto& r : resources) {
        if (r.isAvailable()) {
            r.display();
            foundAny = true;
        }

    }
    if (!foundAny) {
        std::cout << "No resources are currently available." << std::endl;

    }
}

Resource* ResourceManager::findResourceByID(const std::string& resourceID) {
    //Linear search (note: can switch out with binary search on sorted vector)
    for (auto& r : resources) {
        if (r.getResourceID() == resourceID) {
            return &r;
        }
    }
    return nullptr;
    
}

//Binary Search, Precondition is that resources must already be sorted by ID (call sortResourcesByID() first)
//Repeatedly halves the search range by comparing the middle element's ID to the target, narrowing to the left or right half each time.
//The time complexity: O(log n)
Resource* ResourceManager::searchResourceByID(const std::string& resourceID) {
    int low = 0;
    int high = static_cast<int>(resources.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; //avoids overflow vs (low+high)/2

        if (resources[mid].getResourcesID() == resourceID) {
            return &resources[mid];
        }
        else if (resources[mid].getResourcesID() < resourceID) {
            low = mid + 1; //target is in the right half
        }
        else {
            high = mid - 1; //target is in the left half
        }
    }
    return nullptr; //not found
}

//Quick Sort - Picks the middle element as the pivot rather than teh first/last.
//A first/last element will degrade to O(n^2) on already sorted data and reverse sorted data
//So the middle element pivot keeps average case O(n log n) behavior on the data instead of taking the worst case every time
//Time complexity: O(n log n) if its average but O(n^2) on worst case
int ResourceManager::partition(std::vector<Resource>& vec, int low, int high, bool byID) {
    int midIndex = low + (high - low) / 2;
    std::string pivotKey = byID ? vec[midIndex].getResourceID() : vec[midIndex].getResourceName();

    int i = low;
    int j = high;
    while (i <= j) {
        while ((byID ? vec[i].getResourceID() : vec[i].getResourceName()) < pivotKey) {
            i++;
        }
        while ((byID ? vec[j].getResourceID() : vec[j].getResourceName()) > pivotKey) {
            j--;
        }
        if (i <= j) {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }
    return i; //split point for the next recursive calls
}

void ResourceManager::quickSort(std::vector<Resource>& vec, int low, int high, bool byID) {
    if (low < high) {
        int splitIndex = partition(vec, low, high, byID);
        quickSort(vec, low, splitIndex - 1, byID);
        quickSort(vec, splitIndex, high, byID);
    }
}

void ResourceManager::sortResourcesByID() {
    if (resources.empty()) return;
    quickSort(resources, 0, static_cast<int>(resources.size()) - 1, true);
}
void ResourceManager::sortResourcesByName() {
    if (resources.empty()) return;
    quickSort(resources, 0, static_cast<int>(resources.size()) - 1, false);
}


bool ResourceManager::setResourceAvailability(const std::string& resourceID, bool isAvailable) {

    Resource* r = findResourceByID(resourceID);
    if (r == nullptr) return false;
    r->setAvailable(isAvailable);
    return true;
}

int ResourceManager::getResourceCount() const {
    return static_cast<int>(resources.size());
}

const std::vector<Resource>& ResourceManager::getAllResources() const {
    return resources;
}
