#include "Reservation.h"
#include <iostream>

Reservation::Reservation()
    : reservationID(0), studentID(0), studentName(""), resourceID(""), reservationDate("") {}
  
Reservation::Reservation(int resID, int studID, const std::string& studName, const std::string& resourceID,  const std::string& date)
    : reservationID(resID), studentID(studID), studentName(studName), resourceID(resourceID), reservationDate(date) {}

int Reservation::getReservationID() const { return reservationID; }
int Reservation::getStudentID() const { return studentID; }
std::string Reservation::getStudentName() const { return studentName; }
std::string Reservation::getResourceID() const { return resourceID; }
std::string Reservation::getReservationDate() const { return reservationDate; }

void Reservation::setReservationID(int id) { reservationID = id; }
void Reservation::setStudentID(int id) { studentID = id; }
void Reservation::setStudentName(const std::string& name) { studentName = name; }
void Reservation::setResourceID(const std::string& id) { resourceID = id; }
void Reservation::setReservationDate(const std::string& date) { reservationDate = date; }

void Reservation::display() const {
    std::cout << "Reservation #" << reservationID << " | Student: " << studentName << " (ID " << studentID << ")" << " | Resource: " << resourceID << " | Date: " << reservationDate << std::endl;
}




