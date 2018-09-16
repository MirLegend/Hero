.. currentmodule:: asyncio

.. _asyncio-event-loop:

Base Event Loop
===============

The event loop is the central execution device provided by :mod:`asyncio`.
It provides multiple facilities, amongst which:

* Registering, executing and cancelling delayed calls (timeouts).

* Creating client and server :ref:`transports <asyncio-transport>` for various
  kinds of communication.

* Launching subprocesses and the associated :ref:`transports
  <asyncio-transport>` for communication with an external program.

* Delegating costly function calls to a pool of threads.

.. class:: BaseEventLoop

   Base class of event loops.

Run an event loop
-----------------

.. method:: BaseEventLoop.run_forever()

   Run until :meth:`stop` is called.

.. method:: BaseEventLoop.run_until_complete(future)

   Run until the :class:`Future` is done.

   If the argument is a :ref:`coroutine object <coroutine>`, it is wrapped by
   :func:`async`.

   Return the Future's result, or raise its exception.

.. method:: BaseEventLoop.is_running()

   Returns running status of event loop.

.. method:: BaseEventLoop.stop()

   Stop running the event loop.

   Every callback scheduled before :meth:`stop` is called will run.
   Callbacks scheduled after :meth:`stop` is called will not run.
   However, those callbacks will run if :meth:`run_forever` is called
   again later.

.. method:: BaseEventLoop.is_closed()

   Returns ``True`` if the event loop was closed.

   .. versionadded:: 3.4.2

.. method:: BaseEventLoop.close()

   Close the event loop. The loop must not be running.

   This clears the queues and shuts down the executor, but does not wait for
   the executor to finish.

   This is idempotent and irreversible. No other methods should be called after
   this one.


Calls
-----

.. method:: BaseEventLoop.call_soon(callback, \*args)

   Arrange for a callback to be called as soon as possible.

   This operates as a FIFO queue, callbacks are called in the order in
   which they are registered.  Each callback will be called exactly once.

   Any positional arguments after the callback will be passed to the
   callback when it is called.

   An instance of :class:`asyncio.Handle` is returned.

.. method:: BaseEventLoop.call_soon_threadsafe(callback, \*args)

   Like :meth:`call_soon`, but thread safe.


.. _asyncio-delayed-calls:

Delayed calls
-------------

The event loop has its own internal clock for computing timeouts.
Which clock is used depends on the (platform-specific) event loop
implementation; ideally it is a monotonic clock.  This will generally be
a different clock than :func:`time.time`.

.. note::

   Timeouts (relative *delay* or absolute *when*) should not exceed one day.


.. method:: BaseEventLoop.call_later(delay, callback, *args)

   Arrange for the *callback* to be called after the given *delay*
   seconds (either an int or float).

   An instance of :class:`asyncio.Handle` is returned.

   *callback* will be called exactly once per call to :meth:`call_later`.
   If two callbacks are scheduled for exactly the same time, it is
   undefined which will be called first.

   The optional positional *args* will be passed to the callback when it
   is called. If you want the callback to be called with some named
   arguments, use a closure or :func:`functools.partial`.

.. method:: BaseEventLoop.call_at(when, callback, *args)

   Arrange for the *callback* to be called at the given absolute timestamp
   *when* (an int or float), using the same time reference as :meth:`time`.

   This method's behavior is the same as :meth:`call_later`.

.. method:: BaseEventLoop.time()

   Return the current time, as a :class:`float` value, according to the
   event loop's internal clock.

.. seealso::

   The :func:`asyncio.sleep` function.


Coroutines
----------

.. method:: BaseEventLoop.create_task(coro)

   Schedule the execution of a :ref:`coroutine object <coroutine>`: wrap it in
   a future. Return a :class:`Task` object.

   Third-party event loops can use their own subclass of :class:`Task` for
   interoperability. In this case, the result type is a subclass of
   :class:`Task`.

   This method was added in Python 3.4.2. Use the :func:`async` function to
   support also older Python versions.

   .. versionadded:: 3.4.2


Creating connections
--------------------

