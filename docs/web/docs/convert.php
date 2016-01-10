<?php
$host="";
$user="";
$pass="";
$db="";

$link=mysql_connect($host,$user,$pass); 
mysql_select_db($db);
header("Content-type: text/html; charset=utf-8");
mysql_query("SET CHARACTER SET utf8");
mysql_query("SET NAMES utf8");

$query='select fcr_page.page_title as titulo, CONVERT( fcr_text.old_text USING utf8) as contenido
  from fcr_page, fcr_revision, fcr_text 
  where fcr_page.page_namespace=0
    and fcr_page.page_latest = fcr_revision.rev_id 
    and fcr_revision.rev_text_id = fcr_text.old_id';

$resultado=mysql_query($query);
while($datos=mysql_fetch_assoc($resultado)){
	$titulo=convert_page_name($datos['titulo']);
	if($titulo!=""){
		echo convert_page_name($datos['titulo'])."...<br />";
		file_put_contents("wikitext/".$titulo.".wt",$datos['contenido']);
	}
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
    $cadena = utf8_encode($cadena);
	return $cadena;
}

?>