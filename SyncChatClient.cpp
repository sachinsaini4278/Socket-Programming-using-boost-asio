/***************************************************************************************************************
###################### Simple synchronous chat with server by I/O operations using boost #######################
                       g++ SyncChatClient.cpp -o client -lboost_system
***************************************************************************************************************/
#include <iostream>
#include <boost/asio.hpp>
std::string read_data(boost::asio::ip::tcp::socket &sock);
void write_data(boost::asio::ip::tcp::socket &sock);
int main() {
    
	unsigned short port_num = 3333;
	
	boost::asio::io_service io_service;
	
	//socket creation
    boost::asio::ip::tcp::socket socket(io_service);
	
	//connection
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
	
	socket.connect( ep );
	
	
	while(1){
		
		write_data(socket);
		std::string str = read_data(socket);
		sleep(2); //wait for 2 second if you need otherwise comment it.
	}
    return 0;
}
std::string read_data(boost::asio::ip::tcp::socket &sock)
{
	boost::system::error_code error;
	// 	getting response from server
	boost::asio::streambuf receive_buffer;
	//boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
	boost::asio::read_until(sock, receive_buffer, "\n");
	if( error && error != boost::asio::error::eof ) {
		std::cout << "receive failed: " << error.message() << std::endl;
	}
	else {
		const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
		std::cout << "Received "<<data << std::endl;
	}
	
}
void write_data(boost::asio::ip::tcp::socket &sock)
{
	//Message to sent for server
	std::string msg;
	std::cout<<"Enter the message to sent\n";
	//std::cin>>msg;
	std::getline(std::cin, msg); //for getting complete line
	boost::system::error_code error;
	
	//Write message to socket
	boost::asio::write( sock, boost::asio::buffer(msg+ "\n"), error );
	if( !error ) {
		std::cout << "Client sent hello message!" << std::endl;
	}
	else {
		std::cout << "send failed: " << error.message() << std::endl;
	}
	
}
