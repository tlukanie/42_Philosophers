# Unix processes in C
resource: https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
<p><b><i>Processes</i></b> are the primitive units for allocation of system resources. Each process has its own address space and (usually) one thread of control. A process executes a program; you can have multiple processes executing the same program, but each process has its own copy of the program within its own address space and executes it independently of the other copies.
</p>
<p>Processes are organized hierarchically. Each process has a parent process which explicitly arranged to create it. The processes created by a given parent are called its child processes. A child inherits many of its attributes from the parent process.</p>
<h3><b>fork()</b> in C</h3>
<p>The Fork system call is used for creating a new process in Linux, and Unix systems, which is called the <b><i>child process</i></b>, which runs concurrently with the process that makes the fork() call (parent process). After a new child process is created, both processes will execute the next instruction following the fork() system call.</p>
<p>The child process uses the same pc(program counter), same CPU registers, and same open files which use in the parent process. It takes no parameters and returns an integer value.</p>
<p>Below are different values returned by fork().</p>
<ul>
  <li><b><i>Negative Value</i></b>: The creation of a child process was unsuccessful.</li>
  <li><b><i>Zero</i></b>: Returned to the newly created child process.</li>
  <li><b><i>Positive value</i></b>: Returned to parent or caller. The value contains the process ID of the newly created child process.</li>
</ul>
