<?php
$last_section_internal_number=0;
$sections[]="";
$contents[1000][]="";
$section_number[0]=0;

include("parsedown.php");

if(!empty($_GET['p'])) {
    parsedown($_GET['p']);
    die();
}

function convert_page_name($name){
    $originales = 'ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõöøùúûýýþÿŔŕ';
    $modificadas = 'aaaaaaaceeeeiiiidnoooooouuuuybsaaaaaaaceeeeiiiidnoooooouuuyybyRr';
    $cadena = utf8_decode($name);
    $cadena = strtr($cadena, utf8_decode($originales), $modificadas);
    $cadena = strtolower($cadena);
    $cadena = str_replace("\\", "",$cadena);
    $cadena = str_replace("/", "",$cadena);
    $cadena = str_replace("!", "",$cadena);
    $cadena = str_replace("@", "",$cadena);
    $cadena = str_replace("&", "",$cadena);
    $cadena = str_replace("*", "",$cadena);
    $cadena = str_replace("(", "",$cadena);
    $cadena = str_replace(")", "",$cadena);
    $cadena = utf8_encode($cadena);
    return $cadena;
}

function parsedown($page){
    $ready=0;
    $i=0;
    while($ready==0){
        $i++;
        if($i==5){
            echo 'Error! Redirect loop.';
            return;
        }
        $ready=1;
        @$page_content=file_get_contents("pages/".$page.".txt");
        if($page_content=="") {
            $page_content = "Page $page not found!";
            return;
        }
        if(strpos($page_content,"REDIRECT [")>-1){
            $ready=0;
            preg_match('/\[(.*?)\]/', $page_content, $output);
            $page=convert_page_name($output[1]);
            if(!file_exists("pages/".$page.".txt")){
                echo "Failed redirection, missing page: ".$page;
            }
        }
    }

    //reemplazamos etiquetas HTML innecesarias:
    $page_content=preg_replace('%\<category(.*?)\>%si', "", $page_content);
    $page_content=preg_replace('%\[category(.*?)wikilink\"\)%si', "", $page_content);
    $page_content=preg_replace('%\]\((.*)wikilink\"\)%i', "\]", $page_content);
    $page_content=preg_replace('%\<DPL\>%i', "", $page_content);
    $page_content=htmlentities($page_content);

    $Parsedown = new Parsedown();
    echo $Parsedown->text($page_content);
    echo '<br />';
}

