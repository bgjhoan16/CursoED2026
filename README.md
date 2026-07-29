"# CursoED2026"  
"# CursoED2026" 
.....



SISTEMA DE ATENCIÓN EN UN SUPERMERCADO
Desarrollar en lenguaje C una aplicación para gestionar la atención de los clientes en un supermercado. Cada cliente deberá registrarse con sus datos básicos y ubicarse en una cola de espera, siendo atendido por el cajero en el mismo orden en que llegó, de acuerdo con el principio FIFO. El sistema deberá permitir ingresar nuevos clientes, consultar la fila actual y atender al primer cliente disponible sin alterar el orden de los demás.
Durante la atención, un cliente podrá registrar una solicitud de devolución indicando SOLAMENTE el producto. Estas solicitudes deberán almacenarse en una pila y serán procesadas por el cajero cuando no haya clientes pendientes en la cola. La última solicitud registrada será la primera en atenderse, respetando el principio LIFO. De esta manera, la cola controla la atención normal de los clientes y la pila administra las devoluciones pendientes como una actividad complementaria del supermercado.
Ejemplo: si el cliente A registra una devolución y posteriormente el cliente B registra otra, la solicitud de B quedará en la parte superior de la pila. Cuando el cajero pueda procesar las devoluciones, atenderá primero la solicitud de B y después la de A.
