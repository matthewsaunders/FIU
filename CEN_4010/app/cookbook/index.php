<?php
session_start();

if( !isset($_SESSION["username"]) ){
	displayLogin();
}else{
	displayHomePage();
}

function displayLogin(){
	header( "Location: ../login.php" );
}

function displayHomePage(){
	include '../db/connectDatabase.php';
	
	try{
		//get user profile
		$sql = "SELECT * FROM users WHERE name = :username";
		$result = $conn->prepare($sql);
		$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
		$result-> execute();
		$profile = $result->fetch();
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
	}
								
	$isOwner = false;
							
	try{
		$sql = "SELECT * FROM cookbook WHERE ID = :cookbookID";
		$result = $conn->prepare($sql);
		$result->bindValue(":cookbookID", $_GET["cookbook"], PDO::PARAM_INT);
		$result-> execute();
						
		if($cookbookDisplay = $result->fetch()){
			if( $_SESSION["username"] == $cookbookDisplay["author"]){
				$isOwner = true;
			}
		}
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
	}
							
	if( !$isOwner ){
		$_POST["message"] = "Access Denied: You do not own the cookbook being accessed!";
		header("Location: ../home");
	}
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

    <!-- Bootstrap Core ../css -->
    <link href="../css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom ../css -->
    <link href="../css/style.css" rel="stylesheet">

    <!-- Morris Charts ../css -->
    <link href="../css/plugins/morris.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="../font-awesome/css/font-awesome.css" rel="stylesheet" type="text/../css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">

        <!-- Navigation -->
        <nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="/">Cookbook Application</a>
            </div>
            <!-- Top Menu Items -->
            <ul class="nav navbar-right top-nav">
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-envelope"></i> <b class="caret"></b></a>
                    <ul class="dropdown-menu message-dropdown">
                        <li class="message-preview">
                            <a href="#">
                                <div class="media">
                                    <span class="pull-left">
                                        <img class="media-object" src="http://placehold.it/50x50" alt="">
                                    </span>
                                    <div class="media-body">
                                        <h5 class="media-heading"><strong>Management</strong>
                                        </h5>
                                        <p class="small text-muted"><i class="fa fa-clock-o"></i> Yesterday at 4:32 PM</p>
                                        <p>Coming Soon...</p>
                                    </div>
                                </div>
                            </a>
                        </li>
                        <li class="message-footer">
                            <a href="#">Read All New Messages</a>
                        </li>
                    </ul>
                </li>
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-bell"></i> <b class="caret"></b></a>
                    <ul class="dropdown-menu alert-dropdown">
                        <li>
                            <a href="#">Coming Soon <span class="label label-default">Alert</span></a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="#">View All</a>
                        </li>
                    </ul>
                </li>
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i>
					<?php 
						print($profile["name"]);
					?>
					<b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Profile</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-gear"></i> Settings</a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="../login.php?action=logout"><i class="fa fa-fw fa-power-off"></i> Log Out</a>
                        </li>
                    </ul>
                </li>
            </ul>
            
                      <!-- Search Bar -->
                        <div class="col-sm-3 col-md-3 pull-right">
        <form action="../search.php" method="POST" class="navbar-form" role="search">
            <div class="input-group">
                <input type="text" class="form-control" placeholder="Search" name="srch-term" id="srch-term">
                    <div class="input-group-btn">
                        <button class="btn btn-default" type="submit"><i class="glyphicon glyphicon-search"></i></button>
                    </div>
            </div>
        </form>
        </div>
            <!-- Sidebar Menu Items - These collapse to the responsive navigation menu on small screens -->
            <div class="collapse navbar-collapse navbar-ex1-collapse">
                <ul class="nav navbar-nav side-nav">
                    <li>
                        <a href="../recipe"><i class="fa fa-cutlery"></i> All Recipes</a>
                    </li>
					<?php
					if( isset($_SESSION["username"]) ){
						if( $profile['adminStatus'] == "Y" ){
							print("
							<li>
								<a href='../ingredient'><span class='glyphicon glyphicon-apple'></span> All Ingredients</a>
							</li>
							");
						}
					}
					?>
					<li class="divider"></li>
					<li>
                        <a href="/"><span class="fa fa-bookmark"></span> My Recipes</a>
                    </li>
                    <li>
                        <a href="javascript:;" data-toggle="collapse" data-target="#booklist"><span class="glyphicon glyphicon-book"></span> Cookbooks <i class="fa fa-fw fa-caret-down"></i></a>
                        <ul id="booklist" class="collapse">
						<?php
						
						try{
							//get user cookbooks
							$sql = "SELECT * FROM cookbook WHERE author = :username";
							$result = $conn->prepare($sql);
							$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
							$result-> execute();
							
							while( $cookbook = $result->fetch() ){
								if( $cookbook['ID'] == $_GET['cookbook'] ){
									print("<li class='active'>");
								}else{
									print("<li>");
								}
								print("
										<a href='../cookbook?cookbook=$cookbook[ID]'>$cookbook[name]</a>
									</li>
								");
							}
						}catch(PDOException $e){
							//do nothing
						}
						
						?>
                        </ul>
                    </li>
					<li>
                        <a href="../cookbook/createEditCookbook.php"><span class="glyphicon glyphicon-plus-sign"></span> Add a Cookbook</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">
				<?php
				if( isset($_POST['message']) ){
				?>
				<div class="row">
					<div class="col-lg-12">
						<div class='alert alert-info' role='alert'>
							<button type='button' class='close' data-dismiss='alert' aria-label='Close'><span aria-hidden='true'>&times;</span></button>
							<strong>test 123</strong>
						</div>
					</div>
				</div>
				<?php
				}
				?>

                <!-- Page Heading -->
                <div class="row">
                    <div class="col-lg-12">
                        <h1 class="page-header">
                            <?php
							print($cookbookDisplay['name']);
							print("
							<small>
							- <a href='createEditCookbook.php?cookbook=$cookbookDisplay[ID]'>edit cookbook</a>
							- <a href='removeCookbook.php?remove=$cookbookDisplay[ID]'>remove cookbook</a>
							</small>
							");
							?>
							<!--
							<div class="dropdown pull-right">
							<button class="btn btn-default dropdown-toggle" type="button" id="dropdownMenu1" data-toggle="dropdown" aria-expanded="true">
							Add recipe
								<span class="caret"></span>
							</button>
							<ul class="dropdown-menu" role="menu" aria-labelledby="dropdownMenu1">
								<li role="presentation"><a role="menuitem" tabindex="-1" href="../recipe/createEditRecipe.php">Create new recipe</a></li>
								<li role="presentation"><a role="menuitem" tabindex="-1" href="#">Add existing recipe</a></li>								
							</ul>
							-->
                        </h1>
                    </div>
                </div>
                <!-- /.row -->

                <div class="row">
				<?php
				try{
					//get user recipes
					$sql = "SELECT * FROM containsRecipe WHERE cookbookId = :cookbookID";
					$result = $conn->prepare($sql);
					$result->bindValue(":cookbookID", $cookbookDisplay["ID"], PDO::PARAM_INT);
					$result-> execute();
					
					$count = 1;
					
					while( $recipeID = $result->fetch() ){
						$sql = "SELECT * FROM recipe WHERE ID = :recipeID";
						$result2 = $conn->prepare($sql);
						$result2->bindValue(":recipeID", $recipeID["recipeId"], PDO::PARAM_INT);
						$result2-> execute();
					
						while( $recipe = $result2->fetch() ){
							print("
								<div class='col-lg-3'>
								<a href='../recipe?recipe=$recipe[ID]'>
									<div class='panel panel-default'>
										<div class='panel-heading'>
											<h3 class='panel-title'><i class=''></i>$recipe[name]</h3>
										</div>
										<div class='panel-body'>
											<img src='../img/default.jpg' class='img-responsive' alt='default' width='100%' height='100%'>
										</div>
									</div>
								</a>
								</div>
							");
							
							//start a new row every 3rd recipe
							if($count++ % 3 == 0){
								print("</div><div class='row'>");
							}
						}
					
					}	
				}catch(PDOException $e){
					//do nothing
				}
				?>

            </div>
            <!-- /.container-fluid -->

        </div>
        <!-- /#page-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="../js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="../js/bootstrap.min.js"></script>

    <!-- Morris Charts JavaScript -->
    <script src="../js/plugins/morris/raphael.min.js"></script>
    <script src="../js/plugins/morris/morris.min.js"></script>
    <script src="../js/plugins/morris/morris-data.js"></script>

</body>

</html>
<?php
}
?>