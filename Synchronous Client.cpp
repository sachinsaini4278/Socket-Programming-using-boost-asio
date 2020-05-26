#include <iostream>
#include <boost/asio.hpp>

int main() {
    
	unsigned short port_num = 3333;
	boost::asio::io_service io_service;
	
	//socket creation
    boost::asio::ip::tcp::socket socket(io_service);
	
	//connection
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
	socket.connect( ep );
	
	//Message to sent for server
	const std::string msg = "Hello from Client!\n";
    
	boost::system::error_code error;
    //Write message to socket
	boost::asio::write( socket, boost::asio::buffer(msg), error );
    if( !error ) {
        std::cout << "Client sent hello message!" << std::endl;
     }
     else {
        std::cout << "send failed: " << error.message() << std::endl;
     }
 // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if( error && error != boost::asio::error::eof ) {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << "Received "<<data << std::endl;
    }

    return 0;
}
