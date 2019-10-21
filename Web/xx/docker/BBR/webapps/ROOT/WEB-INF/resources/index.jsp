<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2018/10/9 0009
  Time: 0:19
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
<title>BBR Login</title>
<meta name="description" content="BBR Login">
<meta name="keywords" content="BBR Login">
<link href="" rel="stylesheet">
<style>
	body,p,div,ul,li,h1,h2,h3,h4,h5,h6{
		margin:0;
		padding: 0;
	}
	body{
		background: #E9E9E9; 
	}
	#login{
		width: 400px;
		height: 270px;
		background: #FFF;
		margin:200px auto;
		position: relative;
	}
	#login h1{
		text-align:center;
		position:absolute;
		left:120px;
		top:-40px;
		font-size:21px;
	}
	#login form p{
		text-align: center;
	}
	#username{
		background:url(../../images/user.png) rgba(0,0,0,.1) no-repeat;
		width: 200px;
		height: 30px;
		border:solid #ccc 1px;
		border-radius: 3px;
		padding-left: 32px;
		margin-top: 50px;
		margin-bottom: 30px;
	}
	#password{
		background: url(../../images/pwd.png) rgba(0,0,0,.1) no-repeat;
		width: 200px;
		height: 30px;
		border:solid #ccc 1px;
		border-radius: 3px;
		padding-left: 32px;
		margin-bottom: 30px;
	}
	#submit{
		width: 232px;
		height: 30px;
		background: rgba(0,0,0,.1);
		border:solid #ccc 1px;
		border-radius: 3px;
	}
	#submit:hover{
		cursor: pointer;
		background:#D8D8D8;
	}
</style>
</head>
<body>
<div id="login">
<h1>BBR Login</h1>
	<form action="Login" method="post">
		<p><input type="text" name="username" id="username" placeholder="username"></p>
		<p><input type="password" name="password" id="password" placeholder="password"></p>
		<p><input type="submit" id="submit" value="Login"></p>
	</form>
	<br/>
	<center><p><a href="Download?filename=help.docx" target="_blank">help</a></p></center>
</div>
</body>
</html>