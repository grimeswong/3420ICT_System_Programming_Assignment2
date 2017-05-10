Q5. Add a short test report to your documentation

A5. The main different between mutex and semaphore (if semaphore initial value using 0) is that semaphore can unlock mutex by signal by other thread,
but mutex can only unlock by it's owner thread. Also, the interchange of the threads access is not be controlled well if just using mutex alone.
In this program, the main thread can use signal to unlock the blocked child thread by increase one in the procure function that allow blocked thread to
executed from the state of waiting to running, then if the main thread try to get the semaphore, the child thread need to notify the semaphore from -1 to
0 which the main thread can continue to execute the critical section.
