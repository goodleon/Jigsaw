#!/usr/bin/php

<?php
	include "db.php";
	// $json = $_POST["json"];
	$json = fread( fopen("jsondump.txt", 'r'), filesize("jsondump.txt") );
	$obj = json_decode($json, true);
	$proto = $obj["proto"];
	$userid = $obj["userid"];
	$response = array("proto"=>50003);

	if ($proto==10003) { //登陆
		if (is_null( getUser($userid) )) {
			$new_uid = create_user();
		}
		$response["proto"] = 50003;
		$response["userid"] = $new_uid;
	}
	echo json_encode($response);




















?>