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
The waiting list is implemented as a linked list backed queue with both a front and a rear pointer.
Maintaining both front and rear pointers is what keeps both enqueue and dequeue at O(1). Without a rear pointer, enqueue would degrade to O(n) because the list would need to be walked to find the last node.

- **Enqueue (add to waiting list): O(1)**
  A new node is attached directly at rear and then its updated. No traversal.
- **Dequeue (remove from waiting list and serve next student): O(1)**
  The node at the `front` is removed directly, and the `front` is advanced to the next node. No traversal.
- **Display waiting list: O(n)**
  Printing every waiting request requires visiting all `n` nodes once.

## 4. Undo Cancellation (Stack)
**Operation:** `CancellationHistory::storeCancellation`, `CancellationHistory::restoreLastCancellation`
The cancellation history is implemented as a linked list backed stack, where push and pop both operate on the top pointer.

- **Store cancellation (push): O(1)**
  A new node is created and linked in as the new `top`.
- **Restore last cancellation (pop): O(1)**
  The node at `top` is removed and top is advanced to the next node because only the most recently cancelled reservation can ever be restored, no traversal.
- **Display waiting list: O(n)**
  Printing the full history by most recent requires visiting all n nodes once.

## Summary - why these structure were picked
- **Linked List for reservations:** reservations are created and cancelled
  frequently and the total count is not known ahead of time, so a dynamically sized structure with O(1) insertion is preferable to a fixed size array.
- **Queue for waiting lists:** requests must be served in the order they arrived, which is exactly the FIFO queue.
- **Stack for cancellation history:** only the simple most recently cancelled a reservation can be undone, which is the LIFO stack. It doesn't need searching to find the most recent item.








