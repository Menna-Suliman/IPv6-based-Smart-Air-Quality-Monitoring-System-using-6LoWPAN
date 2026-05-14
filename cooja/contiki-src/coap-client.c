#include "contiki.h"
#include "coap-blocking-api.h"
#include "net/routing/routing.h"
#include "net/linkaddr.h"
#include "sys/etimer.h"
#include "sys/log.h"

#include <stdio.h>
#include <string.h>

#define LOG_MODULE "CoAP-Client"
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
    LOG_INFO("CoAP request timed out\n");
    return;
  }

  int len = coap_get_payload(response, &chunk);

  if(len > 0) {
    LOG_INFO("Received CoAP response: '%.*s'\n", len, (const char *)chunk);
  } else {
    LOG_INFO("Received CoAP response with no payload\n");
  }
}

PROCESS(coap_client_process, "CoAP Air Quality Client");
AUTOSTART_PROCESSES(&coap_client_process);

PROCESS_THREAD(coap_client_process, ev, data)
{
  static struct etimer timer;
  static int count = 0;
  char payload[48];

  PROCESS_BEGIN();

  coap_endpoint_parse(SERVER_EP, strlen(SERVER_EP), &server_ep);

  etimer_set(&timer, CLOCK_SECOND * 10);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    if(NETSTACK_ROUTING.node_is_reachable()) {
      int node_id = linkaddr_node_addr.u8[LINKADDR_SIZE - 1];
      int aqi = 300 + node_id * 7 + (count % 30);
      int temp = 24 + node_id;
      int hum = 50 + (count % 10);
      int gas = (aqi > 350) ? 1 : 0;

      if(node_id == 4) {
        snprintf(payload, sizeof(payload), "NODE4 TEMP=%d HUM=%d", temp, hum);
      } else if(node_id == 5) {
        snprintf(payload, sizeof(payload), "NODE5 GAS=%d", gas);
      } else {
        snprintf(payload, sizeof(payload), "NODE%d AQI=%d", node_id, aqi);
      }

      coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
      coap_set_header_uri_path(request, SERVICE_URL);
      coap_set_header_content_format(request, TEXT_PLAIN);
      coap_set_payload(request, (uint8_t *)payload, strlen(payload));

      LOG_INFO("Sending CoAP POST to /air: %s\n", payload);

      COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);

      count++;
    } else {
      LOG_INFO("Network not reachable yet\n");
    }

    etimer_reset(&timer);
  }

  PROCESS_END();
}
