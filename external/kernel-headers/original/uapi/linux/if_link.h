#ifndef _UAPI_LINUX_IF_LINK_H
#define _UAPI_LINUX_IF_LINK_H

#include <linux/types.h>
#include <linux/netlink.h>

struct rtnl_link_stats {
	__u32	rx_packets;		
	__u32	tx_packets;		
	__u32	rx_bytes;		
	__u32	tx_bytes;		
	__u32	rx_errors;		
	__u32	tx_errors;		
	__u32	rx_dropped;		
	__u32	tx_dropped;		
	__u32	multicast;		
	__u32	collisions;

	
	__u32	rx_length_errors;
	__u32	rx_over_errors;		
	__u32	rx_crc_errors;		
	__u32	rx_frame_errors;	
	__u32	rx_fifo_errors;		
	__u32	rx_missed_errors;	

	
	__u32	tx_aborted_errors;
	__u32	tx_carrier_errors;
	__u32	tx_fifo_errors;
	__u32	tx_heartbeat_errors;
	__u32	tx_window_errors;

	
	__u32	rx_compressed;
	__u32	tx_compressed;
};

struct rtnl_link_stats64 {
	__u64	rx_packets;		
	__u64	tx_packets;		
	__u64	rx_bytes;		
	__u64	tx_bytes;		
	__u64	rx_errors;		
	__u64	tx_errors;		
	__u64	rx_dropped;		
	__u64	tx_dropped;		
	__u64	multicast;		
	__u64	collisions;

	
	__u64	rx_length_errors;
	__u64	rx_over_errors;		
	__u64	rx_crc_errors;		
	__u64	rx_frame_errors;	
	__u64	rx_fifo_errors;		
	__u64	rx_missed_errors;	

	
	__u64	tx_aborted_errors;
	__u64	tx_carrier_errors;
	__u64	tx_fifo_errors;
	__u64	tx_heartbeat_errors;
	__u64	tx_window_errors;

	
	__u64	rx_compressed;
	__u64	tx_compressed;
};

struct rtnl_link_ifmap {
	__u64	mem_start;
	__u64	mem_end;
	__u64	base_addr;
	__u16	irq;
	__u8	dma;
	__u8	port;
};


enum {
	IFLA_UNSPEC,
	IFLA_ADDRESS,
	IFLA_BROADCAST,
	IFLA_IFNAME,
	IFLA_MTU,
	IFLA_LINK,
	IFLA_QDISC,
	IFLA_STATS,
	IFLA_COST,
#define IFLA_COST IFLA_COST
	IFLA_PRIORITY,
#define IFLA_PRIORITY IFLA_PRIORITY
	IFLA_MASTER,
#define IFLA_MASTER IFLA_MASTER
	IFLA_WIRELESS,		
#define IFLA_WIRELESS IFLA_WIRELESS
	IFLA_PROTINFO,		
#define IFLA_PROTINFO IFLA_PROTINFO
	IFLA_TXQLEN,
#define IFLA_TXQLEN IFLA_TXQLEN
	IFLA_MAP,
#define IFLA_MAP IFLA_MAP
	IFLA_WEIGHT,
#define IFLA_WEIGHT IFLA_WEIGHT
	IFLA_OPERSTATE,
	IFLA_LINKMODE,
	IFLA_LINKINFO,
#define IFLA_LINKINFO IFLA_LINKINFO
	IFLA_NET_NS_PID,
	IFLA_IFALIAS,
	IFLA_NUM_VF,		
	IFLA_VFINFO_LIST,
	IFLA_STATS64,
	IFLA_VF_PORTS,
	IFLA_PORT_SELF,
	IFLA_AF_SPEC,
	IFLA_GROUP,		
	IFLA_NET_NS_FD,
	IFLA_EXT_MASK,		
	IFLA_PROMISCUITY,	
#define IFLA_PROMISCUITY IFLA_PROMISCUITY
	IFLA_NUM_TX_QUEUES,
	IFLA_NUM_RX_QUEUES,
	IFLA_CARRIER,
	IFLA_PHYS_PORT_ID,
	IFLA_CARRIER_CHANGES,
	__IFLA_MAX
};


#define IFLA_MAX (__IFLA_MAX - 1)

#ifndef __KERNEL__
#define IFLA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifinfomsg))))
#define IFLA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ifinfomsg))
#endif

enum {
	IFLA_INET_UNSPEC,
	IFLA_INET_CONF,
	__IFLA_INET_MAX,
};

