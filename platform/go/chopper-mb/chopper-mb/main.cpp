//
//  main.cpp
//  chopper-mb
//
//  Created by Wes Richardet on 2/14/18.
//  Copyright © 2018 boundlessgeo. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <mbgl/map/map.hpp>
#include <mbgl/gl/headless_frontend.hpp>
#include <mbgl/storage/file_source.hpp>
#include <mbgl/storage/default_file_source.hpp>
#include <mbgl/gl/headless_backend.hpp>
#include <mbgl/util/shared_thread_pool.hpp>
#include <mbgl/style/style.hpp>
#include <mbgl/renderer/renderer.hpp>
#include <mbgl/renderer/renderer_backend.hpp>

volatile sig_atomic_t done = 0;

void term(int signum)
{
    done = 1;
}

void foo() {
  mbgl::FileSource *fileSource = new mbgl::DefaultFileSource("/tmp/mbgl-cache.db",".");
  std::shared_ptr<mbgl::ThreadPool> scheduler = mbgl::sharedThreadPool();
  float pixelRatio {1};
  mbgl::Renderer *rendererBackend = new mbgl::RendererBackend();
  mbgl::RendererFrontend *rendererFrontend = new mbgl::RendererFrontend(
  mbgl::Renderer *renderer = new mbgl::Renderer(rendererBackend, pixelRatio, *fileSource, *scheduler);
}

void doIt(std::shared_ptr<mbgl::ThreadPool> scheduler, mbgl::FileSource *fileSource, mbgl::PremultipliedImage *img) {
    std::unique_ptr<mbgl::Map> mapFront;
    mbgl::HeadlessFrontend *frontend;
    float pixelRatio {1};
    mbgl::HeadlessBackend *backend;
    backend = new mbgl::HeadlessBackend({256,256});
    frontend = new mbgl::HeadlessFrontend({256,256},pixelRatio,*fileSource,*scheduler);
    mapFront = std::make_unique<mbgl::Map>(*frontend, mbgl::MapObserver::nullObserver(),frontend->getSize(),1.0f,*fileSource,*scheduler,mbgl::MapMode::Tile);

    mbgl::CameraOptions camera;
    camera.center = mbgl::LatLng{0,0};
    camera.zoom = 0;
    float bearing = 0.0f;
    float pitch = 0.0f;
    camera.angle = bearing * mbgl::util::DEG2RAD;
    camera.pitch = pitch * mbgl::util::DEG2RAD;
    std::exception_ptr err;
    std::string url = "/Users/wesr/Development/boundless/mapbox-gl-native/platform/go/chopper-mb/style.json";
    std::ifstream t(url);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);
    mapFront->getStyle().loadJSON(buffer);
    mapFront->setZoom(0);
    frontend->setSize({512,512});
    mapFront->setSize({512,512});
    bool done = false;


    mapFront->renderStill([&](const std::exception_ptr eptr) {
        if (eptr) {
            err = std::move(eptr);
            std::cout << "It failed\n";
        } else {
            mbgl::PremultipliedImage i = frontend->readStillImage();
            img = &i;
            std::cout << "It worked\n";
        }
        done = true;
    });
    
    while (!done) {
        std::cout << "Waiting\n";
    }
}

int main(int argc, const char * argv[]) {
    mbgl::FileSource *fileSource = new mbgl::DefaultFileSource("/tmp/mbgl-cache.db",".");
    std::shared_ptr<mbgl::ThreadPool> scheduler = mbgl::sharedThreadPool();
    mbgl::PremultipliedImage *img = NULL;
    doIt(scheduler,fileSource,img);
    std::cout << "foo:b\n";
    
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    
    int loop = 0;
    while (!done && img == NULL)
    {
        int t = sleep(1);
        /* sleep returns the number of seconds left if
         * interrupted */
        while (t > 0)
        {
            printf("Loop run was interrupted with %d "
                   "sec to go, finishing...\n", t);
            t = sleep(t);
        }
        printf("Finished loop run %d.\n", loop++);
    }
    
    printf("done.\n");
  return 0;
}
