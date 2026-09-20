#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>

//Represents a single campus resource (ex. study room)
class Resource {
private:
    std::string resourceID;
    std::string resourceName;
    std::string resourceType;
    bool available;

public:
    Resource();
    Resource(const std::string& id, const std::string& name, const std::string& type, bool isAvailable);
     
    //getters
    std::string getResourceID() const;
    std::string getResourceName() const;
    std::string getResourceType() const;
    bool isAvailable() const;

    //setters
    void setResourceID(const std::string& id);
    void setResourceName(const std::string& name);
    void setResourceType(const std::string& type);
    void setAvailable(bool isAvailable);

    //display a single resource's info which is used by resourcemanager

    void display() const;

};

// owns the resource inventory. stored in a vector per the spec, to support fast traversal
//and later sorting/searching 
class ResourceManager {
private:
    std::vector<Resource> resources;

public:
    ResourceManager();

    //loads resource records from a formatted text file
    //returns true on success, false if the file could not be opened

    bool loadFromFile(const std::string& filename);

    //adds a single resource to the in-memory store
    bool addResource(const Resource& resource);

    //displays all resources currently stored
    void displayAllResources() const;

    //diplays only resources that are currently available
    void displayAvailablity() const;

    //finds a resource by ID. Returns a  pointer to the resource in the internal vector
    //, or null ptr if not found. It's used by ReservationManager 
    //to validate reservation requests
    Resource* findResourceByID(const std::string& resourceID);

    //updates the availability of a resource by ID
    //returns true if the resource was found and updated
    bool setResourceAvailability(const std::string& resourceID, bool isAvailable);

    //returns the number of resources currently stored
    int getResourceCount() const;

    //read only access to the underlying vector
    const std::vector<Resource>& getAllResources() const;
};

#endif // RESOURCE_H
