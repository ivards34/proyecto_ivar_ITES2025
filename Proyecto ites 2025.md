Proyecto ites 2025 

Detector de calidad del aire en el ambiente de una habitación de un hogar y alarmar si se detectan gases nocivos para nuestra salud.

1. Los gases que son nocivos para la salud son:
Asbesto
Contaminantes biológicos
Monóxido de carbono (CO)
Formaldehído
Materia particulada en interiores (PM)
Plomo
Moho y humedad
Dióxido de nitrógeno (NO2)
Pesticidas
Radón
Humo de segunda mano/humo ambiental de tabaco
Compuestos orgánicos volátiles (VOCs)
Humo de madera
2.3.  Los que podemos lograr monitorear con ESP32 dentro de una habitación son:
	{Monóxido de carbono(CO): sensor compatible MQ-7 o MQ-2
	Formaldehído: sensor compatible HCHO (e.g., Winsen ZE08-HCHO)
	Materia particulada (PM2.5/PM10): sensor compatible PMS5003, SDS011
	Dióxido de nitrógeno (NO₂): sensor compatible MiCS-2714, SPEC sensors
	Compuestos orgánicos volátiles (VOCs): sensor compatible CCS811, BME680
	Humo de madera / tabaco: sensor compatible MQ-2, MQ-135}
	EN ESTE PROYECTO SOLO USAREMOS EL SENSOR (MQ-2) Y EL MODULO (SIM800L) PAR COMUNICARNOS VIA SMS.
4. Mi propósito es que el microcontrolador mida la calidad del aire del ambiente y a su vez si detecta algún gas que sea nocivo para la salud. si llega a detectar un gas nocivo el dispositivo nos debe alertar mediante una app en el teléfono o nos envíe un mensaje alertando nos, esperando una respuesta de nosotros  confirmando que estamos enterados del problema y lo solucionemos o ventilemos.En caso de no contestar, alertar a emergencias(los bomberos) con un mensaje o llamada diciendo el motivo y la dirección donde se encuentra la casa o departamento.

