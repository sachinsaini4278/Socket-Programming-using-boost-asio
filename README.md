# Socket-Programming-using-boost-asio-c++
<h3>What is socket programming?</h3><br />
Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket(node) listens on a particular port at an IP, while other socket reaches out to the other to form a connection. Server forms the listener socket while client reaches out to the server.

State diagram for server and client model
![alt text](https://media.geeksforgeeks.org/wp-content/uploads/Socket-Programming-in-C-C-.jpg)

<h3>Why Boost.Asio?</h3><br />
Writing networking code that is portable is easy to maintain has been an issue since long. C++ took a step to resolve this issue by introducing boost.asio. It is a cross-platform C++ library for network and low-level I/O programming that provides developers with a consistent asynchronous model using a modern C++ approach. Here’s a list of what it offers:

Cross platform networking code (code would work on Windows, Linux, etc.)<br />
IPv4 and IPv6 support<br />
Asynchronous event support<br />
Timer support<br />
iostream compatibility<br />
And much more. You can get the complete overview of the library [here](https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/overview.html).


<h3>Environment Setup </h3><br />
I’m currently in Linux so would be covering environment setup for the same. <br/>

We just need the following to get started:

boost.asio <br />
C++ compiler (preferably g++) <br />
Text-editor <br />
The simplest way to get asio on linux is by executing the following command:<br />
```
sudo apt-get install libboost-all-dev  
```

If you’re using some other platform or the above doesn’t seem a good fit for you, follow the document [here](http://think-async.com/Asio/asio-1.10.6/doc/asio/using.html) to get asio on your system.

The next step is to make sure you have C++ compiler on your compiler. I’m using g++. You can get the same with the following command in linux.

```
sudo apt-get install g++ 
```

Once you have the compiler, you’re good to follow along. I don’t have any text-editor preference. You can choose one of your choice.

Now that we have everything, we are in a position to start coding.
