# Organización del equipo y reparto de responsabilidades

## Objetivo

Este documento establece la distribución final de las áreas del proyecto **Control de habitaciones** entre Jorge, Federico, Mohamed, Manuel y George.

Cada persona tiene **cuatro roles**, ordenados del primero al cuarto según la importancia o carga estimada. Los roles con mayor carga están destacados como prioritarios; los demás se consideran apoyo o responsabilidades compartidas.

## Reparto de roles

| Persona | 1.º — Mayor prioridad | 2.º | 3.º | 4.º — Menor prioridad |
|---|---|---|---|---|
| **Federico** | Hardware | Backend | Firmware edge | Pruebas y calidad |
| **Manuel** | Frontend | Gestión e integración | Pruebas y calidad | Documentación |
| **Jorge** | Gestión e integración | Frontend | Backend | Documentación |
| **Mohamed** | Backend | Firmware edge | Hardware | Documentación |
| **George** | Pruebas y calidad | Documentación | Gestión e integración | Frontend |

## Criterios del reparto

- **Frontend:** principal responsabilidad compartida por Manuel y Jorge. Manuel lo sitúa como su rol número 1 y Jorge como su rol número 2.
- **Hardware:** papel principal de Federico en su posición número 1, dado su peso y especialidad.
- **Backend:** Mohamed lo mantiene como prioridad número 1; Federico ocupa el segundo puesto y Jorge el tercero para equilibrar la carga del área.
- **Firmware edge:** carga técnica compartida entre Mohamed y Federico, sin convertirla en una responsabilidad exclusiva.
- **Pruebas y calidad:** George coordina el área; Manuel y Federico aportan apoyo con diferente peso.
- **Gestión e integración:** Jorge coordina el área y Manuel y George aportan apoyo transversal.
- **Documentación:** George la coordina; el resto participa según su relación con cada componente.

## Equipamiento de cargas

Los roles se han ordenado considerando que hardware, backend, firmware y frontend son los roles más intensivos, seguidos de gestión, pruebas y calidad. Las responsabilidades están repartidas de forma que:

- cada persona tenga exactamente cuatro roles;
- Federico tenga **Hardware** primero y luego Backend;
- Manuel tenga **Frontend** primero;
- Jorge tenga **Frontend** segundo;
- no haya una sola persona concentrando todas las responsabilidades más pesadas;
- las áreas transversales se repartan entre varias personas.

## Forma de trabajo

1. **Acordar interfaces antes de integrar.** Backend y frontend concretan API y formatos de datos; hardware y firmware acuerdan conexiones, señales y comportamiento esperado.
2. **Trabajar por funcionalidades pequeñas.** Cada tarea debe indicar su responsable principal y las personas que apoyan.
3. **Revisar los cambios entre compañeros.** Otra persona debe revisar cambios relevantes, especialmente los que afectan a interfaces.
4. **Probar el flujo completo.** Además de pruebas por componente, el equipo comprobará el recorrido completo entre interfaz, backend y dispositivo.
5. **Mantener la documentación al día.** La documentación se actualizará junto con cambios de arquitectura, configuración, conexiones o uso.
6. **Revisar el reparto periódicamente.** Si una fase concentra demasiada carga en una persona, el equipo podrá redistribuir tareas manteniendo claros los responsables principales.

## Revisión inicial

Esta distribución es una propuesta de partida. En la primera revisión del proyecto, el equipo deberá confirmar preferencias, estimar el esfuerzo pendiente y ajustar las prioridades si el trabajo real requiere modificar el reparto.
