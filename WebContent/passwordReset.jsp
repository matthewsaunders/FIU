<%@ page language="java" contentType="text/html; charset=US-ASCII"
	pageEncoding="US-ASCII"%>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Reset your Password</title>
<meta name="keywords" content="" />
<meta name="description" content="" />
<link href="http://fonts.googleapis.com/css?family=Open+Sans:400,300,600,700|Archivo+Narrow:400,700" rel="stylesheet" type="text/css">
<link href="register.css" rel="stylesheet" type="text/css" media="all" />
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
</head>

<body>
	<div id="header-wrapper">
		<div id="header" class="container">
			<div id="logo">
				<a href="/FamilyTree/welcome.jsp"> <img id="logoPic"
					src="images/logo.png">
				</a>
			</div>
			<div id="menu">
				<ul>
					<li><a href="/FamilyTree/welcome.jsp"
						accesskey="1" title="">Home</a></li>
				</ul>
			</div>
		</div>
	</div>

	<div id="banner-wrapper">
		<div id="banner" class="passForm">

			<div align="left">
				<form method="GET" action="AccountController"
					name="resetForm" class="passwordReset">
					<P>
						<label for="email">Enter Email:</label> <input type="text"
							name="email" id="email" value="" />
					</p>
					
					<P id="resetButton">
						<button type="submit" name="reset" class="button-register">Reset</button>
					
					${message}
					</p>
					
					
				</form>
			</div>
		</div>
		<div id="treePicture">
			<img src="images/familytree.png" width="623" />
			<p style="text-align: center">
				Your Family Ancestry just <strong>a click away</strong>.
			</p>
		</div>
	</div>

	<div id="copyright" class="container">
		<p>
			Copyright (c) 2013 <a href="http://www.familytree.com">FamilyTree.com</a>.
			All rights reserved.
		</p>
	</div>
</body>
</html>