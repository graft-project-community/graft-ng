#include "router.h"
#include "graft_manager.h"
#include "requests.h"

namespace graft {

    Status http_test(const Router::vars_t&, const Input&, Context&, Output&)
    {
         std::cout << "blah-blah" << std::endl;
         return Status::Ok;
    }

    void setHttpRouters(GraftServer& gs)
    {
        Router dapi_router("/dapi/v2.0");
        Router::Handler3 h3_test1(http_test, nullptr, nullptr);

        dapi_router.addRoute("/test", METHOD_GET, h3_test1);
        gs.addRouter(dapi_router);

        Router http_router;
        graft::registerRTARequests(http_router);
        gs.addRouter(http_router);

        Router forward_router;
        graft::registerForwardRequests(forward_router);
        gs.addRouter(forward_router);
    }
}
