const char* paginaPrincipal()
{
    const char* pag = R"foo(
<!DOCTYPE html>
<html lang="">
<head>
    <style>
    h2 {
        font-size: 2.5vh;
        text-align: center;
        padding-bottom: 1vh;
        color: #21b5a6;
        border-bottom: 1px solid #84cf34;
    }
    .titulo {
        font-family: sans-serif;
        text-align: center;
        color: #29d9c7;
        margin: 0px;
        font-size: 6vh;
        text-shadow: 1px 2px 1px #4d4d4d;
    }
    header {
        padding-bottom: 1.5vh; 
        background-color: #eaffd4;
        border-bottom: 4px solid #84cf34;
        margin-bottom:  2vh;
        box-shadow: 2px 4px 6px #727272;
    }
    .selector {
        font-family: Georgia;
    }
    div {
        margin-top: 1vh;
        text-align: center;
        border: 2px solid #84cf34;
        border-radius: 25px;
        margin-right: 10vw;
        margin-left: 10vw;
        font-size: 2.3vh;
        background-color: #f4ffe9;
        margin-bottom:  2vh;
        padding-bottom: 0.2vh;
        box-shadow: 2px 4px 6px #727272;
    }
    select {
        font-size: 2.3vh;
        border-radius: 12px;
        margin-bottom: 1vh;
        margin-left: 1vh;
        font-family: monospace;
        background-color: #f3f3f3;
    }
    input[type=submit] {
        font-family: Georgia;
        width: 80%;
        background-color: #54b454;
        font-size: 2.3vh;
        color: white;
        padding: 14px 20px;
        margin: 8px 0;
        border: none;
        border-radius: 60px;
        cursor: pointer;
        size: 3vw;
    }
    input[type=submit]:hover {
        background-color: #45a049;
    }
    #enlaceplantnet {
        border-radius:60px;
        background-color: #ebad67;
        padding: 1vh;
        color: white;
        text-decoration: none;
    }
    #enlaceplantnet:hover {
        background-color: #d19b5c;
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
        <h2>CONSULTA EL ESTADO DEL NODO</h2>
        <label>Escoge un nodo:</label>
        <select name="nodoelegido">
            <option value="nodo1">Nodo-1</option>
            <option value="nodo2">Nodo-2</option>
            <option value="nodo3">Nodo-3</option>
        </select><br>
        <input type="submit" value="CONSULTAR">
        </form>
    </div>

    <!-- Se utiliza para configurar un dispositivo seleccionado 
    <div class="configurador">
        <br>
    </div>
    -->

    <div>
        <h2>INDENTIFICA TU BONSAI</h2>
        <a id="enlaceplantnet" href="https://identify.plantnet.org/es">Pl@ntNet</a>
        <h3></h3>
        
    </div>

    </main>
    <footer></footer>
</body>
</html>
)foo";

    return pag;

}