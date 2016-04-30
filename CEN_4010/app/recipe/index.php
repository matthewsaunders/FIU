<?php
session_start();

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

if( isset($_GET['recipe']) ){
	displayRecipe();
}else{
	displayAllRecipes();
}

function displayAllRecipes(){
	header( "Location: allRecipes.php" );
}

function displayRecipe(){
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
		$sql = "SELECT * FROM recipe WHERE ID = :recipeID";
		$result = $conn->prepare($sql);
		$result->bindValue(":recipeID", $_GET["recipe"], PDO::PARAM_STR);
		$result-> execute();
		$recipe = $result->fetch();
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
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
                <form class="navbar-form" role="search">
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
					if( isset($_SESSION['username']) and $profile['adminStatus'] == "Y" ){
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
						<form role="form">
                            <div class="row">
    							<div class="col-lg-12">
    								<h2 class="text-center">
									<?php
									print("$recipe[name]");
									?>
									</h2> 
    							</div>
                            </div>
							<div class="row">
                                <div class="col-lg-4">
                                    <img src="../img/default.jpg" class="img-responsive" alt="peanutButter" width="100%" height="100%">
                                </div>
                                <div class="col-lg-8">

                                    <div class="row">
                                        <div class="col-sm-3"  >
                                            
                                        </div>
                                        <div class="col-sm-9 vcenter"  >
											<?php
											if( isset($_SESSION['username']) and $profile['name'] == $recipe['author'] || $profile['adminStatus'] == "Y"){
												print("<a href='createEditRecipe.php?recipe=$recipe[ID]'>edit recipe</a> - ");
												print("<a href='removeRecipe.php?remove=$recipe[ID]'>remove recipe</a> -");
											}
											
											print("<a href='../cookbook/addToCookbook.php?recipe=".$recipe['ID']."'>add to cookbook</a>");
											?>
                                        </div>
                                    </div>

                                    <div class="row">
                                        <div class="col-sm-3"  >
                                            <h4><strong>Name</strong></h4>
                                        </div>
                                        <div class="col-sm-9 vcenter"  >
                                            <p>
											<?php
											print("$recipe[name]");
											?>
											</p>
                                        </div>
                                    </div>

                                    <div class="row">
                                        <div class="col-sm-3"  >
                                            <h4><strong>Author</strong></h4>
                                        </div>
                                        <div class="col-sm-9 vcenter"  >
                                            <p>
											<?php
											print("$recipe[author]");
											?>
											</p>
                                        </div>
                                    </div>

                                    <div class="row">
                                        <div class="col-sm-3"  >
                                            <h4><strong>Difficulty</strong></h4>
                                        </div>
                                        <div class="col-sm-9"  >
                                            <div class="btn-group" role="group" aria-label="...">
											<?php
												if($recipe['difficulty'] == 1){
													print("<button type='button' class='btn btn-default active'>1</button>");
												}else{
													print("<button type='button' class='btn btn-default'>1</button>");
												}
												
												if($recipe['difficulty'] == 2){
													print("<button type='button' class='btn btn-default active'>2</button>");
													}else{
													print("<button type='button' class='btn btn-default'>2</button>");
												}
												
												if($recipe['difficulty'] == 3){
													print("<button type='button' class='btn btn-default active'>3</button>");
													}else{
													print("<button type='button' class='btn btn-default'>3</button>");
												}
												
												if($recipe['difficulty'] == 4){
													print("<button type='button' class='btn btn-default active'>4</button>");
													}else{
													print("<button type='button' class='btn btn-default'>4</button>");
												}
												
												if($recipe['difficulty'] == 5){
													print("<button type='button' class='btn btn-default active'>5</button>");
													}else{
													print("<button type='button' class='btn btn-default'>5</button>");
												}
											?>
                                            </div>
                                        </div>
                                    </div>

                                    <div class="row">
                                        <div class="col-sm-3"  >
                                            <h4><strong>Cooktime</strong></h4>
                                        </div>
                                        <div class="col-sm-9 vcenter"  >
                                            <p>
											<?php
											$hours = intval($recipe['cooktime'] / 60);
											$minutes = $recipe['cooktime'] % 60;
											print("$hours hours, $minutes minutes");
											?>
											</p>
                                        </div>
                                    </div>

                                    <div class="row">
                                        <div class="col-sm-3" >
                                            <h4><strong>Ingredients</strong></h4>
                                        </div>
                                        <div class="col-sm-9 vcenter"  >
											<?php
											try{
												//get user cookbooks
												$sql = "SELECT * FROM containsIngredient WHERE recipeId = :recipeID";
												$result = $conn->prepare($sql);
												$result->bindValue(":recipeID", $_GET["recipe"], PDO::PARAM_INT);
												$result-> execute();
												
												print("<table class='ingredientsTable'>");
												while( $ingredient = $result->fetch() ){
													$sql = "SELECT * FROM ingredient WHERE name = :ingredientName";
													$result2 = $conn->prepare($sql);
													$result2->bindValue(":ingredientName", trim($ingredient['ingredientName']), PDO::PARAM_STR);
													$result2-> execute();
													$unit = $result2->fetch();
													
													print("
													<tr>
														<td>$ingredient[amount]</td>");
														if( $unit['measurementUnit'] != "NULL"){
															print("<td> $unit[measurementUnit]</td>");
														}else{
															print("<td></td>");
														}
														print("<td>$ingredient[ingredientName]</td>
													</tr>
													");
													
												}
												print("</table>");
											}catch(PDOException $e){
												//do nothing
											}
											?>
                                        </div>
                                    </div>

                                    <div class="row">
                                        <div class="col-sm-3"  >
                                            <h4><strong>Cooking Instructions</strong></h4>
                                        </div>
                                        <div class="col-sm-9 vcenter"  >
                                            <p>
											<?php
											print("$recipe[instructions]");
											?>
											</p>
                                        </div>
                                    </div>

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