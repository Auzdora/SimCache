# SimCache
This project is a simple distributed cache system.

## How to start
After you get the src code of this project, you need to do the following to let this program successfully compile and run.

### Build
```shell
mkdir build
cd build 
cmake ..
make -j$(nproc)
```
In this way, you will get the binary output file called `simcache-server`, which is located in `./build/bin/`.

### Dockerfile
To be able to run this bin file. You will need locate the project root directory, and run the following command.
```shell
docker build -t cache_image .
docker run -p 1234:9527 cache_image
```
1234 is the port that you will access in your local computer. 9527 should be set before you compiled in `./apps/main.cpp`.

### Docker Compose
Docker compose is a powerful tool to deploy a distributed program. For this project, the `docker-compose.yaml` is all set. You can just simply run the following command
```shell
docker compose up
```
If you want shut all these down, type
```shell
docker compose down
```

## TODO
- [x] Add docker-compose.yaml feature 
- [x] Server components
- [ ] gRPC components
- [ ] Storage and retrieve