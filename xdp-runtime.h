#ifndef XDP_RUNTIME_H
#define XDP_RUNTIME_H

#include <stdint.h>

struct xdp_md_userspace {
	uint64_t data;
	uint64_t data_end;
	uint64_t data_meta;
	unsigned int ingress_ifindex;
	unsigned int rx_queue_index;
	unsigned int egress_ifindex;
};


// run the eBPF program(s) for xdp
int ebpf_module_run_at_handler(void *mem, uint64_t mem_size,
                                     uint64_t *ret);
// init the runtime context
int ebpf_module_init();

#endif