function docs_read_content($file){
    //empezamos HTML y ponemos sidebar
    $fp=fopen($file,"r");
    $titulo=fgets($fp);
    echo '<!DOCTYPE html>
<html lang="en">

<head>
    <title>'.$titulo.'</title>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link href="css/simple-sidebar.css" rel="stylesheet">
    <link href="css/style.css" rel="stylesheet">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesnt work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

    <script src="js/jquery.min.js"></script>
    <script src="js/bootstrap.min.js"></script>

</head>

<body>

    <div id="wrapper">

        <!-- Sidebar -->
        <div id="sidebar-wrapper">
            <ul class="sidebar-nav">
                <li class="sidebar-brand">
                    <a href="#">
                        '.$titulo.'
                    </a>
                </li>
';

    // ponemos secciones en la sidebar
    $section_number=0;
    while(!feof($fp)) {
        $line=fgets($fp);
        $line=preg_replace( "/\r|\n/", "", $line ); //quitamos los saltos de línea
        if($line[0]=="*") {
            $section_number++;
            if($line[1]==" ") {
                $section_name=substr($line,2);
                //falta comprobar si hay que explotar y hacer dos partes
                if(strpos($section_name," ||| ") === FALSE){
                } else {
                    $temp=explode(" ||| ",$section_name);
                    $page=$temp[1];
                    $section_name=$temp[0];
                }
                echo '<li><a href="#section'.$section_number.'" onclick="show('.$section_number.');">'.$section_name.'</a></li>'."\n";
            }
        }
    }
    fclose($fp);

    echo '</ul>
        </div>
        <!-- /#sidebar-wrapper -->

        <!-- Page Content -->
        <div id="page-content-wrapper">
            <div class="container-fluid">
                <div class="row">
                    <div class="col-lg-12">
';

    //PONEMOS ÍNDICE
    $fp=fopen($file,"r"); //round 2
    while(!feof($fp)) {
        $line=fgets($fp);
        $line=preg_replace( "/\r|\n/", "", $line ); //quitamos los saltos de línea
        $level=-1;
        $page="";
        if($line[0]=="*"){
            for($i=0;$i<=10;$i++){
                if($line[$i]=="*"){
                    $level++;
                } else {
                    break;
                }
            }
            $section_name=substr($line,$level+1);
            //falta comprobar si hay que explotar y hacer dos partes
            if(strpos($section_name," ||| ") === FALSE){
                add_section($section_name,$level,"");
            } else {
                $temp=explode(" ||| ",$section_name);
                $section_name=$temp[0];
                $page=$temp[1];
                add_section($section_name,$level,$page);
            }
            echo "\n";
        }
        if($line[0]=="t"){
            title(substr($line,2));
        }
    }
    fclose($fp);

    echo '<hr>'."\n";

    //ponemos las secciones y el contenido!
    $section_number=0;
    $content_number=0;
    $anterior_level=0;
    $columns=0;
    $fp=fopen($file,"r"); //round 3!
    while(!feof($fp)) {
        $page="";
        $line=fgets($fp);
        $line=preg_replace( "/\r|\n/", "", $line ); //quitamos los saltos de línea
        $level=-1;
        if($line[0]=="c"){
            echo '<div class="cols'.$line[1].'">';
            $columns=1;
        }
        if($line[0]=="*"){
            $section_number++;
            for($i=0;$i<=10;$i++){
                if($line[$i]=="*"){
                    $level++;
                } else {
                    break;
                }
            }

            if($level<=$anterior_level){
                for($i=$level;$i<=$anterior_level;$i++){
                    echo "</div>\n";
                }
            }

            if($columns) {
                $columns=0;
                echo "</div>\n";
            }

            $section_name=substr($line,$level+1);

            //falta comprobar si hay que explotar y hacer dos partes
            if(strpos($section_name," ||| ") === FALSE){
            } else {
                $temp=explode(" ||| ",$section_name);
                $section_name=$temp[0];
                $page=$temp[1];
            }
            echo '<hr id="section'.$section_number.'"><h2>'.$section_name.'</h2>
            <div class="docssection">';
            parsedown($page);
        }
        if($line[0]=="-"){
            $content_number++;
            $content_name=substr($line,2);

            if(strpos($content_name," ||| ") === FALSE){
                if(file_exists("pages/".convert_page_name($content_name).".txt")){
                    $page=convert_page_name($content_name);
                }
            } else {
                $temp=explode(" ||| ",$content_name);
                $content_name=$temp[0];
                $page=$temp[1];
            }
            //echo '<a href="#" onclick="show_content('.$content_number.');">'.$content_name.'</a><br />'."\n";
            echo '<button type="button" class="btn btn-default" onclick="show_content('.$content_number.');">'.$content_name.'</button><br />';
            if($page!=""){
                echo '<div class="bs-callout bs-callout-info" id="content'.$content_number.'" style="display:none">';
                parsedown($page);
                echo "</div>\n";
            }
        }
        if($line[0]=="*") {
            $anterior_level=$level;
        }
    }

    //hide all sections
    echo '<script>
function show(id){
    return false;
    $(".docssection").hide("slow");
    $(".docscontent").hide("slow");
    $("#section"+id).show("slow");
}
function load_content(id,page){
    return false;
    if(page=="") return false;
    $.ajax({
        cache: false,
        url: "index.php?p="+page
    })
    .done(function( msg ) {
        document.getElementById("content"+id).innerHTML=msg;
        $("#content"+id).show("slow");
    });
}
function show_content(id){
    $("#content"+id).toggle("swing");
}
function load_section(id,page){
    return;
    if(page=="") return false;
    $.ajax({
        cache: false,
        url: "index.php?p="+page
    })
    .done(function( msg ) {
        document.getElementById("section"+id+"content").innerHTML=msg;
        $("#section"+id+"content").show("slow");
    });
}
</script>
    ';

    echo '                    </div>
                </div>
            </div>
        </div>
        <!-- /#page-content-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- Menu Toggle Script -->
    <script>
    $("#menu-toggle").click(function(e) {
        e.preventDefault();
        $("#wrapper").toggleClass("toggled");
    });
    </script>

</body>

</html>';
}

function add_section($name, $level, $page){
    global $section_number;
    global $subsection_number;
    global $sections;
    global $last_section_internal_number;

    for($i=$level+1; $i<=10; $i++){
        $section_number[$i]=0;
    }

    $full_section = '';
    $spacing = '';

    $section_number[$level]++;
    for($i=0;$i<=$level;$i++){
        $full_section.=$section_number[$i].".";
        $spacing.="&nbsp;&nbsp;&nbsp;";
    }

    $last_section_internal_number++;

    echo '<a href="#section'.$last_section_internal_number.'" onclick="show('.$last_section_internal_number.');">'.$spacing.$full_section.' '.$name.'</a><br />';

    $sections[]=[$full_section.' '.$name,$page];
}

function title($name){
    echo '<h1>'.$name.'</h1>';
}
?>