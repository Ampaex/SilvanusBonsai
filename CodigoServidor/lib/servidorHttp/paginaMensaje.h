#include <Arduino.h>

String paginaMensaje(String mensaje)
{
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
      div {
        text-align: center;
      }
      textarea {
        width: 50vw;
        height: 20vh;
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
      <div>
        <br>
)foo";

    String men = "<p><i>" + mensaje + "</i></p>" ;
    
    String pag2 = R"foo(
       <br>
        <a id="enlace" href="http://silvanus">VOLVER</a>
      </div>
    </main>
    <footer></footer>
  </body>
</html>
     )foo";

    return pag1 + men + pag2;

}