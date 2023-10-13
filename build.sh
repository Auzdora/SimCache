cd /SDCS

cd ../third_party/json
rm -rf build
mkdir build
cd build
cmake ..
make -j 4
make install

cd /SDCS

cd ../third_party/grpc
rm -rf build
mkdir build
cd build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      ../..
make -j 4
make install