Q3 .)In the parent thread, read one line of input into the buffer.
Print the buffer to stdout from within the child thread (do not synchronize with the parent at this stage).
Explain in your README what happens and why!

A3. After create the child thread, the parent read a line of code and store it in the specified memory address(array),
and a pointer pointer to the beginning of the address, and the child thread print the line of code by the address of pointer
However, both thread happen at the same time (racing), if the child thread print the line first (read the buffer first and the ),
then the result is nothing or just part of the strings on the screen.
So the current situation is, the child thread print nothing on the screen because child thread is faster than the main thread
something strange code output (h?), h?>

Q5. After the child thread has printed the output, make the parent thread prompt the user to hit Enter
(and wait for the user to do so). Hint: You will need a second mutex for this.
Explain in your README why this cannot be done reliably with a single mutex!
How reliable is an approach that uses 2 mutexes?
Explain if there is a scenario where even two mutexes might not be enough and
whether adding further mutexes (but no other synchronisation means such as busy waiting) would help.

A5. Because mutex can only unlock by the thread who lock it. As the
otherwise the child thread will be exited normally
