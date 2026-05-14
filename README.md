# IPv6-based Smart Air Quality Monitoring System using 6LoWPAN

This project implements and simulates an IPv6-based smart air quality monitoring network using 6LoWPAN. The system is designed for low-power wireless sensor communication and supports multi-hop routing, lightweight application-layer messaging, and network resiliency.

## Overview

The network consists of a 6LoWPAN wireless sensor network with one Border Router and multiple sensor nodes. The system uses IPv6 addressing, RPL routing, and CoAP/UDP communication to transmit air quality data from sensor nodes to a centralized monitoring station.

## Main Features

- IPv6-based wireless sensor network
- 6LoWPAN adaptation layer
- RPL routing protocol
- CoAP/UDP application communication
- Border Router for network bridging
- Multi-node Cooja simulation
- Wireshark packet verification
- Self-healing network behavior
- Link-layer security verification

## Network Architecture

The simulated network contains:

- One Border Router / RPL Root
- Five wireless sensor nodes
- IPv6 addressing using the `fd00::/64` prefix
- CoAP communication over UDP port `5683`
- RPL-based mesh routing

## Project Structure

- `cooja/` - Cooja simulation files
- `docs/` - project documentation
- `screenshots/` - Cooja, Wireshark, and hardware screenshots
- `captures/` - selected Wireshark packet captures
- `contiki-src/` - Contiki source files, if modified

## Cooja Simulation Files

The Cooja simulation files are located in:

```text
cooja/
```

Main simulation files:

```text
cooja/project-network.csc
cooja/test.csc
```

## How to Run the Cooja Simulation

1. Open Contiki/Cooja.
2. Load one of the simulation files from the `cooja/` folder.
3. Start the simulation.
4. Observe the mote output, radio messages, and packet transmission.
5. Use Wireshark to verify 6LoWPAN, RPL, UDP, and CoAP packets.

## Protocol Stack

The project uses the following protocol stack:

- Application Layer: CoAP / UDP
- Network Layer: IPv6 with RPL routing
- Adaptation Layer: 6LoWPAN IPHC
- Link Layer: IEEE 802.15.4
- Physical Layer: Low-power wireless communication

## Verification

The system was verified using:

- Cooja simulation topology
- Mote output logs
- Wireshark packet inspection
- RPL DODAG verification
- CoAP request/response analysis
- UDP payload verification
- Self-healing topology test
- Link-layer security verification

## Tools Used

- Contiki / Cooja
- Wireshark
- IPv6
- 6LoWPAN
- RPL
- CoAP / UDP