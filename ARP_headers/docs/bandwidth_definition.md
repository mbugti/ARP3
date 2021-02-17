# Bandwidth
Here are some definitions about the two types of bandwidths required by the RURZ's server.
It's worty of note that all the rates are measured in *bits per second*. Remember that:
-   the function **sizeof( A )** returns the number of *bytes* of the "object" A
-   th standard message uses *timeval* (s, ms) in order to hold the informations about time
So, before performing any computation, remember to convert any measurement in bits and seconds using *float* types. 


## Global Bandwidth
It is the ratio between the number of *transferred bits* along the network, and *the time from the first sending and the last receiving*.
How to compute the transferred bits? Simply it is **8 \* size( msg )**.
And what about the time? Keep into account that *the messages could arrive to you not ordered*. For example, in the case we have 4 available nodes within the network, the turn leader must wait for 5 messages, the 4 measurements of the "fly" bandwidth (see the next section) and the message for the end of the turn; the sending of the "fly" measurements could be much more slow than the transferring of the main message, so the standard message could come before other "fly" messages.
I suggest to store all the packets before analyze them when they are sent to the turn leader. Then, compute the bandwidth. Take apart also the first receiving, so you don't need to store even the first standard message.
**the formula** is the following: 
>   8 \* size( msg ) / ( last_receiving - first_sending )


## Fly-time Bandwidth
It is a different approach that ignores the elaboration time within each node of the network: it is considered only the time the message requires for starting from a node and coming to the next one. 
The quantity of transferred bits at every step is always the same, so it is possible to use the same estimation of bits shown before: **8 \* size( msg )**.
You can compute the time in this way:
1.  take one of the packets you've received (except the one which contains the standard message)
2.  compute *receiving - sending* within the same packet
3.  and then sum this duration to a variable *T* 
So, *T* is the sum of all the "fly" durations. The formula is this:
>   8 \* size( msg ) / T