.. method:: BaseEventLoop.create_connection(protocol_factory, host=None, port=None, \*, ssl=None, family=0, proto=0, flags=0, sock=None, local_addr=None, server_hostname=None)

   Create a streaming transport connection to a given Internet *host* and
   *port*: socket family :py:data:`~socket.AF_INET` or
   :py:data:`~socket.AF_INET6` depending on *host* (or *family* if specified),
   socket type :py:data:`~socket.SOCK_STREAM`.  *protocol_factory* must be a
   callable returning a :ref:`protocol <asyncio-protocol>` instance.

   This method is a :ref:`coroutine <coroutine>` which will try to
   establish the connection in the background.  When successful, the
   coroutine returns a ``(transport, protocol)`` pair.

   The chronological synopsis of the underlying operation is as follows:

   #. The connection is established, and a :ref:`transport <asyncio-transport>`
      is created to represent it.

   #. *protocol_factory* is called without arguments and must return a
      :ref:`protocol <asyncio-protocol>` instance.

   #. The protocol instance is tied to the transport, and its
      :meth:`connection_made` method is called.

   #. The coroutine returns successfully with the ``(transport, protocol)``
      pair.

   The created transport is an implementation-dependent bidirectional stream.

   .. note::
      *protocol_factory* can be any kind of callable, not necessarily
      a class.  For example, if you want to use a pre-created
      protocol instance, you can pass ``lambda: my_protocol``.

   Options allowing to change how the connection is created:

   * *ssl*: if given and not false, a SSL/TLS transport is created
     (by default a plain TCP transport is created).  If *ssl* is
     a :class:`ssl.SSLContext` object, this context is used to create
     the transport; if *ssl* is :const:`True`, a context with some
     unspecified default settings is used.

     .. seealso:: :ref:`SSL/TLS security considerations <ssl-security>`

   * *server_hostname*, is only for use together with *ssl*,
     and sets or overrides the hostname that the target server's certificate
     will be matched against.  By default the value of the *host* argument
     is used.  If *host* is empty, there is no default and you must pass a
     value for *server_hostname*.  If *server_hostname* is an empty
     string, hostname matching is disabled (which is a serious security
     risk, allowing for man-in-the-middle-attacks).

   * *family*, *proto*, *flags* are the optional address family, protocol
     and flags to be passed through to getaddrinfo() for *host* resolution.
     If given, these should all be integers from the corresponding
     :mod:`socket` module constants.

   * *sock*, if given, should be an existing, already connected
     :class:`socket.socket` object to be used by the transport.
     If *sock* is given, none of *host*, *port*, *family*, *proto*, *flags*
     and *local_addr* should be specified.

   * *local_addr*, if given, is a ``(local_host, local_port)`` tuple used
     to bind the socket to locally.  The *local_host* and *local_port*
     are looked up using getaddrinfo(), similarly to *host* and *port*.

   On Windows with :class:`ProactorEventLoop`, SSL/TLS is not supported.

   .. seealso::

      The :func:`open_connection` function can be used to get a pair of
      (:class:`StreamReader`, :class:`StreamWriter`) instead of a protocol.


.. method:: BaseEventLoop.create_datagram_endpoint(protocol_factory, local_addr=None, remote_addr=None, \*, family=0, proto=0, flags=0)

   Create datagram connection: socket family :py:data:`~socket.AF_INET` or
   :py:data:`~socket.AF_INET6` depending on *host* (or *family* if specified),
   socket type :py:data:`~socket.SOCK_DGRAM`.

   This method is a :ref:`coroutine <coroutine>` which will try to
   establish the connection in the background.  When successful, the
   coroutine returns a ``(transport, protocol)`` pair.

   See the :meth:`BaseEventLoop.create_connection` method for parameters.

   On Windows with :class:`ProactorEventLoop`, this method is not supported.


.. method:: BaseEventLoop.create_unix_connection(protocol_factory, path, \*, ssl=None, sock=None, server_hostname=None)

   Create UNIX connection: socket family :py:data:`~socket.AF_UNIX`, socket
   type :py:data:`~socket.SOCK_STREAM`. The :py:data:`~socket.AF_UNIX` socket
   family is used to communicate between processes on the same machine
   efficiently.

   This method is a :ref:`coroutine <coroutine>` which will try to
   establish the connection in the background.  When successful, the
   coroutine returns a ``(transport, protocol)`` pair.

   On Windows with :class:`ProactorEventLoop`, SSL/TLS is not supported.

   See the :meth:`BaseEventLoop.create_connection` method for parameters.

   Availability: UNIX.


