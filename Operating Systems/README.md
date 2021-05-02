INTRODUCTION:	

Our project is an extended version of Linux shell with some extra Functions. We will implement our own system calls, which will work via kernel. We will develop our own SHELL and then we will integrate our system calls. We will implement two system calls, namely, Cosine function and Dining Philosopher Problem (Dead Lock Simulation).
 
 MODULES:
 
1	Cosine Function:

We will implement the COS function as a system call.

2	Dining Philosopher Problem:

The Dining Philosopher Problem states that K philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pick up the two chopsticks adjacent to him. One chopstick may be picked up by any one of its adjacent followers but not both.

TOOLS:

GEDIT & DEV C++ (For C Programming Code) 


DETAILS: 

	Cosine Function: In our implementation of the cosine function, we made use of the Taylor series expansion of cosine.

Cosx  = 1 – x^2/2! + x^4/4! - …

All calculations were carried out by user defined functions, no built in functions or libraries were used. To speed up the process, threads were used to enable task level parallelism.

	Dining Philosopher: In our implementation of the dining philosopher, we created 5 separate threads, one for each philosopher. Mutex locks were used for the sharing of resource, in this case the spoons. Spoons were randomly picked and locked by the mutex_lock call. If a spoon was already in use, the thread would be blocked from executing the eat function (executed as a form of a delay) unless it was released using the mutex_unlock call.  This solved the critical section problem as it ensured that the 3 conditions of mutual exclusion, progress and bounded waiting were fulfilled.
