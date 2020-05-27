// JavaScript source code
var elm_p = "";
var elm_k = "";
var licznik_iteracji = 0;
var str = "";

function fDodaj() {
    elm_p = $("#el_p").val();
    elm_k = $("#el_k").val();
    
    if (!elm_k || !elm_p)
        alert("Proszê wybraæ element pocz¹tkowy oraz koñcowy");
    else if (elm_p == elm_k) {
        $('#' + elm_p).css({ "border": "6px solid black", "background-color": "#80ccff" });
        $("#elm_p").html("S={" + elm_p + "}");
        $("#elm_k").html("F={" + elm_k + "}");
    } else {
        $("#elm_p").html("S={" + elm_p + "}");
        $("#elm_k").html("F={" + elm_k + "}");
        $('#' + elm_p).css({ "border": "6px solid black", "background-color": "#6699ff" });
        $('#' + elm_k).css({ "border": "6px solid black", "background-color": "#99ffff" });
    }
}

function fUsun() {
    $("#elm_p").html("S={}");
    $("#elm_k").html("F={}");
    fRClear();
}
function fRClear(){
    $('#q0').removeAttr("style");
    $('#q1').removeAttr("style");
    $('#q2').removeAttr("style");
    $('#q3').removeAttr("style");
    $('.arrow').children().removeAttr("style");
    $('.tab_pion tbody h3').removeAttr("style");
}
function fActive(element) {
    fRClear();
    $('#' + element).css({ "border": "6px solid red", "background-color": "#6699ff" });
}

function fBold(elem, liczba) {
    if (licznik_iteracji - 1 < liczba) {
        setTimeout(function () {
            $('#' + elem).css({ "font-weight": "bold", "font-size": "250%", "color": "red" });
        }, 1000);
    }
}

////////////////////////////////////////////////////////////

function fStart() {
    elm_p = "";
    elm_k = "";
    licznik_iteracji = 0;
    fDodaj();
    var patt = /^[01]*$/g;
    var input = $('#inp').val();
    if (!patt.test(input) || !input) {
        alert("Proszê wprowadziæ porpawny ci¹g 0 i 1");
    } else {
        var el_o = elm_p;
        str = input;
        fPrzebieg(el_o);
    }
}

function fPrzebieg(element) {
    setTimeout(function () {
        if (licznik_iteracji <= str.length+1) {
            if (licznik_iteracji - 1 < str.length) {
                fRClear();
                fActive(element)
            }
            licznik_iteracji += 1;
            switch (element) {
                case "q0":
                    if (str[licznik_iteracji - 1] == 0) {
                        fBold("q0q2d", str.length);
                        setTimeout(function () {
                            fPrzebieg("q2");
                        }, 1000);
                    } else {
                        fBold("q0q1r", str.length);
                        setTimeout(function () {
                            fPrzebieg("q1");
                        }, 1000);
                    }
                    break;

                case "q1":
                    if (str[licznik_iteracji - 1] == 0) {
                        fBold("q1q3d", str.length);
                        setTimeout(function () {
                            fPrzebieg("q3");
                        }, 1000);
                    } else {
                        fBold("q0q1l", str.length);
                        setTimeout(function () {
                            fPrzebieg("q0");
                        }, 1000);
                    }
                    break;

                case "q2":
                    if (str[licznik_iteracji - 1] == 0) {
                        fBold("q0q2u", str.length);
                        setTimeout(function () {
                            fPrzebieg("q0");
                        }, 1000);
                    } else {
                        fBold("q2q3r", str.length);
                        setTimeout(function () {
                            fPrzebieg("q3");
                        }, 1000);
                    }
                    break;

                case "q3":
                    if (str[licznik_iteracji - 1] == 0) {
                        fBold("q1q3u", str.length);
                        setTimeout(function () {
                            fPrzebieg("q1");
                        }, 1000);
                    } else {
                        fBold("q2q3l", str.length);
                        setTimeout(function () {
                            fPrzebieg("q2");
                        }, 1000);
                    }
                    break;
            }
        } else
            fCheck(element);
    }, 1000);
}

function fCheck(elm) {
    if (elm == elm_k) alert("Podany ci¹g jest zaakceptowany!");
    else alert("Podany ci¹g nie zosta³ zaakceptowany!");
}