Creating listening connections
------------------------------

.. method:: BaseEventLoop.create_server(protocol_factory, host=None, port=None, \*, family=socket.AF_UNSPEC, flags=socket.AI_PASSIVE, sock=None, backlog=100, ssl=None, reuse_address=None)

   Create a TCP server bound to *host* and *port*. Return a :class:`Server` object,
   its :attr:`~Server.sockets` attribute contains created sockets. Use the
   :meth:`Server.close` method to stop the server: close listening sockets.

   This method is a :ref:`coroutine <coroutine>`.

   If *host* is an empty string or ``None``, all interfaces are assumed
   and a list of multiple sockets will be returned (most likely
   one for IPv4 and another one for IPv6).

   *family* can be set to either :data:`socket.AF_INET` or
   :data:`~socket.AF_INET6` to force the socket to use IPv4 or IPv6. If not set
   it will be determined from host (defaults to :data:`socket.AF_UNSPEC`).

   *flags* is a bitmask for :meth:`getaddrinfo`.

   *sock* can optionally be specified in order to use a preexisting
   socket object.

   *backlog* is the maximum number of queued connections passed to
   :meth:`~socket.socket.listen` (defaults to 100).

   *ssl* can be set to an :class:`~ssl.SSLContext` to enable SSL over the
   accepted connections.

   *reuse_address* tells the kernel to reuse a local socket in
   TIME_WAIT state, without waiting for its natural timeout to
   expire. If not specified will automatically be set to True on
   UNIX.

   On Windows with :class:`ProactorEventLoop`, SSL/TLS is not supported.

   .. seealso::

      The function :func:`start_server` creates a (:class:`StreamReader`,
      :class:`StreamWriter`) pair and calls back a function with this pair.


.. method:: BaseEventLoop.create_unix_server(protocol_factory, path=None, \*, sock=None, backlog=100, ssl=None)

   Similar to :meth:`BaseEventLoop.create_server`, but specific to the
   socket family :py:data:`~socket.AF_UNIX`.

   Availability: UNIX.


Watch file descriptors
----------------------

On Windows with :class:`SelectorEventLoop`, only socket handles are supported
(ex: pipe file descriptors are not supported).

On Windows with :class:`ProactorEventLoop`, these methods are not supported.

.. method:: BaseEventLoop.add_reader(fd, callback, \*args)

   Start watching the file descriptor for read availability and then call the
   *callback* with specified arguments.

.. method:: BaseEventLoop.remove_reader(fd)

   Stop watching the file descriptor for read availability.

.. method:: BaseEventLoop.add_writer(fd, callback, \*args)

   Start watching the file descriptor for write availability and then call the
   *callback* with specified arguments.

.. method:: BaseEventLoop.remove_writer(fd)

   Stop watching the file descriptor for write availability.


Low-level socket operations
---------------------------

.. method:: BaseEventLoop.sock_recv(sock, nbytes)

   Receive data from the socket.  The return value is a bytes object
   representing the data received.  The maximum amount of data to be received
   at once is specified by *nbytes*.

   With :class:`SelectorEventLoop` event loop, the socket *sock* must be
   non-blocking.

   This method is a :ref:`coroutine <coroutine>`.

   .. seealso::

      The :meth:`socket.socket.recv` method.

.. method:: BaseEventLoop.sock_sendall(sock, data)

   Send data to the socket.  The socket must be connected to a remote socket.
   This method continues to send data from *data* until either all data has
   been sent or an error occurs.  ``None`` is returned on success.  On error,
   an exception is raised, and there is no way to determine how much data, if
   any, was successfully processed by the receiving end of the connection.

   With :class:`SelectorEventLoop` event loop, the socket *sock* must be
   non-blocking.

   This method is a :ref:`coroutine <coroutine>`.

   .. seealso::

      The :meth:`socket.socket.sendall` method.

