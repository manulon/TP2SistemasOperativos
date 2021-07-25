# Sistemas Operativos: TP2 #  
---
**Grupo 4**  

**Autores:**  
- **Manuel Longo - 102425** 
- **Federico Burman - 104112**   
- **Agustín More - 102914**  
- **Daniel Alejandro Lovera López - 103442**
---
## Compilacion ##
- Ingresar en linea de comandos **make** o **make all** para crear los ejecutables.
- Ingresar en linea de comandos **make clean** para limpir los ejecutables del directorio
---
## Ejecución ##  
1. Ejecutar el programa **inicializador** para iniciar los *semaforos* usados y *memoria compartida*.
2. Ejecutar el programa **coordinador** para que atienda a los influencers que vayan llegando.
3. Ejecutar el programa **grunger** para sentarlo en la mesa controlada por el coordinador.
4. Ejecutar el programa **swagger** para sentarlo en la mesa controlada por el coordinador.
---
## Finalización ##  
Para liberar los recursos utilizados se debera llamar al programa **terminador**.  

---
## DE ACA PARA ABAJO, TODO ES PARA ELIMINAR. ARRIBA TODO LO QUE VAYAMOS A DEJAR FIJO ##
## Lista cosas posibles por hacer ##  
[ ] Ingresar varios prints para ver mejor la ejecucion de los programas (Los que se les ocurran).  
[ ] **PROBAR** nuevamente el funcionamiento de todo (ya lo probe yo, pero por las dudas **PRUEBENLO**)  
[ ] Crear un nuevo programa **finalizador** que se encargue de terminar al coordinador, ya que va a estar  
siempre esperando a que ingrese un influencer.  

## NOTAS para cuando prueben ##
El coordinador aceptará influencers siempre y cuando cumplan con las condiciones del enunciado. En el caso de encontrarse
en una situacion de 3 grunges y un swagger que se intenta sentar (o viceversa) el swagger que esta intentando sentarse se quedara esperando
hasta que ingrese un nuevo grunge que pueda ocupar ese espacio en la mesa, hasta que no ingrese un grunge que la complete cualquier intento de sentar
un nuevo swagger no sera posible (todos se quedaran esperando hasta que el coordinador los deje entrar). Cuando ingrese el influencer del grupo faltante, automaticamente todos los influencers del grupo contrario (en el cacso del ejemplo los grungers) que intentaron entrar antes van a entrar de golpe porque
es como si quedaran todos encolados hasta que finalmente ingreso el influencer que le hacia falta a la mesa que no estaba completa.

