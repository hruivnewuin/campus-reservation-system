#ifndef WAITING_LIST_H
#define WAITING_LIST_H
#include "ReservationRecord.h"
#include <functional>
#include <ostream>
#include <queue>

// Create one instance per resource. The front is always the oldest request.
class WaitingList {
private:
    std::string resourceId;
    std::queue<ReservationRecord> requests;
public:
    explicit WaitingList(const std::string& resourceId);
    // Returns false for incomplete, wrong-resource, or duplicate requests.
    bool addStudent(const ReservationRecord& request);
    // FIFO removal; false on empty, leaving output unchanged.
    bool removeStudent(ReservationRecord& removed);
    // Calls the manager's assignment function for the oldest request only.
    // Removes the request only when assignment succeeds.
    bool processNext(const std::function<bool(const ReservationRecord&)>& assign);
    void display(std::ostream& out) const;
    bool empty() const;
    std::size_t size() const;
};
#endif
