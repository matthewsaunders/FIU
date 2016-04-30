<?php
session_start();
//$_POST["login"] = true;
//$_GET["action"] = "logout";
//$_POST["username"] = "John Doe";
//$_POST["password"] = "password123";
//$_SESSION["username"] = "John Doe";

if( isset($_GET["action"]) and $_GET["action"] == "logout"){
	logout();
}elseif(isset($_SESSION["username"]) ) {
	displayHomePage();
}elseif ( isset( $_POST["login"] ) ) {
	login();
}else{
	displayLoginForm('');
}

function login() {
	if (isset($_POST["username"]) and isset($_POST["password"])) {
		
		try{
			include 'db/connectDatabase.php';
			$sql = "SELECT name, password FROM users WHERE name = :username";
			$result = $conn->prepare($sql);
			$result->bindValue(":username", $_POST["username"], PDO::PARAM_STR);
			$result-> execute();
			$row = $result->fetch();
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
		
		if ($row and $_POST["username"] == $row['name'] and $_POST["password"] == $row['password'] ) {
			$_SESSION["username"] = $row['name'];
			$_POST["message"] = "Welcome Back!!";
			session_write_close();
			header( "Location: /home" );
		} else {
			displayLoginForm('Sorry, that username/password could not be found. Please try again.' );
		}
		
	}else{
		displayLoginForm('Sorry, that username/password could not be found. Please try again.' );
	}
}

function logout() {
	session_unset();
	session_destroy();
	$_SESSION = array();
	session_write_close();
	displayLoginForm("Successfully Logged Out!");
}

function displayHomePage(){
	header( "Location: /home" );
}

function displayLoginForm( $message ) {
?>

<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Cookbook Application</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/style.css" rel="stylesheet">

    <!-- Morris Charts CSS -->
    <link href="css/plugins/morris.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="font-awesome/css/font-awesome.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">
	    <div class="container">    
        <div id="loginbox" style="margin-top:50px;" class="mainbox col-md-6 col-sm-offset-1 col-sm-8 ">                    
            <div class="panel panel-info" >
                    <div class="panel-heading">
                        <div class="panel-title">Sign In</div>
                        <div style="float:right; font-size: 80%; position: relative; top:-10px"><a href="#">Forgot password?</a></div>
                    </div>     

                    <div style="padding-top:30px" class="panel-body" >
                            
                        <form id="loginform" action="login.php" method="post" class="form-horizontal" role="form">
                            <?php if($message){
								if( isset($_GET["action"]) and $_GET["action"] == "logout"){
									print("
									<div class='alert alert-info' role='alert'>
									");
								}else{
									print("
									<div class='alert alert-danger' role='alert'>
									");
								}
									print("
										  <button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>
										  <strong>$message</strong>
										</div>
									");
							}?>

                            <div style="margin-bottom: 25px" class="input-group">
                                        <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
                                        <input id="login-username" type="text" class="form-control" name="username" value="" placeholder="username or email">                                        
                                    </div>
                                
                            <div style="margin-bottom: 25px" class="input-group">
                                        <span class="input-group-addon"><i class="glyphicon glyphicon-lock"></i></span>
                                        <input id="login-password" type="password" class="form-control" name="password" placeholder="password">
                                    </div>
                                    

                                
                            <div class="input-group">
                                      <div class="checkbox">
                                        <label>
                                          <input id="login-remember" type="checkbox" name="remember" value="1"> Remember me
                                        </label>
                                      </div>
                                    </div>


                                <div style="margin-top:10px" class="form-group">
                                    <!-- Button -->

                                    <div class="col-sm-12 controls">
										<input type="hidden" name="login" value="true"></input>
										<input type="submit" name="login" value="Login" id="btn-login" class="btn btn-success"></input>
										<a type="button" class="btn btn-default">Cancel</a>
                                    </div>
                                </div>


                                <div class="form-group">
                                    <div class="col-md-12 control">
                                        <div style="border-top: 1px solid#888; padding-top:15px; font-size:85%" >
                                            Don't have an account! 
                                        <a href="#" onClick="$('#loginbox').hide(); $('#signupbox').show()">
                                            Sign Up Here
                                        </a>
                                        </div>
                                    </div>
                                </div>    
                            </form>     



                        </div>                     
                    </div>  
        </div>
        <div id="signupbox" style="display:none; margin-top:50px" class="mainbox col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
                    <div class="panel panel-info">
                        <div class="panel-heading">
                            <div class="panel-title">Sign Up</div>
                            <div style="float:right; font-size: 85%; position: relative; top:-10px"><a id="signinlink" href="#" onclick="$('#signupbox').hide(); $('#loginbox').show()">Sign In</a></div>
                        </div>  
                        <div class="panel-body" >
                            <form id="signupform" class="form-horizontal" role="form">
                                
                                <div id="signupalert" style="display:none" class="alert alert-danger">
                                    <p>Error:</p>
                                    <span></span>
                                </div>
                                    
                                <div class="alert alert-danger" role="alert">
                                  <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                                  <strong>Sign Up Failed:</strong> This email is already being used.  To reset your password, click <a href="#">here</a>.
                            </div>
                                
                                  
                                <div class="form-group">
                                    <label for="email" class="col-md-3 control-label">Email</label>
                                    <div class="col-md-9">
                                        <input type="text" class="form-control" name="email" placeholder="Email Address">
                                    </div>
                                </div>
                                    
                                <div class="form-group">
                                    <label for="firstname" class="col-md-3 control-label">First Name</label>
                                    <div class="col-md-9">
                                        <input type="text" class="form-control" name="firstname" placeholder="First Name">
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label for="lastname" class="col-md-3 control-label">Last Name</label>
                                    <div class="col-md-9">
                                        <input type="text" class="form-control" name="lastname" placeholder="Last Name">
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label for="password" class="col-md-3 control-label">Password</label>
                                    <div class="col-md-9">
                                        <input type="password" class="form-control" name="passwd" placeholder="Password">
                                    </div>
                                </div>

								<div class="form-group">
                                    <!-- Button -->                                        
                                    <div class="col-md-offset-3 col-md-9">
                                        <button id="btn-signup" type="button" class="btn btn-info"><i class="icon-hand-right"></i> &nbsp Sign Up</button>
                                        <a type="button" class="btn btn-default">Cancel</a>
                                    </div>
                                </div>
                                
                            </form>
                         </div>
                    </div>
         </div> 
    </div>
	
	</div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>

    <!-- Morris Charts JavaScript -->
    <script src="js/plugins/morris/raphael.min.js"></script>
    <script src="js/plugins/morris/morris.min.js"></script>
    <script src="js/plugins/morris/morris-data.js"></script>

</body>
</html>




<?php
}
?>