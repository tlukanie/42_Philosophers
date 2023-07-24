# Philosophers
https://github.com/tlukanie/42_Philosophers/assets/120662241/fbdafb35-eb2c-451b-8f29-5860c446595c
<h4>Dining Philosophers Problem. Goal of the project: learn to avoid deadlocks and race conditions when creating multithreaded applications.</h4>
<p>The dining philosophers problem is an excellent example to explain the concept of deadlock while resource sharing in OS.</p>
<p>The philosophers are considered to be threads and the forks to be a shared resource. Every thread needs two resources out of which one it has already acquired and the other is acquired by some other thread. Till the other thread does not free the resource, this thread cannot proceed. Similarly, the other thread is dependent on another thread for its resource. Since every thread is dependent on each other, it forms a circular-wait and the system goes into a deadlock condition.</p>
<p>In the Mandatory Part of the subject we are required to implement each philosopher as a separate thread and use mutexes to avoid the deadlocks.</p>
<h3>Tester:</h3> https://github.com/MichelleJiam/LazyPhilosophersTester<br>
<h3>Article:</h3> https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
