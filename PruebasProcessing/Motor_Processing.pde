/*
 * Nombre: Ruiz Villalba Valentina Fabienne
 * Prueba motor con processing --> Interfaz processing
 * Octubre 2020
 * ESP32 TRA 
 */



/*
*-----------------------------------------
* Biblioteca, variables y objeto Serial
*-----------------------------------------
*/

import processing.serial.*;

Serial ESP32;

boolean flag = false; // Badera para controlar si el esta prendido o apagado

/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */

void setup(){
   ESP32 = new Serial(this,"COM5",115200);
   size(350,300);
}

void draw(){
 stroke(0);
  background(204, 255, 230);
  
  //Botón turn On
  fill(0, 179, 0);
  ellipse(90,230,65,65);
 
   //Botón turn Off
  fill(230, 0, 0);
  ellipse(260,230,65,65);
  
  fill(0);
  textSize(15);
  text("On",80,235);
  text("Off",250,235);
  
  //Botón left 
  noStroke();
  fill(54, 125, 107);
  rect(120,70,45,30);
  beginShape();
    vertex(121, 65);
    vertex(75, 85);
    vertex(121, 105);
  endShape(CLOSE);
  
  //Botón right
  noStroke();
  fill(54, 125, 107);
  rect(190,70,45,30);
  
  beginShape();
    vertex(235, 65);
    vertex(280, 85);
    vertex(235, 105);
  endShape(CLOSE);
  
  fill(0);
  textSize(15);
  text("Izquierda",80,130);
  text("Derecha",230,130);
}


/*
*   Verifica que el el mause este sobre el botón de encendido
*   regresa un verdadero si esta condición se cumple en caso contrario
*   regresa un falso
*/
boolean sobreTurnOn(){
  if(mouseY >= 230 && mouseY <=295 && mouseX >= 90 && mouseX <= 150){
    return true;
  }else{
    return false;
  }
}

/*
*   Verifica que el el mause este sobre el botón de apagado 
*   regresa un verdadero si esta condición se cumple en caso contrario
*   regresa un falso
*/
boolean sobreTurnOff(){
  if(mouseY >= 230 && mouseY <=295 && mouseX >= 260 && mouseX <= 325){
    return true;
  }else{
    return false;
  }
}

/*
*   Verifica que el el mause este sobre el botón de giro a la izquiera
*   regresa un verdadero si esta condición se cumple en caso contrario
*   regresa un falso
*/
boolean sobreLeft(){
  if(mouseY >= 70  && mouseY <=100 && mouseX >= 75 && mouseX <= 165){
    return true;
  }else{
    return false;
  }
}

/*
*   Verifica que el el mause este sobre el botón de giro a la derecha
*   regresa un verdadero si esta condición se cumple en caso contrario
*   regresa un falso
*/
boolean sobreRight(){
  if(mouseY >= 70  && mouseY <=100 && mouseX >= 190 && mouseX <= 280){
    return true;
  }else{
    return false;
  }
}


/*
*   Dependido en donde está posicionado el mouse y si el usuario le da click se manda la información 
*    (una letra), indicando la acción a realizar, al arduino. 
*   "flag" es una bandera que incialmente esta en falso indicando que el motor esta apagado 
*    si el usuario presiona el botón de enecendido la bandera cambia a verdadero.
*    a--> Indica que el motor debe apagarse
*    p --> Indica que el motor debe prenderse
*    l --> Indica que el sentido de giro será a la izquierda
*    r --> Indica que el sentido de giro será a la derecha   
*/

void mouseClicked(){
  if(sobreTurnOn() && flag == false){
    println("Motor encendido");
     ESP32.write('p');
     flag = true;
  }else if(sobreTurnOff() && flag == true){
    println("Motor apagado");
    ESP32.write('a');
    flag = false;
  }else if(sobreLeft() && flag == true){
    println("Cambiando a la izquierda");
    ESP32.write('l');
  }else if(sobreRight() && flag == true){
    println("Cambiando a la derecha");
    ESP32.write('r');
  }else if(flag == false && (sobreLeft() || sobreRight() || sobreTurnOff() )){
    println("El motor esta apagado");
  }
}
