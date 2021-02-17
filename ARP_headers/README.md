
# Libraries

## Compiling

All headers are conveniently referenced by the *arpnet.h* library, which resides in the root folder of the "ARP_headers" directory.
From within the source code it's sufficient to write
```
	#include "arpnet.h"
```
to reference it.

Similarly, all libraries objects (the ones expresssed in the different subdirectories) are linked together in the static library
*libarpnet.a*, once again found in the root of the "ARP_headers" dir.

To correctly reference them when compiling it's sufficient to tell the compiler where to look (-I option for the header, 
-L for the library), following the pattern
```
	$ gcc -L<path_>/ARP_headers -I<path>/ARP_headers -o <source_name> <source_name>.c -larpnet

```
Where "path" referes to the path that make "ARP_headers" reachable from the current directory at the time of calling the
compiler. As a further example, supposing to have a structure with 

```
root/
	|
	ARP_headers/
		|
		arpnet.h
		libarpnet.a
		<stuff>
	src/
		|
		hello_node.c
```
We can simply compile our "hello_node.c" into the executable "hello_node" by going into the
directory src/ and writing
```
	$ gcc -L../ARP_headers -I../ARP_headers -o hello_node hello_node.c -larpnet
```
