LIB =	network

SRCS =				\
	address			\
	bundle_broadcast	\
	bundle			\
	channel			\
	common			\
	delayed_channels	\
	error_reporter		\
	event_dispatcher	\
	event_poller		\
	encryption_filter	\
	fixed_messages		\
	interface_defs		\
	message_handler		\
	listener_receiver	\
	network_stats		\
	network_interface	\
	packet_filter		\
	packet_reader		\
	packet_sender		\
	packet_receiver		\
	poller_epoll		\
	poller_select		\
	endpoint		\
	tcp_packet		\
	tcp_packet_receiver	\
	tcp_packet_sender	\
	udp_packet		\
	udp_packet_receiver	\
	websocket_packet_reader	\
	websocket_packet_filter	\
	websocket_protocol	

USE_OPENSSL = 1

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

include $(KBE_ROOT)/src/build/common.mak