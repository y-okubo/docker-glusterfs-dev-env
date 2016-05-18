FROM centos

MAINTAINER Yuki Okubo <y-okubo@nekojarashi.com>

ENV container docker

# Install require packages
RUN yum --setopt=tsflags=nodocs -y update
RUN yum --setopt=tsflags=nodocs -y install wget nfs-utils openssh-server vim
RUN yum -y swap -- remove fakesystemd -- install systemd systemd-libs

# Added to enable systemd. Reference: http://developerblog.redhat.com/2014/05/05/running-systemd-within-docker-container/
RUN yum -y update; yum clean all; \
(cd /lib/systemd/system/sysinit.target.wants/; for i in *; do [ $i == systemd-tmpfiles-setup.service ] || rm -f $i; done); \
rm -f /lib/systemd/system/multi-user.target.wants/*;\
rm -f /etc/systemd/system/*.wants/*;\
rm -f /lib/systemd/system/local-fs.target.wants/*; \
rm -f /lib/systemd/system/sockets.target.wants/*udev*; \
rm -f /lib/systemd/system/sockets.target.wants/*initctl*; \
rm -f /lib/systemd/system/basic.target.wants/*;\
rm -f /lib/systemd/system/anaconda.target.wants/*;

# Add epel repository
RUN wget http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-6.noarch.rpm
RUN rpm -ivh epel-release-7-6.noarch.rpm

# Install GlusterFS packages
RUN wget http://download.gluster.org/pub/gluster/glusterfs/3.7/LATEST/EPEL.repo/glusterfs-epel.repo -O /etc/yum.repos.d/glusterfs-epel.repo
RUN yum -y update
RUN yum --setopt=tsflags=nodocs --enablerepo=epel -y install glusterfs glusterfs-fuse glusterfs-cli glusterfs-api glusterfs-api-devel glusterfs-devel
RUN yum --setopt=tsflags=nodocs --enablerepo=epel -y install attr iputils iproute
RUN yum clean all

RUN echo 'root:password' | chpasswd
VOLUME [ “/sys/fs/cgroup” ]

EXPOSE 111 245 443 24007 2049 8080 6010 6011 6012 38465 38466 38468 38469 49152 49153 49154 49156 49157 49158 49159 49160 49161 49162

RUN systemctl disable nfs-server.service
RUN systemctl enable rpcbind.service
RUN systemctl enable sshd.service
CMD ["/usr/sbin/init"]

RUN yum --setopt=tsflags=nodocs -y groupinstall "Development Tools"
RUN wget https://storage.googleapis.com/golang/go1.6.2.linux-amd64.tar.gz
RUN tar -C /usr/local -xzf go1.6.2.linux-amd64.tar.gz

COPY ./hello.c /root/hello.c

RUN mkdir -p /root/go/bin \
  && echo 'export GOROOT=/usr/local/go' >> /root/.bashrc \
  && echo 'export GOPATH=/go/path' >> /root/.bashrc \
  && echo 'export GOBIN=/go/bin' >> /root/.bashrc \
  && echo 'export PATH=$PATH:$GOROOT/bin:$GOBIN' >> /root/.bashrc
