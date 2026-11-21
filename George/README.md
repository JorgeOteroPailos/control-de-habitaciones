# Módulos Clima, Actuadores, Nuevos Ambientes y Sinóptico SCADA

Contribución al panel **RoomSense** (Node-RED + Dashboard 2.0) para integrar datos meteorológicos exteriores, referencia horaria, control bidireccional por MQTT, expansión a 5 ambientes y representación visual tipo SCADA.

## Archivos incluidos
* **`flows_george.json` (Clima y Hora Local):**
  * **API OpenWeatherMap (`A Estrada, ES`):** Extrae temperatura (`tempc`), humedad (`humidity`) y estado climático (`detail`) hacia la tarjeta **`Exterior Clima A Estrada`**.
  * **Hora Local (`Europe/Madrid`):** Actualización cada segundo mediante `inject` + `function`.
* **`flows_actuadores_george.json` (Control de Actuadores MQTT):**
  * **Tarjeta `Control de Actuadores`:** Selector dinámico de ambiente con interruptores para **Luz**, **Ventana**, **Calefacción** y selector de **Modo** (`AUTO`, `VENTILAR`, `CALEFACCION`), publicando comandos en `roomsenseg3/{hab}/actuadores` sobre `broker.emqx.io` y confirmando la recepción en tiempo real.
* **`flows_scada_george.json` (Ambientes 4-5 y Sinóptico SCADA):**
  * **Expansión a 5 ambientes:** Creación del **Ambiente 4 (Pasillo Distribuidor)** con sensores de presencia y lux + controles de luz/extractor, y del **Ambiente 5 (Terraza / Patio Exterior)** con sensores de lluvia/UV + controles de luz exterior/toldo motorizado.
  * **Sinóptico SCADA Interactivo (`ui-template` SVG):** Plano de planta completo que refleja en tiempo real el estado de los 5 ambientes y permite operar directamente sobre sus actuadores mediante clics en el plano.

## Capturas
<img width="1580" height="730" alt="imagen" src="https://github.com/user-attachments/assets/b216ad2b-86f1-48a4-afb2-ed38879de474" />
<img width="3188" height="1006" alt="imagen" src="https://github.com/user-attachments/assets/005b9133-dc76-4d4c-a73e-a82f3e9535bf" />
<img width="3166" height="1574" alt="imagen" src="https://github.com/user-attachments/assets/cd0f520d-45c5-4fb5-8de3-96dd2fb52cf7" />

## Uso
1. Instalar `node-red-node-openweathermap` y `@flowfuse/node-red-dashboard`.
2. Importar `flows_george.json`, `flows_actuadores_george.json` y `flows_scada_george.json` en Node-RED.
3. Configurar tu **API Key** en el nodo `Clima A Estrada` y pulsar **Deploy**.
