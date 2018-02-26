//
//  main.cpp
//  chopper-mb
//
//  Created by Wes Richardet on 2/14/18.
//  Copyright © 2018 boundlessgeo. All rights reserved.
//

#include <iostream>
#include <mbgl/map/map.hpp>
#include <mbgl/gl/headless_frontend.hpp>
#include <mbgl/storage/file_source.hpp>
#include <mbgl/gl/headless_backend.hpp>
#include <mbgl/util/shared_thread_pool.hpp>

int doIt(mbgl::FileSource *fileSource) {
    std::unique_ptr<mbgl::Map> mapFront;
  std::unique_ptr<mbgl::Map> mapBack;
  mbgl::HeadlessFrontend *frontend;
  std::shared_ptr<mbgl::ThreadPool> scheduler = mbgl::sharedThreadPool();
  float a = 1.0f;
  frontend = new mbgl::HeadlessFrontend({256,256},a,*fileSource,*scheduler);
//  std::unique_ptr<mbgl::HeadlessBackend> backend;
//    backend = std::make_unique<mbgl::HeadlessBackend>(mbgl::Size{256, 256});
//  mapFront = std::make_unique<mbgl::Map>(*frontend,,frontend->getSize(),1.0f,fileSource,scheduler,mbgl::MapMode::Tile);
//    mapFront->getStyle().
    return 1;
}

int main(int argc, const char * argv[]) {
  return 0;
}
