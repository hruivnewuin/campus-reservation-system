#include "Resource.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

        std::stringstream ss(line)
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
    //Linear search, can be replaced with binary search on a sorted vector 
    for (auto& r : resources) {
        if (r.getResourceID() == resourceID) {
            return &r;
        }
    }
    return nullptr;
    
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
