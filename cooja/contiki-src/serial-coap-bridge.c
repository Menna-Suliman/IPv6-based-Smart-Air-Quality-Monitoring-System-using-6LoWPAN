#include "contiki.h"
#include "coap-blocking-api.h"
#include "dev/serial-line.h"
#include "net/routing/routing.h"
#include "sys/log.h"

#include <string.h>

#define LOG_MODULE "Serial-CoAP-Bridge"
#define LOG_LEVEL LOG_LEVEL_INFO

#define SERVER_EP "coap://[fd00::201:1:1:1]"
#define SERVICE_URL "air"

static coap_endpoint_t server_ep;
static coap_message_t request[1];

static void
client_chunk_handler(coap_message_t *response)
{
  const uint8_t *chunk = NULL;

  if(response == NULL) {
    LOG_INFO("No CoAP response received\n");
    return;
  }

  int len = coap_get_payload(response, &chunk);

  if(len > 0) {
    LOG_INFO("CoAP response: '%.*s'\n", len, (const char *)chunk);
  } else {
    LOG_INFO("CoAP response received\n");
  }
}

PROCESS(serial_coap_bridge_process, "Serial to CoAP Bridge");
AUTOSTART_PROCESSES(&serial_coap_bridge_process);

PROCESS_THREAD(serial_coap_bridge_process, ev, data)
{
  PROCESS_BEGIN();

  serial_line_init();
  coap_endpoint_parse(SERVER_EP, strlen(SERVER_EP), &server_ep);

  LOG_INFO("Serial-to-CoAP bridge started\n");
  LOG_INFO("Waiting for STM32/ESP-01 payloads from serial socket\n");

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);

    if(data != NULL) {
      char *payload = (char *)data;

      LOG_INFO("Serial payload received: %s\n", payload);

      if(NETSTACK_ROUTING.node_is_reachable()) {
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request, SERVICE_URL);
        coap_set_header_content_format(request, TEXT_PLAIN);
        coap_set_payload(request, (uint8_t *)payload, strlen(payload));

        LOG_INFO("Forwarding payload to CoAP server /air\n");

        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
      } else {
        LOG_INFO("RPL network not reachable yet\n");
      }
    }
  }

  PROCESS_END();
}
