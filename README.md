Description: -

•	Mutex – Only one thread to access a resource at once. Example, when student is accessing a file, no one else should have access the same file at the same time. A lock of mutex (from mutual exclusion) is a synchronization mechanism for enforcing limits on access to a resource in an environment where there are many threads of execution. A lock is designed to enforce a mutual exclusion concurrency control policy.

Mutex Lock used: -
To lock and unlock variable ChairsCount to increment and decrement its value.

•	Semaphore – A semaphore contains access to a shared resource through the use of a counter. If the counter is greater than zero, than access is allowed. If it is zero, then access is denied. What the counter is counting are permits that allow access to the shared resource. Thus, to access the resource, a thread must be granted a permit from the semaphore.  

Semaphores used:
1) A semaphore to signal and wait TA's sleep.
2) An array of 3 semaphores to signal and wait chair to wait for the TA.
3) A semaphore to signal and wait for TA's next student.

Working of Semaphore
In general, to use a semaphore, the thread that wants access to the shared resource tries to acquire a permit.
•	If the semaphore’s count is greater than zero, then the thread acquires a permit, which causes the semaphore’s count to be decremented.
•	Otherwise, the thread will be blocked until a permit can be acquired.
•	When the thread no longer needs an access to the shared resource, it releases the permit, which causes the semaphore’s count to be incremented.
•	If there is another thread waiting for a permit, then that thread will acquire a permit at that time.

•	Pthread – Pthreads are a simple and effective way of creating a multi-threaded application. This introduction to pthreads shows the basic functionality – executing two tasks in parallel and merging back into a single thread in this case ‘mutex’ when the work has been done. It’s just like making two function calls at the same time.

N threads for students.
1 thread for TA.

