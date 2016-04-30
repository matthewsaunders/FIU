<?php
session_start();

if( isset($_GET['remove']) ){
	removeCookbook();
}elseif( isset($_POST['submit']) and isset($_POST['remove-cookbook']) ){
	removeFromDB();
}else{
	displayAllRecipes();
}

function displayAllRecipes(){
	header( "Location: ../recipe/allRecipes.php" );
}

function removeFromDB(){
	include '../db/connectDatabase.php';

	if( isset($_SESSION["username"]) ){
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
	}
	
	try{
		//get recipe information
		$sql = "SELECT * FROM cookbook WHERE ID = :cookbookID";
		$result = $conn->prepare($sql);
		$result->bindValue(":cookbookID", $_POST["remove-cookbook"], PDO::PARAM_STR);
		$result-> execute();
		$cookbook = $result->fetch();
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
	}

	if($profile['name'] == $cookbook['author'] || $profile['adminStatus'] == "Y"){
		try{
			$sql = "DELETE FROM cookbook WHERE ID = :cookbookID";
			$result = $conn->prepare($sql);
			$result->bindValue(":cookbookID", $_POST["remove-cookbook"], PDO::PARAM_STR);
			$result-> execute();
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
	}
	
	displayAllRecipes();
}

function removeCookbook(){
	include '../db/connectDatabase.php';

	if( isset($_SESSION["username"]) ){
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
	}
	
	try{
		//get recipe information
		$sql = "SELECT * FROM cookbook WHERE ID = :cookbookID";
		$result = $conn->prepare($sql);
		$result->bindValue(":cookbookID", $_GET["remove"], PDO::PARAM_STR);
		$result-> execute();
		$cookbook = $result->fetch();
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
	}
	
	if($profile['name'] != $cookbook['author'] && $profile['adminStatus'] != "Y"){
		header( "Location: ../home");
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
				<?php
				if( isset($_SESSION["username"]) ){
				?>
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
			<?php
			}else{
			?>
				<li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i>
					Guest
					<b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="../login.php"><i class="fa fa-fw fa-user"></i> Login</a>
                        </li>
                    </ul>
                </li>
			<?php
			}
			?>
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
					if( $profile['adminStatus'] == "Y" ){
						print("
						<li>
							<a href='../ingredient'><span class='glyphicon glyphicon-apple'></span> All Ingredients</a>
						</li>
						");
					}
					?>
					<li class="divider"></li>
					<?php
					if( isset($_SESSION["username"]) ){
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
								$sql = "SELECT name FROM cookbook WHERE author = :username";
								$result = $conn->prepare($sql);
								$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
								$result-> execute();
								
								while( $cookbook = $result->fetch() ){
									print("
										<li>
											<a href='../cookbook?cookbook=$cookbook[name]'>$cookbook[name]</a>
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
					<?php
					}
					?>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">
					<div class="row">
						<form action="removeCookbook.php" method="post">
                            <div class="row">
								<div class="col-lg-12">
									<h2 class='text-center'>Remove Cookbook</h2>
								</div>
							</div>
							<div class="col-md-6 col-md-offset-3">
								<?php
								try{
									//get recipe information
									$sql = "SELECT * FROM cookbook WHERE ID = :cookbookID";
									$result = $conn->prepare($sql);
									$result->bindValue(":cookbookID", $_GET["remove"], PDO::PARAM_STR);
									$result-> execute();
									$cookbook = $result->fetch();
								}catch(PDOException $e){
									$conn = null;
									print($e->getMessage()."<br>");
								}
								?>
								<p>Are you sure you want to delete <strong><?php print($cookbook['name']) ?></strong>?</p>
							</div>
                            <div style="clear:both"></div> 
							<div class="col-md-6 col-md-offset-3">
								<div class="form-actions pull-right">
									<input type="hidden" name="remove-cookbook" value=" <?php print($cookbook['ID']); ?> "></input>
									<input type="submit" name="submit" value="Submit" class="btn btn-primary"></input>
									<?php
									print("
									<script>
									function cancelRemove(){
										location.href = '../cookbook?cookbook=".$_GET['remove']."';
									}
									</script>
									");
									print("<button type='button' onclick='cancelRemove()' class='btn'>Cancel</button>");
									?>
								</div>	
							</div>
						</form>
					</div>
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