.. method:: BaseEventLoop.sock_connect(sock, address)

   Connect to a remote socket at *address*.

   The *address* must be already resolved to avoid the trap of hanging the
   entire event loop when the address requires doing a DNS lookup.  For
   example, it must be an IP address, not an hostname, for
   :py:data:`~socket.AF_INET` and :py:data:`~socket.AF_INET6` address families.
   Use :meth:`getaddrinfo` to resolve the hostname asynchronously.

   With :class:`SelectorEventLoop` event loop, the socket *sock* must be
   non-blocking.

   This method is a :ref:`coroutine <coroutine>`.

   .. seealso::

      The :meth:`BaseEventLoop.create_connection` method, the
      :func:`open_connection` function and the :meth:`socket.socket.connect`
      method.


.. method:: BaseEventLoop.sock_accept(sock)

   Accept a connection. The socket must be bound to an address and listening
   for connections. The return value is a pair ``(conn, address)`` where *conn*
   is a *new* socket object usable to send and receive data on the connection,
   and *address* is the address bound to the socket on the other end of the
   connection.

   The socket *sock* must be non-blocking.

   This method is a :ref:`coroutine <coroutine>`.

   .. seealso::

      The :meth:`BaseEventLoop.create_server` method, the :func:`start_server`
      function and the :meth:`socket.socket.accept` method.


Resolve host name
-----------------

.. method:: BaseEventLoop.getaddrinfo(host, port, \*, family=0, type=0, proto=0, flags=0)

   This method is a :ref:`coroutine <coroutine>`, similar to
   :meth:`socket.getaddrinfo` function but non-blocking.

.. method:: BaseEventLoop.getnameinfo(sockaddr, flags=0)

   This method is a :ref:`coroutine <coroutine>`, similar to
   :meth:`socket.getnameinfo` function but non-blocking.


Connect pipes
-------------

On Windows with :class:`SelectorEventLoop`, these methods are not supported.
Use :class:`ProactorEventLoop` to support pipes on Windows.

.. method:: BaseEventLoop.connect_read_pipe(protocol_factory, pipe)

   Register read pipe in eventloop.

   *protocol_factory* should instantiate object with :class:`Protocol`
   interface.  *pipe* is a :term:`file-like object <file object>`.
   Return pair ``(transport, protocol)``, where *transport* supports the
   :class:`ReadTransport` interface.

   With :class:`SelectorEventLoop` event loop, the *pipe* is set to
   non-blocking mode.

   This method is a :ref:`coroutine <coroutine>`.

.. method:: BaseEventLoop.connect_write_pipe(protocol_factory, pipe)

   Register write pipe in eventloop.

   *protocol_factory* should instantiate object with :class:`BaseProtocol`
   interface. *pipe* is file-like object.
   Return pair (transport, protocol), where transport support
   :class:`WriteTransport` interface.

   With :class:`SelectorEventLoop` event loop, the *pipe* is set to
   non-blocking mode.

   This method is a :ref:`coroutine <coroutine>`.

.. seealso::

   The :meth:`BaseEventLoop.subprocess_exec` and
   :meth:`BaseEventLoop.subprocess_shell` methods.


UNIX signals
------------

Availability: UNIX only.

.. method:: BaseEventLoop.add_signal_handler(signum, callback, \*args)

   Add a handler for a signal.

   Raise :exc:`ValueError` if the signal number is invalid or uncatchable.
   Raise :exc:`RuntimeError` if there is a problem setting up the handler.

.. method:: BaseEventLoop.remove_signal_handler(sig)

   Remove a handler for a signal.

   Return ``True`` if a signal handler was removed, ``False`` if not.

.. seealso::

   The :mod:`signal` module.


Executor
--------

Call a function in an :class:`~concurrent.futures.Executor` (pool of threads or
pool of processes). By default, an event loop uses a thread pool executor
(:class:`~concurrent.futures.ThreadPoolExecutor`).

.. method:: BaseEventLoop.run_in_executor(executor, callback, \*args)

   Arrange for a callback to be called in the specified executor.

   The *executor* argument should be an :class:`~concurrent.futures.Executor`
   instance. The default executor is used if *executor* is ``None``.

   This method is a :ref:`coroutine <coroutine>`.

.. method:: BaseEventLoop.set_default_executor(executor)

   Set the default executor used by :meth:`run_in_executor`.


Error Handling API
------------------

Allows to customize how exceptions are handled in the event loop.

