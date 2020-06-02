****************************************************************************************************************
###################### Server for giving response to client.################################
          g++ SynServerHeartbeat.cpp -o server -lboost_system -lpthread
          
*************************************************************************************************/

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
void process(boost::asio::ip::tcp::socket& sock);
std::string read_data(boost::asio::ip::tcp::socket& sock);
void write_data(boost::asio::ip::tcp::socket& sock, std::string);
//void hearbeatSender(boost::asio::ip::tcp::socket& sock);
int main()
{

    unsigned short port_num = 3333;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
    boost::asio::io_service io;
    try
    {
        boost::asio::ip::tcp::acceptor acceptor(io, ep.protocol());
        acceptor.bind(ep);
        acceptor.listen();
		boost::asio::ip::tcp::socket sock(io);
        acceptor.accept(sock);
		
     //   std::thread t([&sock]() {
     //       hearbeatSender(sock);
     //   });
        process(sock);
      //  t.join();

    }
    catch (boost::system::system_error& e)
    {
        std::cout << "Error occured! Error code = " << e.code()
            << ". Message: " << e.what();

        return e.code().value();
    }
    return 0;

}
void process(boost::asio::ip::tcp::socket& sock)
{
    while (1) {
        std::string data = read_data(sock);
        std::cout << "Client's request is: " << data << std::endl;
		if(data[0] =='H')
		{
			std::string msg = "HEARTBEAT";
			//data='5';
			boost::asio::write(sock, boost::asio::buffer(msg+'\n'));
			std::cout<<"******************HEARTBEAT sent to clinet********************\n";
		}
        else
		write_data(sock, data);
    }
}
std::string read_data(boost::asio::ip::tcp::socket& sock)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(sock, buf, "\n");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}
void write_data(boost::asio::ip::tcp::socket& sock, std::string data)
{
    boost::system::error_code error;
    std::string msg;
    int ch = data[0] - '0';
    switch (ch)
    {
    case 1: msg = "Case 1\n"; break;
    case 2: msg = "Case 2\n"; break;
    case 3: msg = "Case 3\n"; break;
    case 4: msg = "Case 4\n"; break;
    default: msg = "Case default\n"; break;
    }
    boost::asio::write(sock, boost::asio::buffer(msg + "\n"), error);
    if (!error) {
        std::cout << "Server sent "<< msg << std::endl;
    }
    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }
}
//Can be used for later use
void hearbeatSender(boost::asio::ip::tcp::socket& sock)
{
    boost::system::error_code error;
    std::string msg = "HEARTBEAT";
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << msg << std::endl;
        boost::asio::write(sock, boost::asio::buffer(msg + "\n"), error);
        if (!error) {
            std::cout << "Server sent HEARTBEAT message!" << std::endl;
        }
        else {
            std::cout << "send failed: " << error.message() << std::endl;
        }
    }
}
