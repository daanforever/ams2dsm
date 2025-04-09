export module web.server.routes;

import web.server.router;

namespace Web::Server {

  export class Routes {
  public:
    Router& router;

    explicit Routes::Routes(Router& router_);
    ~Routes();
    void setup();
  };

  explicit Routes::Routes(Router& router_) : router(router_) {};
  Routes::~Routes() = default;

  void Routes::setup() {

    router.auth("/login/").set_mount_point("/", "./web");
    router.set_mount_point("/login", "./web/login");

    router.post("/auth", Web::Controllers::Auth::post());
    router.get("/auth", Web::Controllers::Auth::get());

    router.get("/status", [](const Request& req, Response& res) {
      res.set_content("Server status: OK", "text/plain");
    });

  }
}  // namespace WebServer::Routes