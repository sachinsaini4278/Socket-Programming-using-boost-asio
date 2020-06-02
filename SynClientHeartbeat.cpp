/****************************************************************************************************************
###################### Client will send HEARTBEAT in eveny n seconds. HEARTBEAT transfer is done in another thread so that IO operation
can not block the heartbeat operation.#################################
				  g++ SynClientHeartbeat.cpp -o client -lboost_system -lpthread
*************************************************************************************************/
#include <iostream>
#include <boost/asio.hpp>
//#include <boost/thread.hpp>
#include<thread>
#include<chrono>
void read_data(boost::asio::ip::tcp::socket &sock);
void write_data(boost::asio::ip::tcp::socket &sock);
void IOthread(boost::asio::ip::tcp::socket &sock)
{
	write_data(sock);
	read_data(sock);
}
void sleepThread(boost::asio::ip::tcp::socket & sock)
{
	std::this_thread::sleep_for(std::chrono::seconds(5)); //sleep thread for 5 seconds
	//boost::system::error_code error;
	std::string msg = "HEARTBEAT";	
	std::cout<<"Trying to write\n";
	boost::asio::write( sock, boost::asio::buffer(msg+'\n'));
	std::cout<<"###### Requested for HEARTBEAT#########\n";
	//read_data(sock);
	//std::cout<<"\nReceived "<<str<<std::endl;
	boost::asio::streambuf receive_buffer;
	boost::asio::read_until(sock, receive_buffer, "\n");
	const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
	std::cout << "******************Received   "<<data <<"  *************  " <<std::endl;
	sleepThread(sock); //call recursively 
}
int main() {
    
	unsigned short port_num = 3333;
	boost::asio::io_service io_service;
	
	//socket creation
    boost::asio::ip::tcp::socket sock(io_service);
	
	//connection
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
	
	sock.connect( ep );
	std::thread t2([&sock](){
				sleepThread(sock);
			});
	while(1)
	{
		IOthread(sock); //calling from main thread.
	}
    return 0;
}
void read_data(boost::asio::ip::tcp::socket &sock) // for reading data
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
	//while(1){
	//Message to sent for server
	std::string msg;
	std::cout<<"Enter the message to sent\n";
	//std::cin>>msg;
	std::getline(std::cin, msg); //for getting complete line
	boost::system::error_code error;
	
	//Write message to socket
	boost::asio::write( sock, boost::asio::buffer(msg+ "\n"), error );
	if( !error ) {
		std::cout << "Client sent " << msg << std::endl;
	}
	else {
		std::cout << "send failed: " << error.message() << std::endl;
	}
	//}
}
