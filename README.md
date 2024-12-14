# CAN2040 Experiment Documentation

This README documents observations from experiments using two Pico microcontrollers configured with CAN2040. The setup involves one Pico continuously transmitting a high-priority message, while the other receives this message and periodically transmits a low-priority message.

## Experiment Setup

- **Pico 1**: Continuously transmits high-priority messages
- **Pico 2**: Receives high-priority messages and periodically transmits low-priority messages

## Observations

### Activity 1: High-Priority Message Dominance

In this initial setup, we observed:

- High-priority messages were successfully transmitted and received
- Low-priority messages were not received at all

**Explanation**: This behavior is due to CAN's inherent multiplexing logic control. When a 3V (logic 0) high-priority signal is received, it takes precedence, and the low-priority signal is ignored. This prioritization is crucial in vehicle operations, ensuring critical functions (like door handles) take precedence over less critical ones (like mirror adjustments).

**Oscilloscope Reading**: The low-priority signal (logic 1) showed a 1.5V signal on the oscilloscope but wasn't displayed on our screen.

### Activity 2: Introducing Delay in High-Priority Node

To allow low-priority messages through, we introduced a short busy-wait delay in the high-priority babbling node:

- A small delay (approximately 10 ms) was sufficient to allow low-priority messages to reach the high-priority babbling transceiver
- Low-priority messages began to be received and processed

## Code Reference

The code used in this experiment is attached for reference (see `can_tx.c`).

## Conclusion

These experiments demonstrate the priority-based nature of CAN communication and how timing adjustments can affect message transmission in a multi-node CAN setup.