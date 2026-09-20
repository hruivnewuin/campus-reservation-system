#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

// Represents a single reservation record
class Reservation {
private:
    int reservationID;
    int studentID;
    std::string studentName;
    std::string resourceID;
    std::string reservationDate;

public:
    Reservation();
    Reservation(int resID, int studID, const std::string& studName, const std::string& resID_resource, const std::string& date);

    // Getters
    int getReservationID() const;
    int getStudentID() const;
    std::string getStudentName() const;
    std::string getResourceID() const;
    std::string getReservationDate() const;

    // Setters
    void setReservationID(int id);
    void setStudentID(int id);
    void setStudentName(const std::string& name);
    void setResourceID(const std::string& id);
    void setReservationDate(const std::string& date);

    // Display a single reservation's info
    void display() const;
};

#endif // RESERVATION_H