#define IFLA_INET_MAX (__IFLA_INET_MAX - 1)



enum {
	IFLA_INET6_UNSPEC,
	IFLA_INET6_FLAGS,	
	IFLA_INET6_CONF,	
	IFLA_INET6_STATS,	
	IFLA_INET6_MCAST,	
	IFLA_INET6_CACHEINFO,	
	IFLA_INET6_ICMP6STATS,	
	IFLA_INET6_TOKEN,	
	IFLA_INET6_ADDR_GEN_MODE, 
	__IFLA_INET6_MAX
};

#define IFLA_INET6_MAX	(__IFLA_INET6_MAX - 1)

enum in6_addr_gen_mode {
	IN6_ADDR_GEN_MODE_EUI64,
	IN6_ADDR_GEN_MODE_NONE,
};


enum {
	IFLA_BR_UNSPEC,
	IFLA_BR_FORWARD_DELAY,
	IFLA_BR_HELLO_TIME,
	IFLA_BR_MAX_AGE,
	__IFLA_BR_MAX,
};

#define IFLA_BR_MAX	(__IFLA_BR_MAX - 1)

enum {
	BRIDGE_MODE_UNSPEC,
	BRIDGE_MODE_HAIRPIN,
};

enum {
	IFLA_BRPORT_UNSPEC,
	IFLA_BRPORT_STATE,	
	IFLA_BRPORT_PRIORITY,	
	IFLA_BRPORT_COST,	
	IFLA_BRPORT_MODE,	
	IFLA_BRPORT_GUARD,	
	IFLA_BRPORT_PROTECT,	
	IFLA_BRPORT_FAST_LEAVE,	
	IFLA_BRPORT_LEARNING,	
	IFLA_BRPORT_UNICAST_FLOOD, 
	__IFLA_BRPORT_MAX
};
#define IFLA_BRPORT_MAX (__IFLA_BRPORT_MAX - 1)

struct ifla_cacheinfo {
	__u32	max_reasm_len;
	__u32	tstamp;		
	__u32	reachable_time;
	__u32	retrans_time;
};

enum {
	IFLA_INFO_UNSPEC,
	IFLA_INFO_KIND,
	IFLA_INFO_DATA,
	IFLA_INFO_XSTATS,
	IFLA_INFO_SLAVE_KIND,
	IFLA_INFO_SLAVE_DATA,
	__IFLA_INFO_MAX,
};

#define IFLA_INFO_MAX	(__IFLA_INFO_MAX - 1)


enum {
	IFLA_VLAN_UNSPEC,
	IFLA_VLAN_ID,
	IFLA_VLAN_FLAGS,
	IFLA_VLAN_EGRESS_QOS,
	IFLA_VLAN_INGRESS_QOS,
	IFLA_VLAN_PROTOCOL,
	__IFLA_VLAN_MAX,
};

#define IFLA_VLAN_MAX	(__IFLA_VLAN_MAX - 1)

struct ifla_vlan_flags {
	__u32	flags;
	__u32	mask;
};

enum {
	IFLA_VLAN_QOS_UNSPEC,
	IFLA_VLAN_QOS_MAPPING,
	__IFLA_VLAN_QOS_MAX
};

#define IFLA_VLAN_QOS_MAX	(__IFLA_VLAN_QOS_MAX - 1)

struct ifla_vlan_qos_mapping {
	__u32 from;
	__u32 to;
};

enum {
	IFLA_MACVLAN_UNSPEC,
	IFLA_MACVLAN_MODE,
	IFLA_MACVLAN_FLAGS,
	IFLA_MACVLAN_MACADDR_MODE,
	IFLA_MACVLAN_MACADDR,
	IFLA_MACVLAN_MACADDR_DATA,
	IFLA_MACVLAN_MACADDR_COUNT,
	__IFLA_MACVLAN_MAX,
};

#define IFLA_MACVLAN_MAX (__IFLA_MACVLAN_MAX - 1)

enum macvlan_mode {
	MACVLAN_MODE_PRIVATE = 1, 
	MACVLAN_MODE_VEPA    = 2, 
	MACVLAN_MODE_BRIDGE  = 4, 
	MACVLAN_MODE_PASSTHRU = 8,
	MACVLAN_MODE_SOURCE  = 16,
};

