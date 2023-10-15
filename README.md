# SimCache
This project is a simple distributed cache system.

## How to start
If you want to test this simple distributed cache system, just download the source code.
Open your terminal, locate the project root, and run the following command.
```shell
docker build -t sdcs .
./compose-generate.sh 3 sdcs
docker compose up
```
After execute above code, 3 server will start up.

You can change the `./compose-generate.sh [server num] [image name]`, make sure it is same as the docker image name you created before.

Note: make sure the image name in `docker-compose.yaml` is same as `sdcs`.

## TODO
- [x] Add docker-compose.yaml feature 
- [x] Server components
- [x] RPC components
- [x] Storage and retrieve