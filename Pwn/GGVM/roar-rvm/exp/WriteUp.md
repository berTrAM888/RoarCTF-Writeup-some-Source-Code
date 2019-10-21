# GGVM

- environ: Ubuntu 18.04
- introduction: mini instruction vm forked from skx/simple.vm

### Step 1 - Leak:

- instruction `concat` will not append `\x00` at the tail of concated string, consequently we can leak something.

- in my exploitation, `_IO_wfile_jumps` is leaked from a abandoned `_IO_FILE_plus`

### Step 2 - Virtual RAM Overflow (actually heap overflow):

- instruction `memcpy` handle the virtual-ram-overflow situation with `if r >0xffff r -= 0xffff`, so that we can overwrite chunks higher than Virtual RAM

- in my exploitation, `svm->error_handler` is controlled and changed to system

### then getshell