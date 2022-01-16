# APD
Directorio de prácticas de algoritmia para problemas dificiles UNIZAR

# Práctica 1 - Dominant Set
Dentro del paradigma de Smart City IoT, la tecnología Wi-SUN ha dotado a Londres de un
sistema de alumbrado de 12.000 unidades.

En una red inteligente y ubicua de tamaño y complejidad parecida al ejemplo anterior, es muy
importante poder identificar y mantener un conjunto de nodos o dispositivos principales de
forma que cualquier otro nodo de la red esté directamente conectado a un nodo principal. Dicho
conjunto de nodos principales ha de ser lo más pequeño posible para minimizar el coste de su
mantenimiento.

En esta práctica buscamos algoritmos que resuelvan o aproximen de forma eficiente el problema
de encontrar el conjunto mínimo de nodos principales D de forma que cualquier otro nodo esté
conectado a al menos uno de los de D. La información de partida es el grafo de conexiones entre
los nodos del sistema, guardada como una matriz o de la forma que se considere conveniente.

# Práctica 2 - Algoritmo probabilista 
Te está costando elegir entre los dos principales servicios de mensajería que hay en tu ciudad.
Tienen el mismo precio, el servicio al cliente tiene coste muy bajo y usan la misma estrategia
de reparto, excepto que empiezan en distinto almacén.

Su estrategia es la siguiente, un conductor sale de un almacén que está directamente conectado
a una intersección. Cuando un conductor llega a una intersección I se elige aleatoriamente una
carretera, dada una distribución de probabilidad conocida de las carreteras que salen de I. Cada
intersección estó conectada con carreteras que van al menos a una intersección distinta. Lleva un
tiempo fijo recorrer una carretera. Si un conductor llega a la intersección donde vives te entrega
el paquete (o lo deja en la puerta si no estás).

Te gustaría elegir el servicio de mensajería que tiene el menor tiempo estimado de reparto.
