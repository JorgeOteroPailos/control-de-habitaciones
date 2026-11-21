# Módulo Clima y Hora Local (`flows_george.json`)

Integración de datos meteorológicos exteriores y referencia horaria en el panel **RoomSense** (Node-RED + Dashboard 2.0).

## Componentes del flujo
* **API OpenWeatherMap (`A Estrada, ES`):** Consulta y extrae temperatura exterior (`tempc`), humedad (`humidity`) y estado climático (`detail`) mediante nodos `change`.
* **Hora Local (`Europe/Madrid`):** Actualización cada segundo con `inject` + `function`.
* **Dashboard 2.0:** Tarjeta **`Exterior Clima A Estrada`** integrada en la página principal `RoomSense` con dos galgas (`ui-gauge`) y dos indicadores de texto (`ui-text`).

## Captura
<img width="1574" height="726" alt="imagen" src="https://github.com/user-attachments/assets/bd0af867-76c3-48ff-9bad-70fad4531c24" />


## Uso
1. Instalar `node-red-node-openweathermap` y `@flowfuse/node-red-dashboard`.
2. Importar `flows_george.json` en Node-RED.
3. Añadir tu **API Key** en el nodo `Clima A Estrada` y pulsar **Deploy**.
