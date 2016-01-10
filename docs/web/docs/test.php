<?php
$input="  REDIRECT [paco_pico] blablabla [este es otro]";
preg_match('/\[(.*?)\]/', $input, $output);
echo $output[2];
?>