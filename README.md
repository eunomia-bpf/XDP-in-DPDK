# XDP in userspace eBPF with DPDK

The repo is moved to https://github.com/userspace-xdp/userspace-xdp

## XDP examples: libbpf-bootstrap

Use libbpf-bootsrap to load xdp program in userspace.

### Run xdp-observer

Run in kernel

```console
make -C xdp-observer
# xdp-observer/main ens33
Source IP, Destination IP, Source Port, Destination Port, SIN, FIN, RST, PSH, ACK 
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
```

Run in userspace with bpftime

```console
# LD_PRELOAD=build-bpftime/bpftime/runtime/syscall-server/libbpftime-syscall-server.so SPDLOG_LEVEL=error xdp-observer/main veth0 xdp-observer/userspace.btf
Successfully started! Please Ctrl+C to stop.
Source IP, Destination IP, Source Port, Destination Port, SIN, FIN, RST, PSH, ACK 
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
10.0.0.1 10.0.0.10 44698 8000 1 0 0 0 0
^CTerminating
```

Test

```sh

```

## Compile and run

To get and build dpdk from the root project directory:

(Also add bpftime in the directory)

```sh
git submodule update --init --recursive
make dpdk
```

build bpftime library

```sh
export PKG_CONFIG_PATH=<the path of the pkgconfig directory inside dpdk>
cmake -B build-bpftime .
make -C  build-bpftime
```

To build the dpdk-based server:

```sh
export PKG_CONFIG_PATH=<the path of the pkgconfig directory inside dpdk>
# e.g. export PKG_CONFIG_PATH=/home/yunwei37/XDP-eBPF-in-DPDK/external/dpdk/install-dir/lib/x86_64-linux-gnu/pkgconfig
make build
```

To run a very simple test:

In one terminal window

```sh
sudo ./build/base-server -l 0 --vdev=net_tap0,iface=tapdpdk
```

In another terminal window:

```sh
sudo ./scripts/testbed-setup.sh
sudo arping -i veth0 1.2.3.4
```

## clean up share memory

```sh
sudo build-bpftime/bpftime/tools/bpftimetool/bpftimetool remove
```
