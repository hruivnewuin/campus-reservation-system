# Complexity Analysis - Milestone 1

## 1. Reservation Insertion (Linked List) 
**Operation:** `ReservationManager::insertReservation`

Reservations are inserted at the **head** of the singly linked list.

**Time Complexity: O(1)**
  No traversal is need. A new node is created and simply linked in front of the current head, then `head` is updated to point to it.
**Space Complexity: O(1)**
  Additional space per insertion (one new node).

If reservations were instead inserted at the **tail**, and the list did not maintain a `tail` pointer, this would require traversing the full list first,
making insertion **O(n)**. Our implementation maintains only a `head` pointer, so tail insertion is avoided in favor of O(1) head insertion.

## 2. Reservation Removal (Linked List)
**Operation:** `ReservationManager::removeReservation(int reservationID, ...)`

- **Time Complexity: O(n)**
  The list must be traversed from the head, comparing each node's reservation ID to the target,
  until a match is found (or the end of the list is reached). In the worst case (reservation not found
  ,or it's the last node), all `n` nodes are visited.
- **Best case:**
  O(1) If the reservation being removed is the head.
- **Space Complexity: O(1)**
  Removal only requires re-linking pointers and freeing one node. No additional data structures are allocated.

## 2b. Reservation Validation (Linked List)

- **Time Complexity: O(n)**
  Validation traverses the active reservation list once, checking each node for a duplicate reservation ID and
  a same resource/same date conflict. Both checks are done per node in the same pass, so this remains a single
  O(n) traversal rather than O(n) twice over.
  
## 3. Waiting List Processing (Queue)
**Operation:** `WaitingList::addToWaitingList`, `WaitingList::removeFromWaitingList`

## 4. Undo Cancellation (Stack)
**Operation:** `CancellationHistory::storeCancellation`, `CancellationHistory::restoreLastCancellation`

## Summary 







