Q5. Add a short test report to your documentation

A5. The mutex and semaphore(binary semaphore which use 1 and 0) are similar in this case.
Mutex can be get twice if acquire by the same owner that will not affect the program because Mutex only
has two states which is locked and unlocked. But if using semaphore with the same
situation above that will become deadlock because this semaphore has no queue in it
that no other thread can unlock it (although semaphore can be signal by other thread that not like
mutex which can only unlock by its owner). And semaphore can avoid race condition if the semaphore has
the queue ability.  
