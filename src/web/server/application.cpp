#include "web/server/application.hpp"

namespace Web::Server
{
    Application::Application()
    {
        core_ = std::make_shared<Core>();
        router_ = std::make_shared<Router>(core_);
        routes_ = std::make_shared<Routes>(router_);
    }

    void Application::start()
    {
        core_->start();
    }

    void Application::stop()
    {
        core_->stop();
    }

    void Application::reload()
    {
        // Реинициализация при необходимости
    }
} // namespace Web::Server
