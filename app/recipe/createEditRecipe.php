<?php
session_start();

if( !isset($_SESSION['username']) ){
	displayLogin();
}elseif( isset($_POST["submit"]) and isset($_POST["recipe-id"]) ){
	updateDB();
}elseif( isset($_POST["submit"]) ){
	createInDB();
}else{
	displayRecipeForm();
}

function displayLogin(){
	header( "Location: ../login.php" );
}

function createInDB(){
	include '../db/connectDatabase.php';
	
	if( isset($_SESSION["username"]) ){
		try{
			//get user profile
			$sql = "INSERT INTO cookbook (author, name) VALUES (:author, :name)";
			$result = $conn->prepare($sql);
			$result->bindValue(":author", trim($_POST['cookbook-author']), PDO::PARAM_STR);
			$result->bindValue(":name", trim($_POST['cookbook-name']), PDO::PARAM_STR);
			$result-> execute();
			
			$_POST["message"] = "Cookbook ".$_POST['cookbook-name']." added successfully!";
			header( "Location: ../home" );
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
	}
}

function updateDB(){
	include '../db/connectDatabase.php';
	
	try{
		//get user profile
		$sql = "UPDATE cookbook SET name = :cookbookName WHERE ID = :cookbookID";
		$result = $conn->prepare($sql);
		$result->bindValue(":cookbookName", trim($_POST['cookbook-name']), PDO::PARAM_STR);
		$result->bindValue(":cookbookID", trim($_POST['cookbook-id']), PDO::PARAM_STR);
		$result-> execute();
			
		//$_POST["message"] = "Cookbook ".$_POST['cookbook-name']." updated successfully!";
		header( "Location: ../cookbook?cookbook=".$_POST['cookbook-id'] );
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
	}
}

function displayRecipeForm(){
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
	
	$recipeExists = false;
	
	if( isset($_GET["recipe"]) ){
		try{
			//get user profile
			$sql = "SELECT * FROM recipe WHERE ID = :recipeID";
			$result = $conn->prepare($sql);
			$result->bindValue(":recipeID", $_GET['recipe'], PDO::PARAM_INT);
			$result-> execute();
			
			if( $recipeEditing = $result->fetch() ){
				if( $recipeEditing['author'] == $_SESSION["username"] ){
					$recipeExists = true;
				}
			}
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
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
					<li class="divider"></li>
					<?php
					if( $profile['adminStatus'] == "Y" ){
						print("
						<li>
							<a href='../ingredient'><span class='glyphicon glyphicon-apple'></span> All Ingredients</a>
						</li>
						");
					}
					?>
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
								$sql = "SELECT * FROM cookbook WHERE author = :username";
								$result = $conn->prepare($sql);
								$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
								$result-> execute();
								
								while( $cookbook = $result->fetch() ){
									print("
										<li>
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
							<a href="createEditCookbook.php"><span class="glyphicon glyphicon-plus-sign"></span> Add a Cookbook</a>
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
						<form role="form" action="createEditCookbook.php" method="post">
							<div class="col-lg-12">
								<?php
								if( isset($_GET['recipe']) ){
									print("<h2 class='text-center'>Edit Recipe</h2>");
								}else{
									print("<h2 class='text-center'>New Recipe</h2>");
								}
								?>
								
							</div>
							<div class="col-md-9">
								<div class="well well-sm"><strong><span class="glyphicon glyphicon-asterisk"></span>Required Field</strong></div>
								<div class="form-group">
									<label for="InputName" class="col-md-2">Name *</label>
									<div class="input-group col-md-10">
										<?php
										if( $recipeExists ){
											print('<input type="text" class="form-control" name="recipe-name" id="InputName" value="'.$recipeEditing["name"].'" required>');
										}else{
											print("<input type='text' class='form-control' name='recipe-name' id='InputName' placeholder='Enter Name' required>");
										}
										?>
									</div>
								</div>								
                                <div style="clear:both"></div> 
								
								<div class="form-group">
									<label for="InputDifficulty" class="col-md-2">Difficulty</label>
									<div class="btn-group" role="group" aria-label="...">
                                      <?php
												if( $recipeExists and $recipeEditing['difficulty'] == 1){
													print("<button type='button' class='btn btn-default active'>1</button>");
												}else{
													print("<button type='button' class='btn btn-default'>1</button>");
												}
												
												if( $recipeExists and $recipeEditing['difficulty'] == 2){
													print("<button type='button' class='btn btn-default active'>2</button>");
													}else{
													print("<button type='button' class='btn btn-default'>2</button>");
												}
												
												if($recipeExists and $recipeEditing['difficulty'] == 3){
													print("<button type='button' class='btn btn-default active'>3</button>");
													}else{
													print("<button type='button' class='btn btn-default'>3</button>");
												}
												
												if($recipeExists and $recipeEditing['difficulty'] == 4){
													print("<button type='button' class='btn btn-default active'>4</button>");
													}else{
													print("<button type='button' class='btn btn-default'>4</button>");
												}
												
												if($recipeExists and $recipeEditing['difficulty'] == 5){
													print("<button type='button' class='btn btn-default active'>5</button>");
													}else{
													print("<button type='button' class='btn btn-default'>5</button>");
												}
											?>
                                    </div>
								</div>
								<div class="form-group">
									<label for="InputEmail" class="col-md-2">Cooktime</label>
									<div class="input-group">
										<?php
											if( $recipeExists and $recipeEditing['difficulty'] == 1){
												$hours = intval($recipeEditing['cooktime'] / 60);
												$minutes = $recipeEditing['cooktime'] % 60;
											}
										?>
                                        <div class="col-md-4">
											<?php
											if($recipeExists){
												print('<input type="number" class="form-control" id="recipe-hours" name="recipe-hours" value='.$hours.'>');
											}else{
												print('<input type="number" class="form-control" id="recipe-hours" name="recipe-hours" placeholder="Hours">');
											}
											?>
                                        </div>
                                        <div class="col-md-4">
                                            <?php
											if($recipeExists){
												print("<input type='number' class='form-control' id='recipe-minutes' name='recipe-minutes' value=".$minutes.">");
											}else{
												print('<input type="number" class="form-control" id="recipe-minutes" name="recipe-minutes" placeholder="Minutes">');
											}
											?>
                                        </div>
                                    </div>
								</div>

                                <div class="form-group">
                                    <label for="InputMessage" class="col-md-3 pull-left">Ingredients *</label>
									<?php
									if($recipeExists){
										try{
											//get ingredients
											$sql = "SELECT * FROM containsIngredient WHERE recipeId = :recipeID";
											$result = $conn->prepare($sql);
											$result->bindValue(":recipeID", $_GET["recipe"], PDO::PARAM_INT);
											$result-> execute();
												
											while( $ingredient = $result->fetch() ){
												$sql = "SELECT * FROM ingredient WHERE name = :ingredientName";
												$result2 = $conn->prepare($sql);
												$result2->bindValue(":ingredientName", trim($ingredient['ingredientName']), PDO::PARAM_STR);
												$result2-> execute();
												$unit = $result2->fetch();
												
												$count = 1;
												//print_r($unit);
												print("
													<div class='input-group col-md-2 pull-right'>
														<input name='recipe-ingredient-unit-$count' id='InputMessage' class='form-control' value='$unit[measurementUnit]'></input>
													</div>
													<div class='input-group col-md-2 pull-right'>
														<input name='recipe-ingredient-amount-$count' id='InputMessage' class='form-control' value='$ingredient[amount]'></input>
													</div>
													<div class='input-group col-md-5 pull-right'>
														<input name='recipe-ingredient-name-$count' id='InputMessage' class='form-control' value='$ingredient[ingredientName]'></input>
													</div>
													<div style='clear:both'></div>
												");
												$count++;
											}
										}catch(PDOException $e){
											//do nothing
										}
										print("
										<div class='form-group'>
											<label for='InputMessage' class='col-md-2 pull-left'></label>
											<div class='input-group col-md-2 pull-right'>
												<input name='recipe-ingredient-unit-$count' id='InputMessage' class='form-control' placeholder='Units'></input>
											</div>
											<div class='input-group col-md-2 pull-right'>
												<input name='recipe-ingredient-amount-$count' id='InputMessage' class='form-control' placeholder='Amount'></input>
											</div>
											<div class='input-group col-md-5 pull-right'>
												<input name='recipe-ingredient-name-$count' id='InputMessage' class='form-control' placeholder='Ingredient'></input>
											</div>
										</div>
										");
									}else{
										for($count = 1; $count <= 3; $count++){
											print("
											<div class='form-group'>
												<label for='InputMessage' class='col-md-2 pull-left'></label>
												<div class='input-group col-md-2 pull-right'>
													<input name='recipe-ingredient-unit-$count' id='InputMessage' class='form-control' placeholder='Units'></input>
												</div>
												<div class='input-group col-md-2 pull-right'>
													<input name='recipe-ingredient-amount-$count' id='InputMessage' class='form-control' placeholder='Amount'></input>
												</div>
												<div class='input-group col-md-5 pull-right'>
													<input name='recipe-ingredient-name-$count' id='InputMessage' class='form-control' placeholder='Ingredient'></input>
												</div>
											</div>
											<div style='clear:both'></div>
											");
										}
									}
									?>
                                </div>
                                <div style="clear:both"></div>

                                
                                
                                <div class="form-group" style="margin-top:10px;">
                                    <button type="button" class="btn btn-info col-md-offset-10">Add Ingredient</button>
                                    <br>
                                </div>
                                <div class="form-group">
									<label for="InputMessage" class="col-md-2">Cooking Instructions</label>
									<div class="input-group">
										<?php
										if($recipeExists){
											print('<textarea name="recipe-instructions" id="InputMessage" class="form-control" rows="5" required>'.$recipeEditing["instructions"].'</textarea>');
										}else{
											print('<textarea name="recipe-instructions" id="InputMessage" class="form-control" rows="5" required></textarea>');
										}
										?>
										<span class="input-group-addon"><span class="glyphicon glyphicon-asterisk"></span></span>
									</div>
								</div>
								
								
								
								
								
								
								
								
								
								
								
								
								
								
								
								
								
								
								<input type="hidden" name="cookbook-author" value="
								<?php
								print($_SESSION["username"]);
								?>
								"></input>
								<div class="form-actions pull-right">
									<?php
									if( isset($_GET['cookbook']) ){
										print("<input type='hidden' name='cookbook-id' value='$cookbookEditing[ID]'></input>");
									}
									?>
									<input type="submit" name="submit" value="Submit" class="btn btn-primary"></input>
									<button type="button" class="btn">Cancel</button>
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