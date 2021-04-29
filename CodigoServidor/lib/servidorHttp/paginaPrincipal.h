const char* paginaPrincipal()
{
    const char* pag = R"foo(
<!DOCTYPE html>
<html lang="es">
  <head>
    <style>
      h2 {
        font-size: 2.5vh;
        text-align: center;
        padding-bottom: 1vh;
        padding-top: 1vh;
        margin-bottom: 1vh;
        color: #FFFFFF;
        border-bottom: 3px solid #38aa7e;
        background-color: #3dc591;
        border-top-left-radius: 25px;
        border-top-right-radius: 25px;
        font-family: sans-serif;
        text-shadow: 2px 2px 1px #4f6e54;
        box-shadow: 0px 2px 3px #2c5e35;
      }
      .titulo {
        font-family: sans-serif;
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
      div {
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
      }
      div:active {
        height: auto;
      }
      select {
        font-size: 2.3vh;
        border-radius: 30px;
        margin-bottom: 1vh;
        padding: 0.2vh;
        padding-left: 0.7vh;
        padding-right: 0.7vh;
        margin-left: 1vh;
        box-shadow: 1px 1px 2px #8b8b8b;
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
      p {
        margin-top: 1.5vh;
        margin-bottom: 1.5vh;
        margin-left: 2vw;
        margin-right: 2vw;
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

    </style>
    <meta charset="utf-8">
  </head>
  <body>
    <header><h1 class="titulo">Silvanus Bonsai</h1></header>
    <main>
      <!-- Encargado de mostrar todos los nodos que se encuentran enlazados en este momento -->
      <div class="selector">
        
        <!-- Ayuda sobre como conectar el formulario con el esp: https://www.luisllamas.es/como-recibir-datos-de-un-formulario-web-con-esp8266/ -->
        <form action="selnodo" method="get">
          <h2>ESTADO DEL NODO</h2>
          <label>Escoge un nodo:</label>
          <select name="nodoelegido">
            <option value="nodo1">Nodo-1</option>
            <option value="nodo2">Nodo-2</option>
            <option value="nodo3">Nodo-3</option>
          </select><br>
          <input type="submit" value="CONSULTAR">
        </form>
      </div>

      
      <div class="configurador">
        <h2>CONFIGURADOR</h2>
        <br>
      </div>

      <div>
        <h2>INDENTIFICA TU BONSAI</h2>
        <p>¿No sabes que planta tienes?</p>
        <p>Indentifícala aquí.</p>
        <a id="enlace" href="https://identify.plantnet.org/es">Pl@ntNet</a>
      </div>

    </main>
    <footer></footer>
  </body>
</html>
)foo";

    return pag;

}