# Philosophers
<img width="598" alt="Screenshot 2023-08-06 at 13 29 48" src="https://github.com/tlukanie/42_Philosophers/assets/120662241/f345b043-7d86-4711-ac8d-cfbfcdbf2f8a">
<h4>Dining Philosophers Problem. Goal of the project: learn to avoid deadlocks and race conditions when creating multithreaded applications.</h4>
<p>The dining philosophers problem is an excellent example to explain the concept of deadlock while resource sharing in OS.</p>
<p>The philosophers are considered to be threads and the forks to be a shared resource. Every thread needs two resources out of which one it has already acquired and the other is acquired by some other thread. Till the other thread does not free the resource, this thread cannot proceed. Similarly, the other thread is dependent on another thread for its resource. Since every thread is dependent on each other, it forms a circular-wait and the system goes into a deadlock condition.</p>
<p>In the Mandatory Part of the subject we are required to implement each philosopher as a separate thread and use mutexes to avoid the deadlocks. Check <i><b>Multithreading_practice directory</b></i> (in the current repository) for more information on threads.</p>
<h3>Tester:</h3> https://github.com/MichelleJiam/LazyPhilosophersTester<br>
<h3>Article:</h3> https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
