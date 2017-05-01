Q3. In the parent thread, read one line of input into the buffer.
Print the buffer to stdout from within the child thread (do not synchronize with the parent at this stage).
Explain in your README what happens and why!

A3. After create the child thread, the parent thread read a line of code and store it in the specified memory address(array),
and a pointer point to the beginning of the address, and the child thread print the line of code by the address of pointer.
However, both thread happen at the same time (thread racing), if the child thread print the line first
(read the buffer first before the main thread read the string to buffer ),
then the output will be nothing or just part of the strings on the screen.
So the current situation is, the child thread print nothing on the screen because child thread is faster than the main thread
something strange code output (h?), h?> which means the child thread run faster than the main thread
A3 answer is ok

Q5(1). After the child thread has printed the output, make the parent thread prompt the user to hit Enter
(and wait for the user to do so). Hint: You will need a second mutex for this.
Explain in your README why this cannot be done reliably with a single mutex!

A5(1). Because when using one mutex, we can't guarantee the order which thread
get(lock) the mutex first or try to get the mutex (get blocked).
In this situation, after child thread print out and release the mutex, and then try to lock the mutex again (suppose to get blocked
until the main thread release the mutex after the user pressed the "enter",
however, the child thread may secure the mutex again and continuously execute the rest of code and exit child thread in order
to main thread get the lock, the main thread can't not notify the child thread the user has pressed the enter key
A5(1) answer is ok

Q5(2). How reliable is an approach that uses 2 mutex?

A5(2). Sometime we can't guarantee the order of both threads which run fast, if in a situation that both threads is trying
to get the other thread lock, and those threads are waiting to each other lock to
release which become a deadlock.
For example: main thread is waiting the child thread's mutex whereas child thread is waiting the main thread's mutex

Two mutex has more chances to become deadlock if the sequence isn't as the design does.
Also it can't guarantee the order of threads are executed in order.
A5(2) answer is ok


Q5(3). Explain if there is a scenario where even two mutex might not be enough and
whether adding further mutex (but no other synchronization means such as busy waiting) would help.

A5(3). Due to the racing in two threads that may not able to schedule the order, and avoid the deadlock if each thread is waiting
for another thread mutex. The third mutex is needed.

the three mutex should be required when the thread is waiting the other thread to release mutex,
the other thread can execute the rest of code unless the third mutex is lock and the thread try to unlock it
(blocked because waiting to the original thread to release it)
Because mutex can only unlock by the thread who lock it. otherwise the child thread will be exited normally

Q6. Do you need a third mutex for this notification?
Will this be reliable under all circumstances?  Explain why/why not!
For the notification step, it should use the third lock.
It should be very reliable if the three mutexes are in rotate order that can avoid the deadlock situation

For example: 1.) Main thread lock mutex1, then child thread lock mutex2 and try to get mutex1 (get blocked),
             2.) Main thread lock mutex3, try to get lock mutex2 (get blocked) then release mutex1, 
                whereas child thread can lock mutex1 and release mutex2 (get blocked)
