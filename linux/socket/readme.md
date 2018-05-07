学习tcp/ip比较好的工具有
tcpdump
wireshark
scapy (python)
scoket (python)
以及http://www.tcpdump.org/related.html

 Project List

ECap

    Ecap (external capture) is a distributed network sniffer with a web front-end.

    Ecap was written many years ago in 2005, but a post on the tcpdump-workers mailing list requested a similar application... so here it is.

    It would be fun to update it and work on it again if there's any interest. 
Network Expect
    Network Expect is a framework that allows to easily build tools that can interact with network traffic. Following a script, traffic can be injected into the network, and decisions can be taken, and acted upon, based on received network traffic. An interpreted language provides branching and high-level control structures to direct the interaction with the network. Network Expect uses libpcap for packet capture and libwireshark (from the Wireshark project) for packet dissection tasks. (GPL, BSD/Linux/OSX)
    Submitted by: Eloy Paris {peloy at chapus.net}

Socket Sentry
    Socket Sentry is a real-time network traffic monitor for KDE Plasma in the same spirit as tools like iftop and netstat.
    Submitted by: Rob Hasselbaum {rob at hasselbaum.net}

Tools for modeling the user-traffic
    This is a page with links to various tools, many of which can process tcpdump output and, for example, generate statistics.

LibNet
    Libnet is a collection of routines to help with the construction and handling of network packets. It provides a portable framework for low-level network packet shaping, handling and injection. Libnet features portable packet creation interfaces at the IP layer and link layer, as well as a host of supplementary and complementary functionality. Using libnet, quick and simple packet assembly applications can be whipped up with little effort.

tcpreplay
    Replays a pcap file on an interface using libnet.

Sniff
    Makes output from the tcpdump program easier to read and parse.

TTT: Tele Traffic Tapper
    TTT is yet another descendant of tcpdump but it is capable of real-time, graphical, and remote traffic-monitoring. ttt won't replace tcpdump, rather, it helps you find out what to look into with tcpdump. ttt monitors the network and automatically picks up the main contributors of the traffic within the time window. The graphs are updated every second by default.

Internet Traffic Archive
    The Internet Traffic Archive is a moderated repository to support widespread access to traces of Internet network traffic, sponsored by ACM SIGCOMM. The traces can be used to study network dynamics, usage characteristics, and growth patterns, as well as providing the grist for trace-driven simulations. The archive is also open to programs for reducing raw trace data to more manageable forms, for generating synthetic traces, and for analyzing traces.

EtherApe
    EtherApe is a graphical network monitor for Unix modeled after etherman. Featuring link layer, ip and TCP modes, it displays network activity graphically. Hosts and links change in size with traffic. Color coded protocols display. It supports Ethernet, FDDI, Token Ring, ISDN, PPP and SLIP devices. It can filter traffic to be shown, and can read traffic from a file as well as live from the network.

TCPslice
    TCPslice is a tool for extracting portions of packet trace files generated using tcpdump's -w flag. It can combine multiple trace files, and/or extract portions of one or more traces based on time. TCPslice originally comes from LBL and now is maintained by tcpdump.org. We have not made formal releases of it as yet, although there have been some updates to it.

TCPTrace
    TCPTrace analyzes the behavior of captured TCP streams, and accepts many trace file formats (including pcap). It provides connection statistics and several types of graphs, including the widely-used time-sequence graphs.

tcpflow
    tcpflow is a program that captures data transmitted as part of TCP connections (flows), and stores the data in a way that is convenient for protocol analysis or debugging. A program like 'tcpdump' shows a summary of packets seen on the wire, but usually doesn't store the data that's actually being transmitted. In contrast, tcpflow reconstructs the actual data streams and stores each flow in a separate file for later analysis.

snort
    Snort is an open source network intrusion prevention and detection system (IDS/IPS) developed by Sourcefire. Combining the benefits of signature, protocol and anomaly-based inspection, Snort is the most widely deployed IDS/IPS technology worldwide. With millions of downloads and approximately 300,000 registered users, Snort has become the de facto standard for IPS.

Scapy
    Scapy is a powerful interactive packet manipulation program. It is able to forge or decode packets of a wide number of protocols, send them on the wire, capture them, match requests and replies, and much more. It can easily handle most classical tasks like scanning, tracerouting, probing, unit tests, attacks or network discovery (it can replace hping, 85% of nmap, arpspoof, arp-sk, arping, tcpdump, tethereal, p0f, etc.). It also performs very well at a lot of other specific tasks that most other tools can't handle, like sending invalid frames, injecting your own 802.11 frames, combining technics (VLAN hopping+ARP cache poisoning, VOIP decoding on WEP encrypted channel, ...), etc. 
