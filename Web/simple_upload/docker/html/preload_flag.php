<?php
	if(stristr($_SERVER["REQUEST_URI"], 'preload_flag')){
		exit;
	}else{
		echo file_get_contents('/flag');
		exit;
	}
?>