#include <atomic>
#include <csignal>
#include <memory>
#include <thread>

#include "web/server/application.hpp"

std::atomic<bool> running{true};
std::unique_ptr<Web::Server::Application> server;

static void handle_signal(int signal)
{
    running = false;
}

int main()
{
    std::signal(SIGTERM, handle_signal);
    std::signal(SIGINT, handle_signal);
    std::signal(SIGABRT, handle_signal);

    logger::set_level(logger::level::debug);

    server = std::make_unique<Web::Server::Application>();
    server->start();

    {
        struct ServerGuard
        {
            ~ServerGuard()
            {
                if (server)
                {
                    server->stop();
                    server.reset();
                }
            }
        } guard;

        while (running)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}