enum macvlan_macaddr_mode {
	MACVLAN_MACADDR_ADD,
	MACVLAN_MACADDR_DEL,
	MACVLAN_MACADDR_FLUSH,
	MACVLAN_MACADDR_SET,
};

#define MACVLAN_FLAG_NOPROMISC	1

enum {
	IFLA_VXLAN_UNSPEC,
	IFLA_VXLAN_ID,
	IFLA_VXLAN_GROUP,	
	IFLA_VXLAN_LINK,
	IFLA_VXLAN_LOCAL,
	IFLA_VXLAN_TTL,
	IFLA_VXLAN_TOS,
	IFLA_VXLAN_LEARNING,
	IFLA_VXLAN_AGEING,
	IFLA_VXLAN_LIMIT,
	IFLA_VXLAN_PORT_RANGE,	
	IFLA_VXLAN_PROXY,
	IFLA_VXLAN_RSC,
	IFLA_VXLAN_L2MISS,
	IFLA_VXLAN_L3MISS,
	IFLA_VXLAN_PORT,	
	IFLA_VXLAN_GROUP6,
	IFLA_VXLAN_LOCAL6,
	IFLA_VXLAN_UDP_CSUM,
	IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
	IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
	__IFLA_VXLAN_MAX
};
#define IFLA_VXLAN_MAX	(__IFLA_VXLAN_MAX - 1)

struct ifla_vxlan_port_range {
	__be16	low;
	__be16	high;
};


enum {
	IFLA_BOND_UNSPEC,
	IFLA_BOND_MODE,
	IFLA_BOND_ACTIVE_SLAVE,
	IFLA_BOND_MIIMON,
	IFLA_BOND_UPDELAY,
	IFLA_BOND_DOWNDELAY,
	IFLA_BOND_USE_CARRIER,
	IFLA_BOND_ARP_INTERVAL,
	IFLA_BOND_ARP_IP_TARGET,
	IFLA_BOND_ARP_VALIDATE,
	IFLA_BOND_ARP_ALL_TARGETS,
	IFLA_BOND_PRIMARY,
	IFLA_BOND_PRIMARY_RESELECT,
	IFLA_BOND_FAIL_OVER_MAC,
	IFLA_BOND_XMIT_HASH_POLICY,
	IFLA_BOND_RESEND_IGMP,
	IFLA_BOND_NUM_PEER_NOTIF,
	IFLA_BOND_ALL_SLAVES_ACTIVE,
	IFLA_BOND_MIN_LINKS,
	IFLA_BOND_LP_INTERVAL,
	IFLA_BOND_PACKETS_PER_SLAVE,
	IFLA_BOND_AD_LACP_RATE,
	IFLA_BOND_AD_SELECT,
	IFLA_BOND_AD_INFO,
	__IFLA_BOND_MAX,
};

#define IFLA_BOND_MAX	(__IFLA_BOND_MAX - 1)

enum {
	IFLA_BOND_AD_INFO_UNSPEC,
	IFLA_BOND_AD_INFO_AGGREGATOR,
	IFLA_BOND_AD_INFO_NUM_PORTS,
	IFLA_BOND_AD_INFO_ACTOR_KEY,
	IFLA_BOND_AD_INFO_PARTNER_KEY,
	IFLA_BOND_AD_INFO_PARTNER_MAC,
	__IFLA_BOND_AD_INFO_MAX,
};

#define IFLA_BOND_AD_INFO_MAX	(__IFLA_BOND_AD_INFO_MAX - 1)

enum {
	IFLA_BOND_SLAVE_UNSPEC,
	IFLA_BOND_SLAVE_STATE,
	IFLA_BOND_SLAVE_MII_STATUS,
	IFLA_BOND_SLAVE_LINK_FAILURE_COUNT,
	IFLA_BOND_SLAVE_PERM_HWADDR,
	IFLA_BOND_SLAVE_QUEUE_ID,
	IFLA_BOND_SLAVE_AD_AGGREGATOR_ID,
	__IFLA_BOND_SLAVE_MAX,
};

#define IFLA_BOND_SLAVE_MAX	(__IFLA_BOND_SLAVE_MAX - 1)


enum {
	IFLA_VF_INFO_UNSPEC,
	IFLA_VF_INFO,
	__IFLA_VF_INFO_MAX,
};

#define IFLA_VF_INFO_MAX (__IFLA_VF_INFO_MAX - 1)

