# SimCache
This project is a simple distributed cache system.

## How to start
If you want to test this simple distributed cache system, just download the source code.
Open your terminal, locate the project root, and run the following command.
```shell
docker build -t sdcs .
docker compose up
```
After execute above two lines of code, 3 server will start up.
Note: make sure the image name in `docker-compose.yaml` is same as `sdcs`.

## TODO
- [x] Add docker-compose.yaml feature 
- [x] Server components
- [x] RPC components
- [x] Storage and retrieve