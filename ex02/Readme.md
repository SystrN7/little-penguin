# Exercise 02

Create branch `change-extra-version` from `master` and do the following:
`git checkout -b change-extra-version master`

Change the EXTRAVERSION in makefile to `-thor_kernel`.

Compile the kernel and install it.
See this [README](../ex00/Readme.md) for more info.

Commit the change.
`git commit -m "change EXTRAVERSION to -thor_kernel"`

Create a patch from the commit and send it to the mailing list.
` git format-patch -o outgoing/ master`

A new directory `outgoing` is created and the patch is inside it.

To test if the patch is correct:
`./scripts/checkpatch.pl ./0001-change-EXTRAVERSION-to-thor_kernel.patch`


## Sources
<!-- https://docs.kernel.org/kbuild/makefiles.html#kbuild-variables -->
 - [Linux KConfig docs](https://www.kernel.org/doc/html/v6.2/kbuild/kconfig.html)
 - [Linux Makefile info about EXTRAVERSION](https://kernel.org/doc/html/v6.2/kbuild/makefiles.html#kbuild-variables)
 - [Linux path submition gidelines](https://www.kernel.org/doc/html/v6.2/process/submit-checklist.html)
 - [man of git format-patch](https://git-scm.com/docs/git-format-patch/en)
