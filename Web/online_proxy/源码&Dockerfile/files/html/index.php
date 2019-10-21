<?php
/**
 * Created by PhpStorm.
 * User: jinzhao
 * Date: 2019/7/24
 * Time: 9:49 PM
 */

include "db.php";

error_reporting(0);

$start = microtime(true);

if(isset($_SERVER['HTTP_X_FORWARDED_FOR'])) {
    $_SERVER['REMOTE_ADDR'] = $_SERVER['HTTP_X_FORWARDED_FOR'];
}

$ip = $_SERVER['REMOTE_ADDR'];

if(!isset($_COOKIE["track_uuid"])) {
    $uuid = gen_uuid();
    setcookie("track_uuid", $uuid, time() + 86400 * 365);
} else {
    $uuid = $_COOKIE["track_uuid"];
}

ini_set("open_basedir", getcwd() . ":/etc:/tmp");

if(!isset($_GET['url'])) {
    $url = 'https://www.zhaoj.in';
} else {
    $url = $_GET['url'];
}

if (strpos($url, 'http://') !== 0 && strpos($url, 'https://') !== 0) {
    die("Illegal scheme!");
}

$content = file_get_contents($url);

$path =  parse_url($url, PHP_URL_PATH);
$ext = pathinfo($path, PATHINFO_EXTENSION);

switch($ext) {
    case 'css':
        $mime_type = "text/css";
        break;
    case 'js':
        $mime_type = "application/javascript";
        break;
    default:
        $mime_type = "text/html;";
        break;
}


header("Content-type: ". $mime_type."; charset=UTF-8");

$content = str_replace("<a href=\"", "<a href=\"/?url=", $content);
$content = str_replace("<a href='", "<a href='/?url=", $content);

echo($content);

$end = microtime(true);
$time = $end - $start;

$last_ip = "";
$result = query("select current_ip, last_ip from ip_log where uuid = '".addslashes($uuid)."'");
if(count($result) > 0) {
    if($ip !== $result[0]['current_ip']) {
        $last_ip = $result[0]['current_ip'];

        query("delete from ip_log where uuid='".addslashes($uuid)."'");
    } else {
        $last_ip = $result[0]['last_ip'];
    }
}

query("insert into ip_log values ('".addslashes($uuid)."', '".addslashes($ip)."', '$last_ip');");

die("\n<!-- Debug Info: \n Duration: $time s \n Current Ip: $ip ".($last_ip !== "" ? "\nLast Ip: ".$last_ip : "")." -->");