#include <Arduino.h>
#include <ArduinoJson.h>
//@param idNodoRegistrado ID del nodo que se encuentra ahora mismo almacenado en el registro.
//@param listaNodos La lista de los nodos disponibles con información para ver.
//@param nNodos Número de nodos en listaNodos
String paginaPrincipal(String idNodoRegistrado, DynamicJsonDocument &listaNodos)
{
  String cadenaTotal;
  String pag1 = R"foo(
<!DOCTYPE html>
<html lang="es">
  <head>
    <script>
      function enfoca(identificador){
        document.getElementById(identificador).focus();
      }
    </script>
    <style>
      body {
        font-family: sans-serif;
        font-size: 2.3vh;
      }
      h2 {
        font-size: 2.5vh;
        text-align: center;
        padding-bottom: 1vh;
        padding-top: 1vh;
        margin-bottom: 1vh;
        margin-top: 0vh;
        color: #FFFFFF;
        border-bottom: 3px solid #38aa7e;
        background-color: #3dc591;
        border-top-left-radius: 25px;
        border-top-right-radius: 25px;
        text-shadow: 2px 2px 1px #4f6e54;
        box-shadow: 0px 2px 3px #2c5e35;
      }
      .titulo {
        text-align: center;
        color: #FFFFFF;
        margin: 0px;
        font-size: 6vh;
        text-shadow: 2px 4px 1px #4f6e54;
      }
      header {
        padding-bottom: 1.5vh; 
        background-color: #3dc591;
        border-bottom: 4px solid #38aa7e;
        margin-bottom:  2vh;
        box-shadow: 2px 3px 3px #4f6e54;
      }
      .desplegable {
        margin-top: 4vh;
        text-align: center;
        border-radius: 25px;
        margin-right: 10vw;
        margin-left: 10vw;
        font-size: 2.3vh;
        background-color: #f4ffe9;
        margin-bottom:  2vh;
        padding-bottom: 0.2vh;
        text-shadow: 1px 1px 0px #d1d1d1;
        box-shadow: 2px 4px 3px #9ccf74;
        overflow: hidden;
        max-height: 7vh;
        transition: all .60s ease-in-out;
      }
      .desplegable:focus-within {
        max-height: 200vh;
      }
      select {
        font-size: 2.3vh;
        border-radius: 60px;
        margin-bottom: 1vh;
        padding: 0.2vh;
        padding-left: 0.7vh;
        padding-right: 0.7vh;
        margin-left: 1vh;
        box-shadow: 2px 3px 0px #10752e;
        font-family: sans-serif;
        background-color: #f3f3f3;
      }
      input[type=submit] {
        font-family: sans-serif;
        font-weight: bold;
        background-color: #ec455b;
        box-shadow: 2px 3px 0px #a13140;
        font-size: 2.3vh;
        color: white;
        padding: 1.5vh;
        padding-left: 2vw;
        padding-right: 2vw;
        margin: 8px 0;
        border: none;
        border-radius: 60px;
        cursor: pointer;
        size: 3vw;
      }
      input[type=submit]:hover {
        background-color: #ec7484;
      }
      input[type=submit]:active {
        background-color: #ec7484;
        margin-left: 1vh;
        margin-top: 0.82vh;
        box-shadow: none;
      }
      input[type=text], input[type=number] {
        text-align: center;
        font-size: 2.3vh;
        font-family: sans-serif;
        color: #2c5e35;
        border-color: #2c5e35;
        border-radius: 60px;
        padding-left: 1vh;
        padding-right: 1vh;
        box-shadow: 2px 3px 0px #09421a;
      }
      input[type=range] {
        width: 30vw;
        display: inline-block;
        margin-left: 1.5vh;
        margin-right: 0.5vw;
        -webkit-appearance: none;
      }
      input[type="range"]::-webkit-slider-thumb {
        width: 2.5vh;
        height: 2.5vh;
        margin-top: -0.75vh;
        background-color: #eb9635;
        border-radius: 50%;
        border: 4px solid #ad6e26;
        -webkit-appearance: none;
        box-shadow: 1px 2px 0px #744919;
      }
      input[type="range"]::-webkit-slider-runnable-track {
        background-color: #82d3b5;
        -webkit-appearance: none;
        height: 1vh;
        border-radius: 60px;
        box-shadow: 2px 3px 0px #10752e;
      }
      .numerito {
        width: 4.5vh;
        box-shadow: 2px 3px 0px #09421a;
      }
      .numeritoh {
        width: 6vh;
        box-shadow: 2px 3px 0px #09421a;
      }
      p {
        margin-top: 1.5vh;
        margin-bottom: 1.5vh;
        margin-left: 2vw;
        margin-right: 2vw;
        text-align: center;
      }
      #enlace {
        border-radius:60px;
        margin-bottom: 1vh;
        background-color: #ffa53e;
        display: inline-block;
        box-shadow: 2px 3px 0px #ca8230;
        padding: 1.5vh;
        padding-left: 2vw;
        padding-right: 2vw;
        color: white;
        font-family: sans-serif;
        font-weight: bold;
        text-decoration: none;
        font-size: 2.3vh;
        margin-bottom: 1vh;
      }
      #enlace:hover {
        background-color: #ffbe74;
      }
      #enlace:active {
        background-color: #ffbe74;
        margin-left: 1vh;
        margin-top: 0.02vh;
        box-shadow: none;
      }
      #n1 {
        margin-left: 3vh;
      }
      #red, #red1 {
        width: 20vw;
      }
      .notificacion {
        background-color: #ffd17c;
        border-radius: 60px;
        border: 2px solid #ac6e27;
        box-shadow: 2px 3px 0px #ac6e27;
        padding-left: 15vw;
        padding-right: 15vw;
        display: inline-block;
        width: fit-content;
      }

    </style>
    <title>Silvanus Bonsai</title>
    <meta charset="utf-8">
  </head>
  <body>
    <header>
      <h1 class="titulo">Silvanus Bonsai</h1>
    </header>
    <main>
      <p><i>Administra tus dispositivos silvanus</i></p>

      <!-- Encargado de mostrar todos los nodos que se encuentran enlazados en este momento -->
      <div class="desplegable" id="selector">
        <h2 onclick="enfoca('escnodo')">DATOS DEL NODO</h2>
        <form action="selnodo" method="POST" onclick="enfoca('escnodo')">
          <br><label>Nodos disponibles:</label>
          <select name="nodoelegido" id="escnodo">
            
)foo";

  cadenaTotal +=pag1;

  String pag11 = "";

  //Rellenar la selección de nodo <option value="nodo3">Nodo-3</option>
  JsonObject obj = listaNodos.as<JsonObject>();
  for (JsonObject::iterator it=obj.begin(); it!=obj.end(); ++it) 
    {
    pag11 += "<option value=\"" + (String)it->key().c_str() + "\">" + (String)it->key().c_str() + "</option>";
  }

  cadenaTotal += pag11;


  String pag12 = R"foo(
    </select><br><br>
          <input type="submit" value="CONSULTAR">
        </form>
      </div>


      <div class="desplegable" id="nuevonodo">
        <h2 onclick="enfoca('idnodo')">REGISTRAR NODO</h2>
  )foo";
  cadenaTotal += pag12;


  //Notificación de nodos registrados
  if(idNodoRegistrado != ""){
    String nodoRegistrado = "<p class=\"notificacion\">Registrado <i>" + idNodoRegistrado + "</i></p>";
    cadenaTotal += nodoRegistrado;
  }
  Serial.println("Nodo registrado añadido");

  String pag2 = R"foo(
        <form action="registranodo" method="POST">
          <br><label>Nombre</label><br>
          <input name="idNodo" required="required" placeholder="ID del nodo" type="text" id="idnodo" maxlength="30">
          
          <br><br>
          <span title="La intensidad que debe adquirir el sol para detectar que se encuentra bien insolada">
          <label>Intensidad lumínica</label><br>
          <input type="range" required="required" min="1" max="100" name="luminosidad" oninput="this.nextElementSibling.value = this.value"><output>50</output>%
          </span>
          <br>
          <span title="Cantidad de horas que la planta ha de estar bien insolada para considerar que ha recibido suficiente luz">
          <label>Horas mínimas de luz</label><br>
          <input type="range" required="required" min="1" max="24" value=8 name="hluminosidad" id="red" oninput="this.nextElementSibling.value = this.value"><output>8</output>h
          </span>
          <br><br>
          <span title="Rango de temperatura ambiental que se considera óptima para la planta">
            <label>Temperatura recomendada</label><br>
            <input type="number" required="required" class="numerito" name="temp1" max="60" min="-60" id="n1" > - <input type="number" class="numerito" name="temp2" max="60" min="-60" ><label> ºC</label>
          </span>
          <br><br>
          <span title="Rango de humedad ambiental que se considera óptima para la planta">
            <label>Humedad recomendada</label><br>
            <input type="number" required="required" class="numeritoh" name="hum1" max="100" min="0" id="n1" > - <input type="number" class="numeritoh" name="hum2" max="100" min="0" ><label> %</label>
          </span>
          <br><br>
          <span title="Minima humedad a partir de la cual por debajo se considera que debe regar">
            <label>Umbral de riego</label><br>
            <input type="range" required="required" min="1" max="100" name="sust" oninput="this.nextElementSibling.value = this.value"><output>50</output>%
          </span>
          <br>
          <span title="Los segundos que la bomba va a encontrarse activa bombeando agua">
            <label>Segundos de bombeo</label><br>
            <input type="range" required="required" min="1" max="60" name="bomb" value=6 id="red1" oninput="this.nextElementSibling.value = this.value"><output>6</output>s
          </span>

          <br><br><input type="submit" value="REGISTRAR">
        </form>
      </div>

      <div class="desplegable" id="identifica">
        <h2 onclick="enfoca('enlace')">INDENTIFICA TU BONSAI</h2>
        <p>¿No sabes que planta tienes?</p>
        <p>Indentifícala aquí.</p>
        <a id="enlace" href="https://identify.plantnet.org/es">Pl@ntNet</a>
      </div>

    </main>
    <footer></footer>
  </body>
</html>
)foo";

  cadenaTotal += pag2;

  return cadenaTotal;

}