Bro
    Bro is an open-source, Unix-based Network Intrusion Detection System (NIDS) that passively monitors network traffic and looks for suspicious activity. Bro detects intrusions by first parsing network traffic to extract its application-level semantics and then executing event-oriented analyzers that compare the activity with patterns deemed troublesome. Its analysis includes detection of specific attacks (including those defined by signatures, but also those defined in terms of events) and unusual activities (e.g., certain hosts connecting to certain services, or patterns of failed connection attempts).

Network Top
    ntop is a network traffic probe that shows the network usage, similar to what the popular top Unix command does. ntop is based on libpcap and it has been written in a portable way in order to virtually run on every Unix platform and on Win32 as well.

Wireshark
    A free network protocol analyzer for Unix and Windows. It allows you to examine data from a live network or from a capture file on disk. You can interactively browse the capture data, viewing summary and detail information for each packet. Wireshark has several powerful features, including a rich display filter language and the ability to view the reconstructed stream of a TCP session.

CoralReef
    CoralReef is a software suite developed by CAIDA to analyze data collected by passive Internet traffic monitors. It provides a programming library libcoral, similar to libpcap with extensions for ATM and other network types, which is available from both C and Perl. The software presently supports dedicated PC boxes using OC3mon and OC12mon cards that collect traffic data in real time, as well as reading from pcap tracefiles. Version 3.4 to be released soon supports listening via bpf enabled devices. CoralReef includes drivers, analysis, web report generation, examples, and capture software. This package is maintained by CAIDA developers with the support and collaboration of the Internet measurement community.

TCPstat
    tcpstat reports certain network interface statistics much like vmstat does for system statistics. tcpstat gets its information by either monitoring a specific interface, or by reading previously saved tcpdump data from a file.

NetDude
    netdude (NETwork DUmp data Displayer and Editor). From their webpage, "it is a GUI-based tool that allows you to make detailed changes to packets in tcpdump tracefiles."

Usenix 93 paper on BPF
    The libpcap interface supports a filtering mechanism based on the architecture in the BSD packet filter. BPF is described in the 1993 Winter Usenix paper ``The BSD Packet Filter: A New Architecture for User-level Packet Capture''.

        The original is at: ftp://ftp.ee.lbl.gov/papers/bpf-usenix93.ps.Z
        A copy is here. (compressed postscript: 144K) http://www.tcpdump.org/papers/bpf-usenix93.ps.Z
        Gzip'ed postscript: http://www.tcpdump.org/papers/bpf-usenix93.ps.gz (100K)
        For the Post-script impaired, here is some PDF:bpf-usenix93.pdf (135K)

BPF for Ultrix
    A distribution of BPF for Ultrix 4.2, with both source code and binary modules.

BPF+: Exploiting Global Data-flow Optimization in a Generalized Packet Filter Architecture
    By Andrew Begel, Steven McCanne, and Susan Graham, originally at: http://www.cs.berkeley.edu/~abegel/sigcomm99/bpf+.ps

DPF
    A paper presented at SIGCOMM '96 on an enhanced version of BPF.

Win32 info
    An extract of a message from Guy Harris on state of WinPcap and WinDump.

Xplot
    The program xplot was written in the late 1980s to support the analysis of TCP packet traces.

Multitail
    MultiTail now has a colorscheme included for monitoring the tcpdump output. It can also filter, convert timestamps to timestrings and much more.

netsniff-ng
    netsniff-ng is a free, performant Linux network analyzer and networking toolkit.
    Submitted by: Daniel Borkmann

libcrafter
    Libcrafter is a high level library for C++ designed to make easier the creation and decoding of network packets. It is able to craft or decode packets of most common network protocols, send them on the wire, capture them and match requests and replies.
    Submitted by: Esteban Pellegrino

pcapfix
    pcapfix is a repair tool for corrupted pcap and pcapng files. It checks for an intact pcap global header and packet block and repairs it if there are any corrupted bytes. If a header is not present, one is created and added to the beginning of the file. It then tries to find pcap packet headers or packet blocks, and checks and repairs them. 
httpflow
    Packet capture and analysis utility similar to tcpdump for HTTP. 
