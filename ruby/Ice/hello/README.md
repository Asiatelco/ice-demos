This demo illustrates how to invoke ordinary (twoway) operations, as
well as how to make oneway, datagram, secure, and batched invocations.

The Ice extension for Ruby currently supports only client-side
functionality, therefore you must use a server from any other language
mapping.

After starting the server, run the Ruby client:

```
ruby Client.rb
```

To test timeouts you can use 'T' to set an invocation timeout on the client
proxy and 'P' to set a delayed response in the server to cause a timeout.
