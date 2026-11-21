# Módulos Clima, Actuadores, Nuevos Ambientes y Sinóptico SCADA

Contribución al panel **RoomSense** (Node-RED + Dashboard 2.0) para integrar datos meteorológicos exteriores, referencia horaria, control bidireccional por MQTT, expansión a 5 ambientes y representación visual tipo SCADA.

## Archivos incluidos
* **`flows_george.json` (Clima y Hora Local):**
  * **API OpenWeatherMap (`Santiago de Compostela, ES`):** Extrae temperatura (`tempc`), humedad (`humidity`) y estado climático (`detail`) hacia la tarjeta **`Exterior Clima Santiago de Compostela`**.
  * **Hora Local (`Europe/Madrid`):** Actualización cada segundo mediante `inject` + `function`.
* **`flows_actuadores_george.json` (Control de Actuadores MQTT):**
  * **Tarjeta `Control de Actuadores`:** Selector dinámico de ambiente con interruptores para **Luz**, **Ventana**, **Calefacción** y selector de **Modo** (`AUTO`, `VENTILAR`, `CALEFACCION`), publicando comandos en `roomsenseg3/{hab}/actuadores` sobre `broker.emqx.io` y confirmando la recepción en tiempo real.
* **`flows_scada_george.json` (Ambientes 4-5 y Sinóptico SCADA):**
  * **Expansión a 5 ambientes:** Creación del **Ambiente 4 (Pasillo Distribuidor)** con sensores de presencia y lux + controles de luz/extractor, y del **Ambiente 5 (Terraza / Patio Exterior)** con sensores de lluvia/UV + controles de luz exterior/toldo motorizado.
  * **Sinóptico SCADA Interactivo (`ui-template` SVG):** Plano de planta completo que refleja en tiempo real el estado de los 5 ambientes y permite operar directamente sobre sus actuadores mediante clics en el plano.

## Capturas
<img width="1584" height="736" alt="imagen" src="https://github.com/user-attachments/assets/4a540642-aec7-4abc-a5f9-84b5861b7f9f" />
<img width="1588" height="734" alt="imagen" src="https://github.com/user-attachments/assets/69868880-f67f-437e-ae15-1126e9474f5a" />
<img width="3166" height="1574" alt="imagen" src="https://github.com/user-attachments/assets/0ea6168b-5def-4f30-afa4-fb0ae3bb0423" />

## Uso
1. Instalar `node-red-node-openweathermap` y `@flowfuse/node-red-dashboard`.
2. Importar `flows_george.json`, `flows_actuadores_george.json` y `flows_scada_george.json` en Node-RED.
3. Configurar tu **API Key** en el nodo `Clima Santiago de Compostela` y pulsar **Deploy**.
