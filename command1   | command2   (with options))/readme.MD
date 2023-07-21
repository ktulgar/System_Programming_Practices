I found this exercise on a website called emertxe.com . I wanted to make for practice. 
<p>
    to visit website <a href="https://www.emertxe.com/embedded-systems/linux-internals/li-assignments/">Click</a>!
<p>


Objectives:
<ul>
	<li>To understand working of pipe between two process.</li>
</ul>

Requirements:
<ol>
	<li>Create two child process and execute commands passed from command-line arguments.</li>
        <li>Each command is separated by a ‘|’ (pipe) character.</li>
        <li>First child execute first command (with or without options) and pass o/p to next.</li>
        <li>Second child executes second command (after ‘|’) will reads I/p from first cmd.</li>
        <li>Parent will wait for both child process to finish.</li>
</ol>

