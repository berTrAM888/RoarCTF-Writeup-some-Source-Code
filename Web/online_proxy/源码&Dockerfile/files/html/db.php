<?php
/**
 * Created by PhpStorm.
 * User: jinzhao
 * Date: 2019/6/21
 * Time: 10:31 PM
 */

include 'config.php';

$mysqli = new mysqli(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);

if ($mysqli->connect_errno) {
    printf("Connect failed: %s\n", $mysqli->connect_error);
    exit();
}

function query($sql) {
    global $mysqli;

    $result_return = array();
    if ($result = mysqli_query($mysqli, $sql)) {
        while ($row = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
            array_push($result_return, $row);
        }

        mysqli_free_result($result);
    }

    return $result_return;
}

function gen_uuid() {
    $uuid = array(
        'time_low'  => 0,
        'time_mid'  => 0,
        'time_hi'  => 0,
        'clock_seq_hi' => 0,
        'clock_seq_low' => 0,
        'node'   => array()
    );

    $uuid['time_low'] = mt_rand(0, 0xffff) + (mt_rand(0, 0xffff) << 16);
    $uuid['time_mid'] = mt_rand(0, 0xffff);
    $uuid['time_hi'] = (4 << 12) | (mt_rand(0, 0x1000));
    $uuid['clock_seq_hi'] = (1 << 7) | (mt_rand(0, 128));
    $uuid['clock_seq_low'] = mt_rand(0, 255);

    for ($i = 0; $i < 6; $i++) {
        $uuid['node'][$i] = mt_rand(0, 255);
    }

    $uuid = sprintf('%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x',
        $uuid['time_low'],
        $uuid['time_mid'],
        $uuid['time_hi'],
        $uuid['clock_seq_hi'],
        $uuid['clock_seq_low'],
        $uuid['node'][0],
        $uuid['node'][1],
        $uuid['node'][2],
        $uuid['node'][3],
        $uuid['node'][4],
        $uuid['node'][5]
    );

    return $uuid;
}
