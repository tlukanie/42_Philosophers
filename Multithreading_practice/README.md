# Multithreading in C
resource:
https://www.youtube.com/playlist?app=desktop&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

<p>
  In computer architecture, <b><i>multithreading</i></b> is the ability of a central processing unit (CPU) (or a single core in a multi-core processor) to provide multiple threads of execution concurrently, supported by the operating system. This approach differs from multiprocessing.
</p>
<p>
  Where multiprocessing systems include multiple complete processing units in one or more cores, multithreading aims to increase utilization of a single core by using thread-level parallelism, as well as instruction-level parallelism. As the two techniques are complementary, they are combined in nearly all modern systems architectures with multiple multithreading CPUs and with CPUs with multiple multithreading cores.
</p>
<h3>What is a Thread?</h3>
<p>
  A thread is a single sequence stream within a process. Because threads have some of the properties of processes, they are sometimes called <i>lightweight processes</i>.
</p>
<h3>What are the differences between process and thread? </h3>
<p>
  Threads are not independent from each other unlike processes. As a result, threads shares with other threads their code section, data section and OS resources like open files and signals. But, like processes, a thread has its own program counter (PC), a register set, and a stack space. 
</p>
<h3>Why Multithreading?</h3>
<p>Threads are popular way to improve application through parallelism. For example, in a browser, multiple tabs can be different threads. MS word uses multiple threads, one thread to format the text, other thread to process inputs, etc. </p>
<p>Threads operate faster than processes due to following reasons: </p>
<ol>
  <li>Thread creation is much faster. </li>
  <li>Context switching between threads is much faster. </li>
  <li>Threads can be terminated easily</li>
  <li>Communication between threads is faster.</li>
</ol>
