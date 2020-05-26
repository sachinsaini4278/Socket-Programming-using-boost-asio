#include <iostream>
#include <boost/asio.hpp>
void process(boost::asio::ip::tcp::socket & sock)
{
	boost::asio::streambuf buf;
	boost::asio::read_until(sock, buf, "\n");
	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	std::cout<<"Client's request is: "<<data<<std::endl;
	data = "Hello from server";
	boost::asio::write(sock, boost::asio::buffer(data));
	std::cout<<"server sent data : "<<data<<std::endl;
	
}
int main()
{
	const int BACKLOG_SIZE = 30;

    // Step 1. Here we assume that the server application has already obtained the protocol port number.
	unsigned short port_num = 3333;
	// Step 2. Creating a server endpoint.
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
	//we need at least one io_service instance. boost::asio uses io_service to talk with operating system's I/O services. 
	boost::asio::io_service io;
	
	try
	{
		// Step 3. Instantiating and opening an acceptor socket.
		boost::asio::ip::tcp::acceptor acceptor(io, ep.protocol());
		// Step 4. Binding the acceptor socket to the server endpint.
		acceptor.bind(ep);
		// Step 5. Starting to listen for incoming connection requests.
		acceptor.listen(BACKLOG_SIZE);
		
		// Step 6. Creating an active socket.
		boost::asio::ip::tcp::socket sock(io);
		// Step 7. Processing the next connection request and connecting the active socket to the client.
		acceptor.accept(sock);
		
		//all steps for creating socket using boost::asio are done.
		
		//Now perform read write operations in a function.
		//while(1)
		process(sock);
		
	}
	catch (boost::system::system_error &e)
	{
		std::cout << "Error occured! Error code = " << e.code()
		<< ". Message: " << e.what();
	
		return e.code().value();
    }
  return 0;

}
