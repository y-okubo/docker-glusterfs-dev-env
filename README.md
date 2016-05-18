# Prepare
```
./bin/docker-machine-nfs.sh default --shared-folder=/Users
```
マウントが異常な場合はホスト側の NFS 再起動する

# Server

## Build
```
$ docker build -t glusterfs-server server
```

## Run
```
$ docker run --privileged -tid -p 20022:22 --hostname gfserver --name gfserver glusterfs-server
```

To detach this container you can press `Ctrl p + Ctrl q`

# Login
```
$ ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -p 20022 root@localhost
```

Mount the volume at login

# Client

## Build
```
$ docker build -t glusterfs-client client
```

## Run
```
$ docker run --privileged -tid -p 20023:22 -p 8080:8080 -v /Users/y-okubo:/go/path --link gfserver:server --hostname gfclient --name gfclient glusterfs-client
```

# Login
```
$ ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -p 20023 root@localhost
```

# Test

```
$ gcc hello.c -lgfapi
$ ./a.out
```
