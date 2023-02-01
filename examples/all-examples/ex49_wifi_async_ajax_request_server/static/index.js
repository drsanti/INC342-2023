window.onload = function(e){

    function getEle(e){
        return document.getElementById(e);
    }
    function load(req) {

        var xml = new XMLHttpRequest();
        xml.timeout = 2000;
        xml.onreadystatechange = function()
        {
            if (xml.readyState == XMLHttpRequest.DONE)
            {
                if (xml.status == 200)
                {
                    getEle('output').innerHTML = xml.responseText;
                }
                else if (xml.status == 400)
                {
                    console.log('There was an error 400');
                }
                else
                {
                    console.log('something else other than 200 was returned');
                }
            }
        };
        xml.open("GET", req, true);
        xml.send();
    }
    function doIt(id, cmd){
        getEle(id).addEventListener("click", function(){
            load(cmd);
        });
    }
    for(var i=0; i<4; i++) {
        doIt('led'+i+'-inv', 'led/'+i+'/2;');
        doIt('led'+i+'-on',  'led/'+i+'/1;');
        doIt('led'+i+'-off', 'led/'+i+'/0;');
        doIt('adc'+i,        'adc/'+i+'/0;');
    }

    setInterval(function(){
        load('adc/1/0;');
    }, 10e3);
}
