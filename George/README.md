# Módulos Clima, Hora Local y Control de Actuadores

Contribución al panel **RoomSense** (Node-RED + Dashboard 2.0) para integrar datos meteorológicos exteriores, referencia horaria y control remoto bidireccional por MQTT.

## Archivos incluidos
* **`flows_george.json` (Clima y Hora Local):**
  * **API OpenWeatherMap (`A Estrada, ES`):** Extrae temperatura (`tempc`), humedad (`humidity`) y estado climático (`detail`) hacia la tarjeta **`Exterior Clima A Estrada`**.
  * **Hora Local (`Europe/Madrid`):** Actualización cada segundo mediante `inject` + `function`.
* **`flows_actuadores_george.json` (Control de Actuadores MQTT):**
  * **Tarjeta `Control de Actuadores`:** Selector dinámico de habitación (`hab1`, `hab2`, `hab3`) con interruptores para **Luz**, **Ventana**, **Calefacción** y selector de **Modo** (`AUTO`, `VENTILAR`, `CALEFACCION`).
  * **Comunicación bidireccional:** Publica comandos en `roomsenseg3/{hab}/actuadores` sobre `broker.emqx.io` y muestra en tiempo real la confirmación recibida desde los nodos.

## Captura
<img width="3200" height="760" alt="imagen" src="https://github.com/user-attachments/assets/f4adbbe1-733a-48ce-a8fe-45131738c5b1" />


## Uso
1. Instalar `node-red-node-openweathermap` y `@flowfuse/node-red-dashboard`.
2. Importar `flows_george.json` y `flows_actuadores_george.json` en Node-RED.
3. Configurar tu **API Key** en el nodo `Clima A Estrada` y pulsar **Deploy**.
