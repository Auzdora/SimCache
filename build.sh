rm -rf build
mkdir build
cd build
cmake ..

cd ../third_party/json
rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)
make install

cd ..
cd ..
cd ..
cd build
make -j$(nproc)