.. method:: BaseEventLoop.set_exception_handler(handler)

   Set *handler* as the new event loop exception handler.

   If *handler* is ``None``, the default exception handler will
   be set.

   If *handler* is a callable object, it should have a
   matching signature to ``(loop, context)``, where ``loop``
   will be a reference to the active event loop, ``context``
   will be a ``dict`` object (see :meth:`call_exception_handler`
   documentation for details about context).

.. method:: BaseEventLoop.default_exception_handler(context)

   Default exception handler.

   This is called when an exception occurs and no exception
   handler is set, and can be called by a custom exception
   handler that wants to defer to the default behavior.

   *context* parameter has the same meaning as in
   :meth:`call_exception_handler`.

.. method:: BaseEventLoop.call_exception_handler(context)

   Call the current event loop exception handler.

   *context* is a ``dict`` object containing the following keys
   (new keys may be introduced later):

   * 'message': Error message;
   * 'exception' (optional): Exception object;
   * 'future' (optional): :class:`asyncio.Future` instance;
   * 'handle' (optional): :class:`asyncio.Handle` instance;
   * 'protocol' (optional): :ref:`Protocol <asyncio-protocol>` instance;
   * 'transport' (optional): :ref:`Transport <asyncio-transport>` instance;
   * 'socket' (optional): :class:`socket.socket` instance.

   .. note::

       Note: this method should not be overloaded in subclassed
       event loops.  For any custom exception handling, use
       :meth:`set_exception_handler()` method.

Debug mode
----------

.. method:: BaseEventLoop.get_debug()

   Get the debug mode (:class:`bool`) of the event loop.

   The default value is ``True`` if the environment variable
   :envvar:`PYTHONASYNCIODEBUG` is set to a non-empty string, ``False``
   otherwise.

   .. versionadded:: 3.4.2

.. method:: BaseEventLoop.set_debug(enabled: bool)

   Set the debug mode of the event loop.

   .. versionadded:: 3.4.2

.. seealso::

   The :ref:`debug mode of asyncio <asyncio-debug-mode>`.

Server
------

.. class:: Server

   Server listening on sockets.

   Object created by the :meth:`BaseEventLoop.create_server` method and the
   :func:`start_server` function. Don't instanciate the class directly.

   .. method:: close()

      Stop serving: close listening sockets and set the :attr:`sockets`
      attribute to ``None``.

      The sockets that represent existing incoming client connections are
      leaved open.

      The server is closed asynchonously, use the :meth:`wait_closed` coroutine
      to wait until the server is closed.

   .. method:: wait_closed()

      Wait until the :meth:`close` method completes.

      This method is a :ref:`coroutine <coroutine>`.

   .. attribute:: sockets

      List of :class:`socket.socket` objects the server is listening to, or
      ``None`` if the server is closed.


Handle
------

.. class:: Handle

   A callback wrapper object returned by :func:`BaseEventLoop.call_soon`,
   :func:`BaseEventLoop.call_soon_threadsafe`, :func:`BaseEventLoop.call_later`,
   and :func:`BaseEventLoop.call_at`.

   .. method:: cancel()

      Cancel the call.



.. _asyncio-hello-world-callback:

Example: Hello World (callback)
-------------------------------

Print ``Hello World`` every two seconds, using a callback::

    import asyncio

    def print_and_repeat(loop):
        print('Hello World')
        loop.call_later(2, print_and_repeat, loop)

    loop = asyncio.get_event_loop()
    loop.call_soon(print_and_repeat, loop)
    try:
        loop.run_forever()
    finally:
        loop.close()

.. seealso::

   :ref:`Hello World example using a coroutine <asyncio-hello-world-coroutine>`.


Example: Set signal handlers for SIGINT and SIGTERM
---------------------------------------------------

Register handlers for signals :py:data:`SIGINT` and :py:data:`SIGTERM`::

    import asyncio
    import functools
    import os
    import signal

    def ask_exit(signame):
        print("got signal %s: exit" % signame)
        loop.stop()

    loop = asyncio.get_event_loop()
    for signame in ('SIGINT', 'SIGTERM'):
        loop.add_signal_handler(getattr(signal, signame),
                                functools.partial(ask_exit, signame))

    print("Event loop running forever, press CTRL+c to interrupt.")
    print("pid %s: send SIGINT or SIGTERM to exit." % os.getpid())
    try:
        loop.run_forever()
    finally:
        loop.close()

