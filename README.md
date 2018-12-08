# Updatable_priority_queue
an Updatable priority queue which is compatible with the STL. 

Compare with the priority_queue, the priority_queue stores value-priority pairs  
The queue use an unordered_map to keep track of the values in the queue.
This give the same complexity for the priority_queue operation and a log(n)
complexity for the update. 

The heap routine from the STL was rewrite to update the map during those operation.

