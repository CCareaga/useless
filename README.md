# useless VM
---

In its current state, useless is a register-based virtual machine written in C. It has 24 instructions and uses an assembly language smiliar to x86 assembly. After creating useless, I wanted to test it's effectiveness. In order to do this I wrote an even simpler VM that runs inside of useless called even-more-useless VM (emuvm). EmuVM is a very simple stack-based virtual machine written entirely in the language of the useless VM. Along the way I also created a debugging command-line called udb. It displays registers, the stack, and the current line and supports typical debugging commands such as break, continue, step and print. 

NOTE: the creation of nested VM's from scratch is purely a proof-of-concept exercise, hence the name useless. Despite the seemingly futile nature of this repository, I believe this experiment has been extremely valuable to me as a learning experience. I urge others to read through the code and take a crack at writing some simple programs to run in both uvm and emuvm. Hopefully, this repo provides a glimpse at the mind-boggling things that can be done in C (or any programming language for that matter).

#### Example Program
---
Here is what a program to recursively print a string backwards looks like in useless assembly:

```
mv &src a
call print_reverse

exit

$print_reverse
    eq 0 *a
    hopt rev_ret

    add 1 a
    call print_reverse
    print *a

    $rev_ret
        sub 1 a
        ret

$src
    "\nI am useless"
```

this will output the following:
```
$ ./uvm examples/recursive.vm
sselesu ma I
```
this is what a simple loop looks like in emuvm assembly:
```
$program
    "push 20"
     
    "$loop" 
        "dup"
        "peek" 
        "push 10"
        "print"
        "push 0"
        "eq" 
        "hopt loop_end"
        "push 1"
        "sub"
        "hop loop" 

    "$loop_end" 
        "exit"
        
    "end"
```
NOTE: since useless has no way of reading from a file, the program text of the inner vm is embedded inside useless assembly following a label called `$program`. 

this program will output:
```
$ ./uvm emuvm/*
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 
```

#### Building and Running
---
To compile useless run:

```sh
$ make
```

to assemble and run a useless program run:

```sh
$ ./uvm <one or more files>
```
NOTE: add the `-d` flag in order to run the program with the the useless debugger

after compiling useless, you can run even-more-useless:

```
./uvm emuvm/*
```

this will run emuvm and emuvm will run a program to calculate fibonacci numbers. the program can be changed, it is stored in `emuvm/fib.vm`.

#### Results
---
One result to note is the performance of both the VMs:

| Machine  | Time to calculate fib(35) |
| ------------- | ------------- |
| Intel i3 @ 2.30GHz  | 0.9 seconds |
| useless  | 5.3 seconds |
|even-more-useless | 2 min 44 secs |

These include time for interpreting the programs so they aren't perfectly exact but I think they display my point. 
I am satisifed with the effectiveness of useless, I was able to create a VM, language and debugger advanced enough to write another VM inside the first...

#### Feedback and Contribution
---
Feel free to add instructions to useless or improve its performance, or fix bugs in emuvm (incredibly hard to debug). Let me know of any error you find or what you think of this project.

#### Documentation
---
Work in progress...