enum {
	IFLA_VF_UNSPEC,
	IFLA_VF_MAC,		
	IFLA_VF_VLAN,
	IFLA_VF_TX_RATE,	
	IFLA_VF_SPOOFCHK,	
	IFLA_VF_LINK_STATE,	
	IFLA_VF_RATE,		
	__IFLA_VF_MAX,
};

#define IFLA_VF_MAX (__IFLA_VF_MAX - 1)

struct ifla_vf_mac {
	__u32 vf;
	__u8 mac[32]; 
};

struct ifla_vf_vlan {
	__u32 vf;
	__u32 vlan; 
	__u32 qos;
};

struct ifla_vf_tx_rate {
	__u32 vf;
	__u32 rate; 
};

struct ifla_vf_rate {
	__u32 vf;
	__u32 min_tx_rate; 
	__u32 max_tx_rate; 
};

struct ifla_vf_spoofchk {
	__u32 vf;
	__u32 setting;
};

enum {
	IFLA_VF_LINK_STATE_AUTO,	
	IFLA_VF_LINK_STATE_ENABLE,	
	IFLA_VF_LINK_STATE_DISABLE,	
	__IFLA_VF_LINK_STATE_MAX,
};

struct ifla_vf_link_state {
	__u32 vf;
	__u32 link_state;
};


enum {
	IFLA_VF_PORT_UNSPEC,
	IFLA_VF_PORT,			
	__IFLA_VF_PORT_MAX,
};

#define IFLA_VF_PORT_MAX (__IFLA_VF_PORT_MAX - 1)

enum {
	IFLA_PORT_UNSPEC,
	IFLA_PORT_VF,			
	IFLA_PORT_PROFILE,		
	IFLA_PORT_VSI_TYPE,		
	IFLA_PORT_INSTANCE_UUID,	
	IFLA_PORT_HOST_UUID,		
	IFLA_PORT_REQUEST,		
	IFLA_PORT_RESPONSE,		
	__IFLA_PORT_MAX,
};

#define IFLA_PORT_MAX (__IFLA_PORT_MAX - 1)

#define PORT_PROFILE_MAX	40
#define PORT_UUID_MAX		16
#define PORT_SELF_VF		-1

enum {
	PORT_REQUEST_PREASSOCIATE = 0,
	PORT_REQUEST_PREASSOCIATE_RR,
	PORT_REQUEST_ASSOCIATE,
	PORT_REQUEST_DISASSOCIATE,
};

enum {
	PORT_VDP_RESPONSE_SUCCESS = 0,
	PORT_VDP_RESPONSE_INVALID_FORMAT,
	PORT_VDP_RESPONSE_INSUFFICIENT_RESOURCES,
	PORT_VDP_RESPONSE_UNUSED_VTID,
	PORT_VDP_RESPONSE_VTID_VIOLATION,
	PORT_VDP_RESPONSE_VTID_VERSION_VIOALTION,
	PORT_VDP_RESPONSE_OUT_OF_SYNC,
	
	PORT_PROFILE_RESPONSE_SUCCESS = 0x100,
	PORT_PROFILE_RESPONSE_INPROGRESS,
	PORT_PROFILE_RESPONSE_INVALID,
	PORT_PROFILE_RESPONSE_BADSTATE,
	PORT_PROFILE_RESPONSE_INSUFFICIENT_RESOURCES,
	PORT_PROFILE_RESPONSE_ERROR,
};

struct ifla_port_vsi {
	__u8 vsi_mgr_id;
	__u8 vsi_type_id[3];
	__u8 vsi_type_version;
	__u8 pad[3];
};



enum {
	IFLA_IPOIB_UNSPEC,
	IFLA_IPOIB_PKEY,
	IFLA_IPOIB_MODE,
	IFLA_IPOIB_UMCAST,
	__IFLA_IPOIB_MAX
};

enum {
	IPOIB_MODE_DATAGRAM  = 0, 
	IPOIB_MODE_CONNECTED = 1, 
};

#define IFLA_IPOIB_MAX (__IFLA_IPOIB_MAX - 1)



enum {
	IFLA_HSR_UNSPEC,
	IFLA_HSR_SLAVE1,
	IFLA_HSR_SLAVE2,
	IFLA_HSR_MULTICAST_SPEC,	
	IFLA_HSR_SUPERVISION_ADDR,	
	IFLA_HSR_SEQ_NR,
	__IFLA_HSR_MAX,
};

#define IFLA_HSR_MAX (__IFLA_HSR_MAX - 1)

#endif 
