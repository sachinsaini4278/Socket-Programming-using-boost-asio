/***************************************************************************************************************
###################### Simple synchronous chat with client by I/O operations using boost #######################
                       g++ SyncChatServer.cpp -o server -lboost_system
****************************************************************************************************************/

#include <iostream>
#include <boost/asio.hpp>
void process(boost::asio::ip::tcp::socket & sock);
std::string read_data(boost::asio::ip::tcp::socket & sock);
void write_data(boost::asio::ip::tcp::socket & sock);
int main()
{
	//const int BACKLOG_SIZE = 30;

    // Step 1. Here we assume that the server application has already obtained the protocol port number.
	unsigned short port_num = 3333;
	// Step 2. Creating a server endpoint.
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
	//we need at least one io_service instance. boost::asio uses io_service to talk with operating system's I/O services. 
	boost::asio::io_service io;
	//while(1){
	try
	{
		// Step 3. Instantiating and opening an acceptor socket.
		boost::asio::ip::tcp::acceptor acceptor(io, ep.protocol());
		// Step 4. Binding the acceptor socket to the server endpint.
		acceptor.bind(ep);
		// Step 5. Starting to listen for incoming connection requests.
		acceptor.listen();
		
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
	//}
  return 0;

}
void process(boost::asio::ip::tcp::socket & sock)
{
	while(1){
	std::string data = read_data(sock);
	std::cout<<"Client's request is: "<<data<<std::endl;
	
	write_data(sock);
	}
}
std::string read_data(boost::asio::ip::tcp::socket & sock)
{
	boost::asio::streambuf buf;
	boost::asio::read_until(sock, buf, "\n");
	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	return data;
}
void write_data(boost::asio::ip::tcp::socket & sock)
{
	boost::system::error_code error;
	std::string msg;
	std::cout<<"Enter the message \n";
	//std::cin>>msg;
	std::getline(std::cin,msg); //For getting complete line 
	boost::asio::write( sock, boost::asio::buffer(msg+ "\n"), error );
     if( !error ) {
        std::cout << "Server sent hello message!" << std::endl;
     }
     else {
        std::cout << "send failed: " << error.message() << std::endl;
     }
}
