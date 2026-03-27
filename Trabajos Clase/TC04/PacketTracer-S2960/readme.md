# Configuración de VLANs y Router-on-a-Stick en Packet Tracer


## Descripción general

Se configuró una red con un switch Cisco 2960 y un router Cisco para segmentar la red usando VLANs y permitir la comunicación entre ellas mediante el método Router-on-a-Stick. El switch se nombró "ci0123" y el router actúa como gateway para cada VLAN.


## Configuración del Switch

- Se crearon dos VLANs en el switch: la VLAN 10 con nombre "isla5" y la VLAN 20 con nombre "isla2"

- El puerto FastEthernet 0/3 se configuró como puerto de acceso y se asignó a la VLAN 10

- El puerto FastEthernet 0/4 se configuró como puerto de acceso y se asignó a la VLAN 20

- En ambos puertos de acceso se activó port-security con las siguientes características:

    - M- odo "sticky" para aprender automáticamente la dirección MAC del dispositivo conectado

    - Violación en modo "restrict" que bloquea dispositivos adicionales pero genera alertas

    - Máximo de 1 dirección MAC permitida por puerto

- El puerto FastEthernet 0/1 se configuró como puerto troncal (trunk) para transportar todas las VLANs hacia el router

- El trunk utiliza encapsulación 802.1q y transporta las VLANs 1, 10 y 20


## Configuración del Router

- Se activó la interfaz física GigabitEthernet 0/0 con el comando "no shutdown"

- Se crearon dos subinterfaces lógicas sobre la interfaz física:

    - La subinterfaz GigabitEthernet 0/0.10 se configuró con encapsulación dot1q para la VLAN 10 y se le asignó la dirección IP 172.16.10.1/24, actuando como gateway para esa VLAN

    - La subinterfaz GigabitEthernet 0/0.20 se configuró con encapsulación dot1q para la VLAN 20 y se le asignó la dirección IP 172.16.20.1/24, actuando como gateway para esa VLAN

- El router ahora tiene rutas directas (conectadas) hacia ambas redes 172.16.10.0/24 y 172.16.20.0/24

- Configuración de las PCs
La PC1 se conectó al puerto Fa0/3 del switch y se configuró con:

    - Dirección IP: 172.16.10.10

    - Máscara de subred: 255.255.255.0

    - Gateway por defecto: 172.16.10.1

- La PC2 se conectó al puerto Fa0/4 del switch y se configuró con:

    - Dirección IP: 172.16.20.10

    - Máscara de subred: 255.255.255.0

    - Gateway por defecto: 172.16.20.1


## Conexiones físicas en Packet Tracer

- Se conectó el puerto Fa0/1 del switch con el puerto G0/0 del router usando un cable de cobre directo

- Se conectó el puerto Fa0/3 del switch con la interfaz Fa0 de la PC1

- Se conectó el puerto Fa0/4 del switch con la interfaz Fa0 de la PC2


## Estado final

La configuración está completada y funcionando correctamente. Las PCs en diferentes VLANs pueden comunicarse entre sí a través del router, y la seguridad por puerto está activa limitando un solo dispositivo por cada puerto de acceso.