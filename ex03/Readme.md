# Exercise 03

To make basic code reformating i use clang-format. with .clang-format file in the root of the kernel source code.
`clang-format -i -style=path_of_kernel source.c`

 - `-i` : edit the file in place

To check the code style i use checkpatch.pl script.
`./scripts/checkpatch.pl -file source.c`


## Sources
 - [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
 - [Submit Checklist](https://kernel.org/doc/html/v6.2/process/submit-checklist.html)
 - [Codding style](https://www.kernel.org/doc/html/v6.2/process/coding-style.html)
