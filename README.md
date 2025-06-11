Este es el archivos y librerias necesarias para correr el proyecto final de programación 1.
Tener Instalado Visual Studio 2022
Tener Instalado MySQL Worbench (paquete completo)
En el visual studio 2022 en las propiedades agregar las siguiente configuraciones 
PROPIEDADES -> C/C++ -> GENERAL -> DIRECTORIOS DE INCLUSION ADICIONALES

C:\Program Files\MySQL\MySQL Connector C++ 9.3\lib64
C:\Program Files\MySQL\MySQL Connector C++ 9.3\include
C:\Program Files\MySQL\MySQL Server 8.0\include
C:\Program Files\MySQL\MySQL Server 8.0\lib

PROPIEDADES -> VINCULADOR  -> ENTRADA -> DEPENDENCIA ADICIONALES
libmysql.lib
mysqlcppconn.lib
