#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <future>
#include <chrono>
#include <thread>
#include "libs/logger/logger.hpp"
#include "libs/httpclient/httpclient.hpp"

using namespace boost;
using asio::ip::tcp;
using std::cout, std::endl;

std::mutex connection_mutex;
std::condition_variable cv;
bool launched_server = false;

logger LOG{};
void start_client();
void start_server();
int main(int argc, char *argv[])
{
    try
    {
        // auto client_future = std::async(std::launch::async, start_client);
        // auto server_future = std::async(std::launch::async, start_server);
        start_client();

        // client_future.wait();
        // server_future.wait();
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
void start_client()
{
    try
    {
        http::httpclient client(LOG);
        client.get("127.0.0.1");
    }
    catch (std::exception &e)
    {
        LOG(e.what());
    }
}
std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
};
void start_server()
{
    try
    {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        tcp::socket socket(io_context);
        std::unique_lock<std::mutex> lk{connection_mutex};
        launched_server = true;
        lk.unlock();
        cv.notify_one();
        acceptor.accept(socket);

        std::string message = make_daytime_string();

        boost::system::error_code ignored_error;
        size_t len = boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        LOG("Wrote: " + std::to_string(len));
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}