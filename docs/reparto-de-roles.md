# Organización del equipo y reparto de responsabilidades

## Objetivo

Este documento establece una primera distribución de las áreas del proyecto **Control de habitaciones** entre Jorge, Federico, Mohamed, Manuel y George. La propuesta respeta las preferencias iniciales —Federico más centrado en hardware y Jorge y Manuel en frontend— y reparte las áreas de mayor carga entre varias personas.

La asignación indica quién coordina cada área y quién la apoya; no crea silos. Las decisiones que afecten a interfaces entre componentes se acuerdan entre las personas implicadas.

## Reparto propuesto

| Área | Responsable principal | Apoyo | Alcance |
|---|---|---|---|
| **Backend** | Mohamed | Jorge | Servicios, API, lógica de aplicación e integración con los datos del sistema. Jorge apoya especialmente en el contrato entre backend y frontend. |
| **Frontend** | Jorge y Manuel (corresponsables) | Mohamed | Interfaz de usuario, vistas y comunicación con el backend. Jorge y Manuel comparten planificación y revisión; pueden repartirse pantallas o funcionalidades según avance el proyecto. |
| **Firmware edge** | Mohamed | Federico | Lógica que se ejecuta en el dispositivo edge y comunicación con sensores, actuadores y backend. Mohamed coordina el software; Federico ayuda con las particularidades del hardware. |
| **Hardware** | Federico | Mohamed | Selección y conexión de componentes, montaje, alimentación y comprobación del funcionamiento físico. Federico concentra aquí su dedicación principal. |
| **Pruebas y calidad** | Manuel | George y el resto del equipo | Plan de pruebas, comprobaciones funcionales y registro de defectos. Cada responsable prueba también su componente; Manuel coordina la visión de conjunto y George ayuda a verificar los flujos integrados. |
| **Gestión e integración** | George | Jorge | Seguimiento de tareas, acuerdos entre áreas, integración de componentes y coordinación de entregas. Jorge ayuda con las decisiones técnicas que afecten a la arquitectura. |
| **Documentación** | George | Todos; Jorge revisa la parte técnica | Organización y mantenimiento de la documentación del proyecto. Cada persona redacta o actualiza la información de su área; George procura que quede integrada y consistente. |

## Por qué este reparto

- **Federico** tiene como foco principal el hardware, con apoyo acotado al firmware edge para asegurar que el software y los componentes físicos encajen.
- **Jorge y Manuel** comparten frontend, como se propuso inicialmente. Para equilibrar la carga, Jorge también apoya el contrato con backend y Manuel coordina pruebas y calidad.
- **Mohamed** asume el backend como área principal y comparte el trabajo de firmware con Federico, evitando concentrar ambas áreas de implementación en una sola persona.
- **George** coordina integración y documentación, y colabora en las pruebas de extremo a extremo. Así se cubren las tareas transversales que suelen quedar sin responsable.
- **La calidad es compartida**: tener una persona coordinadora no exime a cada responsable de probar su propio trabajo.

## Forma de trabajo

1. **Acordar interfaces antes de integrar.** Backend y frontend concretan API y formatos de datos; hardware y firmware acuerdan conexiones, señales y comportamiento esperado.
2. **Trabajar por funcionalidades pequeñas.** Cuando una tarea cruza varias áreas, se nombra una persona responsable de coordinarla y se especifican las dependencias.
3. **Revisar los cambios entre compañeros.** Siempre que sea posible, otra persona revisa cada cambio antes de integrarlo, priorizando las interfaces entre áreas.
4. **Probar el flujo completo.** Además de pruebas por componente, el equipo comprueba los recorridos completos que conectan interfaz, backend y dispositivo.
5. **Mantener la documentación al día.** Los cambios de arquitectura, configuración, conexiones o uso se documentan junto con la implementación.
6. **Revisar el reparto periódicamente.** Si una fase carga demasiado a una persona, el equipo redistribuye tareas en la reunión de seguimiento, manteniendo claro quién coordina cada área.

## Revisión inicial

Esta distribución es una propuesta de partida, no una asignación rígida. En la primera revisión del proyecto, el equipo debería confirmar las preferencias, estimar las tareas pendientes y ajustar el reparto según la carga real y la experiencia de cada integrante.
