# Prepare
```
./bin/docker-machine-nfs.sh default --shared-folder=/Users
```

# Server

## Build image
```
$ docker build -t glusterfs-server server
```

## Run container
```
$ docker run --privileged -tid -p 20022:22 --hostname gfserver --name gfserver glusterfs-server
```

To detach this container you can press `Ctrl p + Ctrl q`

# SSH login
```
$ ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -p 20022 root@localhost
```

Mount the volume at login

# Client

## Build image
```
$ docker build -t glusterfs-client client
```

## Run container
```
$ docker run --privileged -tid -p 20023:22 -p 8080:8080 -v /Users/y-okubo:/go/path --link gfserver:server --hostname gfclient --name gfclient glusterfs-client
```

# SSH login
```
$ ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -p 20023 root@localhost
```

# Test
```
$ gcc hello.c -lgfapi
$ ./a.out
```
