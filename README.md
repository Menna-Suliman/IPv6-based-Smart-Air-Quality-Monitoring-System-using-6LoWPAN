\# IPv6-based Smart Air Quality Monitoring System using 6LoWPAN



This project implements and simulates an IPv6-based smart air quality monitoring network using 6LoWPAN. The system is designed for low-power wireless sensor communication and supports multi-hop routing, lightweight application-layer messaging, and network resiliency.



\## Overview



The network consists of a 6LoWPAN wireless sensor network with one Border Router and multiple sensor nodes. The system uses IPv6 addressing, RPL routing, and CoAP/UDP communication to transmit air quality data from sensor nodes to a centralized monitoring station.



\## Main Features



\- IPv6-based wireless sensor network

\- 6LoWPAN adaptation layer

\- RPL routing protocol

\- CoAP/UDP application communication

\- Border Router for network bridging

\- Multi-node Cooja simulation

\- Wireshark packet verification

\- Self-healing network behavior

\- Link-layer security verification



\## Network Architecture



The simulated network contains:



\- One Border Router / RPL Root

\- Five wireless sensor nodes

\- IPv6 addressing using the `fd00::/64` prefix

\- CoAP communication over UDP port `5683`

\- RPL-based mesh routing



\## Project Structure



```text

cooja/

&#x20; Cooja simulation files



docs/

&#x20; Project documentation







