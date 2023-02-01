<?php

    header("Access-Control-Allow-Origin: *");
    // header('Content-Type: text/html');

    if( isset($_GET["int"]) ) {
        echo( rand( -32768, 32767) );
    }
    else if( isset($_GET["float"]) || isset($_GET["double"]) || isset($_GET["real"]) ) {
        echo( sin(rand( -32768, 32767)) );
    }
    else if( isset($_GET["date"]) ) {
        echo( date("D d M Y") );
    }
    else if( isset($_GET["time"]) ) {
        echo( date("h:i:s") );
    }
    else {
        echo("Unknown API");
    }

    echo("\r\n");
?>
