# Updatable_priority_queue
an Updatable priority queue which is compatible with the STL. 

This queue work similarly as the priority_queue from the STL but it stores value-priority pairs instead of bared priority
This is of use for application where the priority is different than the value itself and the priority may change. 
(Ex: People waiting in a queue, where priority may be influence by external factor)


The queue use an unordered_map to keep track of the values in the queue.
This give the same complexity for the priority_queue operation and a log(n) complexity for the update. 
The heap routine from the STL was rewrite to update the map during those operation.

