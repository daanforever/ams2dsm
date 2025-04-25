#include <string>

#include "web/server/headers.hpp"

namespace Web::Server
{

    Router::Router(std::shared_ptr<Core> core_) : core(core_)
    {
        logger::debug("router.set_pre_routing_handler");

        core->server->set_pre_routing_handler(
            [this](const httplib::Request& req, httplib::Response& res) -> Result {
                logger::debug("router.pre_routing_handler for path {0}", req.path);
                const Request wrapped_req(shared_from_this(), req);
                Response wrapped_res(shared_from_this(), wrapped_req, res);
                auto result = apply_middlewares(wrapped_req, wrapped_res);
                return result;
            });
    }

    Router::~Router() = default;

    WrappedHandler Router::wrapped(Handler handler)
    {
        return [&, handler](const httplib::Request& req, httplib::Response& res) {
            logger::debug("router.wrapped {0}", req.path);
            const Request wrapped_req(shared_from_this(), req);
            Response wrapped_res(shared_from_this(), wrapped_req, res);
            handler(wrapped_req, wrapped_res);
        };
    }

    Router& Router::use(Middleware middleware)
    {
        global_middlewares_.push_back(middleware);
        return *this;
    }

    Router& Router::use(const std::string& path, Middleware middleware)
    {
        path_middlewares_[path].push_back(middleware);
        logger::debug("router.use path_middlewares_ for path {0} size={1}", path,
                      path_middlewares_.count(path));
        return *this;
    }

    Router& Router::auth(const std::string& path)
    {
        logger::debug("router.auth set");
        chain_middlewares_.push_back(Middlewares::Auth(core->session, path));
        return *this;
    }

    Router& Web::Server::Router::path(const std::string& path)
    {
        next_path = std::move(path);
        return *this;
    }

    void Router::directory(const std::string& uri, const std::string& path)
    {
        chain_to_path_middleware(uri);
        core->server->set_mount_point(uri, path);
    }

    void Router::get(const std::string& path, Handler handler)
    {
        chain_to_path_middleware(path);
        core->server->Get(path, wrapped(handler));
    }

    void Router::post(const std::string& path, Handler handler)
    {
        chain_to_path_middleware(path);
        core->server->Post(path, wrapped(handler));
    }

    void Router::put(const std::string& path, Handler handler)
    {
    }

    void Router::patch(const std::string& path, Handler handler)
    {
    }

    void Router::del(const std::string& path, Handler handler)
    {
    }

    void Router::head(const std::string& path, Handler handler)
    {
    }

    void Router::options(const std::string& path, Handler handler)
    {
    }

    void Router::connect(const std::string& path, Handler handler)
    {
    }

    void Router::trace(const std::string& path, Handler handler)
    {
    }

    Result Router::apply_middlewares(const Request& req, Response& res)
    {
        std::vector<Middleware> middlewares = {};

        if (global_middlewares_.size())
        {
            middlewares = global_middlewares_;
        }

        if (path_middlewares_.count(req.path))
        {
            auto& path_mw = path_middlewares_[req.path];
            middlewares.insert(middlewares.end(), path_mw.begin(), path_mw.end());
        }

        auto result = Result::Unhandled;

        logger::debug("router.apply_middlewares {0}", middlewares.size());

        if (middlewares.empty())
        {
            return result;
        }

        for (auto it = middlewares.rbegin(); it != middlewares.rend(); ++it)
        {
            auto& mw = *it;
            result = mw(req, res);

            if (result == Result::Handled)
                break;
        }

        return result;
    }

    void Router::chain_to_path_middleware(const std::string& path)
    {
        if (chain_middlewares_.size())
        {
            for (auto it = chain_middlewares_.rbegin(); it != chain_middlewares_.rend(); ++it)
            {
                auto& mw = *it;
                use(path, mw);
            }

            chain_middlewares_.clear();
        }
    }
} // namespace Web::Server
