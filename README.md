# PubSub

UDB and RPC based server and client.

# How to run the program

First compile with make

`$ make`

To run the server:

`$ sudo ./communicate_server server_port registry_server_ip registry_server_port`

This starts the server and connec to the registry server with registry_server_ip and registry_server_port. There is a simple user interface for our group server where user can select 1 to get the registered server list from the registry server and 2 to deregister from the registry server and quit.

For each client, a separate terminal window in the same directory is used. To start it,

`$ ./communicate_client localhost  //or ip of server`

The client has a simple text-based UI using integers as menu selectors:

```
What do you want to do?
1 - subscribe
2 - unsubscribe
3 - publish
4 - quit
>
```

At the prompt, simply type the number for your menu item and press enter, and then at the prompt that follows, enter a string for operation. It handles most (not going to say all) invalid strings gracefully.

Periodically, there will be a ping message, but this is normal operation indicating that the server is still alive and won’t affect any inputs.

