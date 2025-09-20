# mapping-test

This repo is about testing the effects of hashmaps and similiar.

## compile and run (example)

> clear; gcc main.c regularArray.c moduloMap.c -o mapping-test; ./mapping-test -l 1024 -m 100000000 -c 1000000

flags explained:

-l default array length
-m maximum id
-s step in ids; Set this to something that -l is is divisible by to hurt modulo by causing more collisions. This will effectively override -m.
-c count