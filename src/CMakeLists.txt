# This is the main binary. List your C files here.
add_executable(can_tx
    can_tx.c
    )

add_executable(can_rx
    can_rx.c
)

add_executable(can_tx_rx
    can_tx_rx.c
)

pico_set_program_name(can_tx "test")
pico_set_program_version(can_tx "0.1")

pico_set_program_name(can_rx "test")
pico_set_program_version(can_rx "0.1")

pico_set_program_name(can_tx_rx "test")
pico_set_program_version(can_tx_rx "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(can_tx 0)
pico_enable_stdio_usb(can_tx 1)

pico_enable_stdio_uart(can_rx 0)
pico_enable_stdio_usb(can_rx 1)

pico_enable_stdio_uart(can_tx_rx 0)
pico_enable_stdio_usb(can_tx_rx 1)

# Add the libraries to the build
target_link_libraries(can_tx PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)

target_link_libraries(can_rx PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)

target_link_libraries(can_tx_rx PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(can_tx PRIVATE
        pico_cyw43_arch_none
    )
    target_link_libraries(can_rx PRIVATE
        pico_cyw43_arch_none
    )
    target_link_libraries(can_tx_rx PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(can_tx)
pico_add_extra_outputs(can_rx)
pico_add_extra_outputs(can_tx_rx)

add_custom_target(flash_tx picotool load -f $<TARGET_FILE:can_tx> DEPENDS can_tx)
add_custom_target(flash_rx picotool load -f $<TARGET_FILE:can_rx> DEPENDS can_rx)
add_custom_target(flash_tx_rx picotool load -f $<TARGET_FILE:can_tx_rx> DEPENDS can_tx_rx)