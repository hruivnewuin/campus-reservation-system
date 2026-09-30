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
    //hand written Quick Sort. Sorts vec[low to high] in place
    //byID selects the comparison field. True = compare resourceID
    //False = compare resourceName
    void quickSort(std::vector<Resource>& vec, int low, int high, bool byID);

    //Partitions vec[low to high] around a middle element pivot and return the pivot's final index
    //Using a middle element rather than first/last avoid Quick Sort's O(n^2) worst case on data that already sorted or reverse sorted
    int partition(std::vector<Resource>& vec, int low, int high, bool byID);

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
    void displayAvailability() const;

    //finds a resource by ID. Returns a pointer to the resource in the internal vector
    //, or null ptr if not found. It's used by ReservationManager 
    //to validate reservation requests
    Resource* findResourceByID(const std::string& resourceID);

    //Binary search for a resource by ID. Requires resources to laready be sorted by ID
    //Call sortResourcesByID() first otherwise its undefined results
    //Returns a pointer to the match or nulptr if not found
    Resource* searchResourceByID(const std::string& resourceID);

    //Sorts the internal resources vector in place by ID through ascending order
    //Must be called before searchResourceByID() to work correctly
    void sortResourceByID();

    //Sorts the internal resources vector in place by resource name, A to Z
    void sortResourcesByName();

    //updates the availability of a resource by ID
    //returns true if the resource was found and updated
    bool setResourceAvailability(const std::string& resourceID, bool isAvailable);

    //returns the number of resources currently stored
    int getResourceCount() const;

    //read only access to the underlying vector
    const std::vector<Resource>& getAllResources() const;
};

#endif // RESOURCE_H
