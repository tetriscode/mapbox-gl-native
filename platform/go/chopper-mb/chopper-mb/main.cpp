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
  std::unique_ptr<mbgl::HeadlessFrontend> frontend;
  std::shared_ptr<mbgl::ThreadPool> scheduler = mbgl::sharedThreadPool();
  frontend = mbgl::HeadlessFrontend(mbgl::Size{ 256, 256 },1.0f,fileSource,scheduler);
//  std::unique_ptr<mbgl::HeadlessBackend> backend;
//    backend = std::make_unique<mbgl::HeadlessBackend>(mbgl::Size{256, 256});
//  mapFront = std::make_unique<mbgl::Map>(*frontend,,frontend->getSize(),1.0f,fileSource,scheduler,mbgl::MapMode::Tile);
//    mapFront->getStyle().
    return 1;
}

int main(int argc, const char * argv[]) {

  // insert code here...
  std::cout << "hello world";
  return 0;
}
