#include "contiki.h"
#include "coap-engine.h"
#include "net/routing/routing.h"
#include "sys/log.h"

#include <string.h>

#define LOG_MODULE "CoAP-Server"
#define LOG_LEVEL LOG_LEVEL_INFO

static void res_post_handler(coap_message_t *request,
                             coap_message_t *response,
                             uint8_t *buffer,
                             uint16_t preferred_size,
                             int32_t *offset);

RESOURCE(res_air,
         "title=\"Air Quality Receiver\";rt=\"Text\"",
         NULL,
         res_post_handler,
         NULL,
         NULL);

static void
res_post_handler(coap_message_t *request,
                 coap_message_t *response,
                 uint8_t *buffer,
                 uint16_t preferred_size,
                 int32_t *offset)
{
  const uint8_t *payload = NULL;
  int len = coap_get_payload(request, &payload);

  if(len > 0) {
    LOG_INFO("Received CoAP POST payload: '%.*s'\n", len, (const char *)payload);
  } else {
    LOG_INFO("Received empty CoAP POST\n");
  }

  const char *reply = "ACK";
  coap_set_status_code(response, CONTENT_2_05);
  coap_set_header_content_format(response, TEXT_PLAIN);
  coap_set_payload(response, reply, strlen(reply));
}

PROCESS(coap_server_process, "CoAP Air Quality Server");
AUTOSTART_PROCESSES(&coap_server_process);

PROCESS_THREAD(coap_server_process, ev, data)
{
  PROCESS_BEGIN();

  NETSTACK_ROUTING.root_start();

  coap_engine_init();
  coap_activate_resource(&res_air, "air");

  LOG_INFO("CoAP server started as RPL root. Resource: /air\n");

  PROCESS_END();
}
