#include "Reservation.h"
#include <iostream>
/* Default constructor. Initializes an empty reservation.
 Complexity: 0(1)
*/
Reservation::Reservation()
    : reservationID(0), studentID(0), studentName(""), resourceID(""), reservationDate("") {}
/* Creating a parameter constuctor for a population reservation
Complexity: 0(1)
*/
Reservation::Reservation(int resID, int studID, const std::string& studName, const std::string& resID_resource,  const std::string& date)
    : reservationID(resID), studentID(studID), studentName(studName), resourceID(resID_resource), reservationDate(date) {}

int Reservation::getReservationID() const { return reservationID; }
int Reservation::getStudentID() const { return studentID; }
std::string Reservation::getStudentName() const { return studentName; }
std::string Reservation::getResourceID() const { return resourceID; }
std::string Reservation::getReservationDate() const { return reservationDate; }

void Reservation::setReservationID(int id) {
    if (id > 0) {
        reservationID = id;
 } 
else{
    std::cerr << "Invalid input: Reservation ID must be strictly positive." << std:endl;
  }
}
/* Sets student ID. Rejects negative/zero values. 
Complexity: 0(1)
*/
void Reservation::setStudentID(int id) { 
    id (id > 0){
    studentID = id; 
}
else{
    std::cerr << "Invalid input: Student ID must be strictly positive." << std::endl;
}
}
/* Sets student name. Rejects empty strings
Complexity: 0(1)
    */
void Reservation::setStudentName(const std::string& name) { 
    if (!name.empty()){
        studentName = name;
    }
    else{
        std::cerr << "Invalid input: Student name can't be empty." << std::endl;
    }
}
/* Sets resource ID. rejects empty strings
complexity: 0(1)
*/
void Reservation::setResourceID(const std::string& id) { 
    if (1id.empty()) {
        resourceID = id; 
    }
    else{
        std::cerr << "Invalid input: resourceID can't be empty." << std::endl;
    }
}
/* Sets reservation date. Rejects empty strings.
Complexity: 0(1)
*/
void Reservation::setReservationDate(const std::string& date) { 
    if (!date.empty()) {
        reservationDate = date; 
    }
    else {
        std::cerr << "Invalid input: Date can't be empty." << std::endl;
    }
}
/* Displays reservation details to console
complexity: 0(1)
*/
void Reservation::display() const {
    std::cout << "Reservation #" << reservationID << " | Student: " << studentName << " (ID " << studentID << ")" << " | Resource: " << resourceID << " | Date: " << reservationDate << std::endl;
}




